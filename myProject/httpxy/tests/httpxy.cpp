/*************************************************************************
  > File Name: Httpxy2.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Wed Nov 22 19:12:20 2017
 ************************************************************************/


#include"ThreadPool.h"
#include"Cdebug.h"

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

#include<iostream>
#include<sstream>
#include<fstream>

using namespace std;

#define SERVER_NAME "Server: jdbhttpd/0.1.0\r\n"//定义server名称

int getLine(int fd,char*buf,int size);
void unimplemented(int client);
void notFound(int client);
void readRequest(int clientFd);  
void headers(int clientFd);
void cat(int clientFd,ifstream& fs); //发送文件内容
void cat2(int clientFd,int fd); //发送文件内容
void returnFile(int fd,const string& path);
void returnFile2(int fd,const string& path);
void cannot_execute(int client);  
void bad_request(int client);
void exec(int clientFd,const string& method,const string& path,const string& params);

int getLine(int fd,char*buf,int size){  //获取一行
	int n=0;
	int i=0;
	char c='\0';

	while(c!='\n'&&i<size){
		n=recv(fd,&c,1,0);
		if(n>0){
			//如果读取到'\r',因为后面会有'\n',需要读出，如果后面不是'\n',用'\n'代替'\r'
			if(c=='\r'){
				n=recv(fd,&c,1,MSG_PEEK);
				if(n>0&&c=='\n'){
					recv(fd,&c,1,0);
				}
				else
					c='\n';
			}
			buf[i]=c;
			i++;
		}
		else 
			c='\n';
	}
	buf[i]='\0';
	return i;
}
void unimplemented(int client)
{
	char buf[1024];
	sprintf(buf, "HTTP/1.0 501 Method Not Implemented\r\n");
	strcat(buf, SERVER_NAME);
	strcat(buf, "Content-Type: text/html\r\n");
	strcat(buf, "\r\n");
	send(client, buf, strlen(buf), 0);

	sprintf(buf, "<HTML><HEAD><TITLE>Method Not Implemented\r\n");
	strcat(buf, "</TITLE></HEAD>\r\n");
	strcat(buf, "<BODY><P>HTTP request method not supported.\r\n");
	strcat(buf, "</BODY></HTML>\r\n");
	send(client, buf, strlen(buf), 0);
}
void notFound(int client){
	char buf[1024];
	sprintf(buf,"HTTP/1.0 404 NOT FOUND\r\n");
	strcat(buf,SERVER_NAME);
	strcat(buf,"CONTENT-TYPE: http/text\r\n");
	strcat(buf,"\r\n");
	send(client,buf,strlen(buf),0);

	sprintf(buf, "<HTML><TITLE>Not Found</TITLE>\r\n");
	strcat(buf, "<BODY><P>The server could not fulfill\r\n");
	strcat(buf, "your request because the resource specified\r\n");
	strcat(buf, "is unavailable or nonexistent.\r\n");
	strcat(buf, "</BODY></HTML>\r\n");
	send(client, buf, strlen(buf), 0);
}


