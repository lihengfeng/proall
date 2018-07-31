/*************************************************************************
  > File Name: tcpServer.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Thu Nov 23 20:39:06 2017
 ************************************************************************/
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
void headers(int clientFd){
	char buf[1024]={0};
	strcpy(buf, "HTTP/1.0 200 OK\r\n");
	strcat(buf, "Content-Type: text/html\r\n");
	strcat(buf, "\r\n");
	send(clientFd, buf, strlen(buf),0);
}
void cat(int fd,string& path){  //发送文件内容
	ifstream fs(path);
	string str;
	if(fs){
		while(getline(fs,str)){
			int len=str.size();
			send(fd,str.c_str(),len,0);
		}
		char buf[]="\r\n";
		send(fd,buf,2,0);
	}
	else {
		cout<<"fs.open失败"<<endl;
	}
	fs.close();
}
int main(){
	char buf[1024]={0};
	sockaddr_in clientaddr;
	int port=9999;
	socklen_t len=sizeof(clientaddr);
	int myFd=init(port);

	printf("httpd running on port %d\n", port);

	int clientFd=::accept(myFd,(struct sockaddr*)&clientaddr,&len);
	while(true){
		read(clientFd,buf,sizeof(buf));
		headers(clientFd);
		string path="../file/index.html";
		cat(clientFd,path);
		memset(buf,0,1024);
	}
	debug_error("未知原因退出");
	close(myFd);
	close(clientFd);
	return 0;
}

/*
   void returnFile(int fd,const string& path){
   int n;
   char buf[1024];

   while(n!=0&&strcmp("\n",buf))//因为返回静态文本，不需要http其余部分，所以清空read中所有数据
   n=getLine(fd,buf,1024);

   ifstream ifs;
   ifs.open(path);
   if(!ifs){
   debug_error("fs.open失败");
   notFound(fd);
   }
   else{
   headers(fd);  //添加响应头
   cat(fd,ifs);  //发送文件内容
   }
   ifs.close();
   }
   */