void readRequest(int clientFd){  
	int n=0;
	char buf[1024];
	bool cgi=false;
	struct stat st;

	string method;
	string url;
	string path;
	string params;  //保存url中"?"后面的参数字符串

	//取出http的请求头
	//请求头格式：  Method url http版本
	n=getLine(clientFd,buf,sizeof(buf));
	if(n==0)
	{
		debug_error("未知错误");	
	}

	//根据空格分别取出method，url 
	istringstream head(buf);
	head>>method;
	head>>url;
	debug_value("method=",method);
	debug_value("url=",url);

	//method只实现了get和post，所以不是get或Post的需要返回错误
	if(method!="GET"&&method!="POST")
	{
		debug_error("method 不是get,也不是post");
		unimplemented(clientFd);
		::close(clientFd);
		return ;
	}
	//当method是GET时，可能会有？，代表后面有参数,所以需要查找是否有'?'
	if(method=="GET"){
		char *c=const_cast<char*>(url.c_str());
		while((*c!='?')&&(*c!='\0')){
			c++;
		}
		if(*c=='?'){
			debug_error("url中有?");
			cgi=true;
			//截断url,只讲?前边的保存下来
			*c='\0';
			url=string(url.c_str());
			debug_value("重新生成的url=",url);
			//将？后面的保存到params中
			params=string(c+1);
			debug_value("params=",params);
		}
	}
	//如果是Psot，需要动态执行
	if(method=="POST")
		cgi=true;

	//将url复制给path
	path="../file"+url;
	debug_value("path=",path);

	//如果path的最后是/，代表path是目录，需要将目录下的主页显示
	int len=path.size();
	if(path[len-1]=='/'){
		path=path+"index.html";
	}

	//函数定义:    int stat(const char *file_name, struct stat *buf);
	// //函数说明:    通过文件名filename获取文件信息，并保存在buf所指的结构体stat中
	//  //返回值:     执行成功则返回0，失败返回-1，错误代码存于errno（需要include <errno.h>）
	if(stat(path.c_str(),&st)==-1){
		debug_error("stat(path)==-1,文件不存在");
		char buf[1024]={0};
		int n=-1;
		while(n!=0&&strcmp("\n",buf))//如果访问的网页不存在，需要将request剩余部分全部读取出来
		{
			n=getLine(clientFd,buf,sizeof(buf));   //存在问题,如果读出的buf是space字符+'\n',不能跳出循环.所以会再一次调用getLine,可能会因为没有数据阻塞.
			if(strcmp("\n",buf)){
				cout<<"buf="<<buf<<endl;
			}
		}
		notFound(clientFd);
		::close(clientFd);
		return ;
	}
	else{
		if ((st.st_mode & S_IFMT) == S_IFDIR){//如果path是目录，需要将目录下的主页显示
			debug_error("st.st.mode=目录");
			path=path+"/index.html";
		}
		//S_IFDIR代表目录
		//S_IXUSR:文件所有者具可执行权限
		// S_IXGRP:用户组具可执行权限
		// S_IXOTH:其他用户具可读取权限 
		if ((st.st_mode & S_IXUSR) ||(st.st_mode & S_IXGRP) ||(st.st_mode & S_IXOTH)){
			debug_error("st.st.mode=可执行文件");
			cgi=true;
		}
	}

	if(cgi)
		exec(clientFd,method,path,params);
	else 
		returnFile2(clientFd,path);

	//因为http是短连接，所以需要一次请求完成后，断开连接.
	::close(clientFd);
}
void headers(int clientFd){
	char buf[1024]={0};
	strcpy(buf, "HTTP/1.0 200 OK\r\n");
	strcat(buf, SERVER_NAME);
	strcat(buf, "Content-Type: text/html\r\n");
	strcat(buf, "\r\n");
	send(clientFd, buf, strlen(buf),0);
}
void cat(int clientFd,ifstream& fs){  //发送文件内容
	string str;
	while(getline(fs,str)){
		int len=str.size();
		send(clientFd,str.c_str(),len,0);
		debug_error(str);
	}
	char buf[]="\r\n";
	send(clientFd,buf,2,0);
}
void cat2(int clientFd,int fd){
	char buf[1024]={0};
	int readLen=-1;
		while((readLen=read(fd,buf,1024))>0)
		{
			cout<<"read len="<<readLen<<endl;
			cout<<"buf len="<<strlen(buf)<<endl;
			int len=send(clientFd,buf,strlen(buf),0);
			cout<<"send len="<<len<<endl;
			if(len!=readLen)
				sleep(1);
			memset(buf,0,sizeof(buf));
		}
}
void returnFile(int clientFd,const string& path){
	int n;
	char buf[1024];

	while(n!=0&&strcmp("\n",buf))//因为返回静态文本，不需要http其余部分，所以清空read中所有数据
		n=getLine(clientFd,buf,1024);

	ifstream ifs;
	ifs.open(path);
	if(!ifs){
		debug_error("fs.open失败");
		notFound(clientFd);
	}
	else{
		headers(clientFd);  //添加响应头
		cat(clientFd,ifs);
	}
	ifs.close();
}
void returnFile2(int clientFd,const string& path){
	int n;
	char buf[1024];
	while(n!=0&&strcmp("\n",buf))//因为返回静态文本，不需要http其余部分，所以清空read中所有数据
		n=getLine(clientFd,buf,1024);

	int fd=open(path.c_str(),O_RDWR);
	if(fd<0){
		debug_error("fs.open失败");
		notFound(clientFd);
	}
	else{
		headers(clientFd);  //添加响应头
		cat2(clientFd,fd);
	}
	close(fd);
}
void cannot_execute(int client)  //无法执行cgi，所以是服务器原因，返回500状态
{
	char buf[1024];
	sprintf(buf, "HTTP/1.0 500 Internal Server Error\r\n");
	strcat(buf, "Content-type: text/html\r\n");
	strcat(buf, "\r\n");
	strcat(buf, "<P>Error prohibited CGI execution.\r\n");
	send(client, buf, strlen(buf), 0);
}
//对于Get：清空http报文的剩余部分， 设置paramsEnv环境变量
//对于Post：找出报文中的content-length部分， 清空http报文的请求头，请求头标，只留下post数据，， 设置contentEnv环境变量,从报文中读出post数据，并且存入cgiIn文件中

void bad_request(int client)
{
	char buf[1024];
	//发送400
	sprintf(buf, "HTTP/1.0 400 BAD REQUEST\r\n");
	strcat(buf, "Content-type: text/html\r\n");
	strcat(buf, "\r\n");
	send(client, buf,strlen(buf), 0);

	sprintf(buf, "<P>Your browser sent a bad request, ");
	strcat(buf, "such as a POST without a Content-Length.\r\n");
	send(client, buf, strlen(buf),0);
}
void exec(int clientFd,const string& method,const string& path,const string& params){
	int n=0;
	int len=1;
	int contentLength=-1; 
	int fd1=open("../file/cgiIn.txt",O_RDWR);  
	int fd2=open("../file/cgiOut.txt",O_RDWR);

	char methodEnv[255];
	char paramsEnv[255];
	char lengthEnv[255];
	struct stat st;

	//判断是否是可执行文件
	stat(path.c_str(),&st);
	if (!(st.st_mode & S_IXUSR)&&!(st.st_mode & S_IXGRP)){ 
		cannot_execute(clientFd);	
		return; 
	}
	//设置method环境变量
	sprintf(methodEnv,"method=%s",method.c_str());
	putenv(methodEnv);
	debug_value("methodEnv=",methodEnv);


	//如果method=get
	//清空recv中数据
	//设置paramsEnv环境变量，便于cgi从中取出数据
	if(method=="GET"){   
		char buf[1024];
		while(n>0&&strcmp("\n",buf))  //请求头，请求头标，空行全部读出
			n=getLine(clientFd,buf,sizeof(buf));

		//将参数送入paramsEnv环境变量
		//string paramsEnv="Params="+params;
		//putenv(const_cast<char*>(paramsEnv.c_str()));

		sprintf(paramsEnv,"params=%s",params.c_str());
		putenv(paramsEnv);
		debug_value("paramsEnv=",paramsEnv);
	}
	else if(method=="POST"){
		int n=1;
		char buf[1024];
		//将请求头和请求头标和空行读出,只留Post的数据下,并且从请求头标中取出content-length对应的值
		while(n>0&&strcmp("\n",buf)){   
			buf[15]='\0';
			if(!strcasecmp("Content-Length:",buf)){  
				debug_error("buf=Content-Length");
				//因为“Content-Length:” 字符串总共占15个字节，第16个字节就是实际的值
				contentLength=atoi(&buf[16]);
				debug_value("contentLength=",contentLength);
			}
			n=getLine(clientFd,buf,sizeof(buf));  
			debug_value("method=Post中，311行：buf=",buf,", n=",n);
		}
		if(contentLength==-1){ //如果没读到content-Length。说明request有错误，执行bad_request
			bad_request(clientFd);
			return ;
		}

		sprintf(lengthEnv,"Content-Length=%d",contentLength);//设置content-Length换变量
		putenv(lengthEnv);
		debug_value("lengthEnv=",lengthEnv);


		char data[1024];
		recv(clientFd,data,contentLength,0);  //取出content-length长度实际的post数据
		debug_value("post数据=",data);

		write(fd1,data,contentLength);//将数据存入cgiIn文件
		lseek(fd1,0,SEEK_SET);  //将cgiIn的文件指针还原到开头
	}

	//这里要使用fork生成子进程，让子进程执行脚本程序，
	//原因： execl函数执行后会覆盖原来的进程，会使得execl后代码无法执行,所以需要fork出子进程，让子进程执行,
	pid_t pid=fork();
	if(pid<0)
	{
		perror("fork()");
		exit(1);
	}
	else if(pid==0){  
		//保存stdin,stdout原来指向的打开文件表，便于更该stdin,stdout后还原
		int inFd=dup(0);
		int outFd=dup(1);

		//将stdin指向fd1所指的打开文件表，stdout指向fd2指向的打开文件表
		dup2(fd1,0);
		dup2(fd2,1);
		//执行动态文件
		execl(path.data(),path.data(),NULL);

		exit(1);
		//正常情况下应该按照如下方式还原stdin,stdouat，但execl执行后会覆盖代码进程代码段，使得原来进程销毁。从而不会执行
		//dup2(fd1,inFd);
		//dup2(fd2,outFd);
	}
	else {
		char headBuf[30]={0};
		sprintf(headBuf, "HTTP/1.0 200 OK\r\n");
		send(clientFd, headBuf, strlen(headBuf), 0);
		//等待子进程
		waitpid(pid,NULL,0);
		//因为cgi程序的结果被保存在fd2指向的文件中，所以从文件中取出data，发送给客户端
		//又因为执行完cgi程序后，读写指针被移动到了写的末尾，所以需要把指针重新移动到开头
		lseek(fd2,0,SEEK_SET);
		char fileData[1024]={0};
		while((len=read(fd2,fileData,1024))>0)
		{	
			cout<<"fileData="<<fileData<<endl;
			send(clientFd,fileData,len,0);
		}
		close(fd1);
		close(fd2);
	}
}


int init(int port){
	int serverFd=0;
	if((serverFd=::socket(PF_INET,SOCK_STREAM,0))<0)
	{
		perror("socket");
		exit(1);
	}
	sockaddr_in myaddr;
	memset(&myaddr,0,sizeof(myaddr));

	myaddr.sin_family=AF_INET;
	myaddr.sin_port=htons(port);
	myaddr.sin_addr.s_addr=htonl(INADDR_ANY);  //接手所有地址发来的连接

	if(bind(serverFd,(struct sockaddr*)&myaddr,sizeof(myaddr))<0){
		perror("bind");
		exit(0);
	}
	if(listen(serverFd,20)<0){
		perror("listen");
		exit(0);
	}
	return serverFd;
}
int main(){
	ThreadPool pool; //创建线程池
	pool.start(10);  //打开10个线程

	sockaddr_in clientaddr;

	int port=9999;
	socklen_t len=sizeof(clientaddr);
	int myFd=init(port);

	printf("httpd running on port %d\n", port);

	while(true){
		int clientFd=::accept(myFd,(struct sockaddr*)&clientaddr,&len);
		if(clientFd==-1)
		{
			perror("accept");
			exit(1);
		}
		//加入线程池，
		pool.run(std::bind(&readRequest,clientFd));
	}
	debug_error("未知原因退出");
	close(myFd);
	return 0;
}


