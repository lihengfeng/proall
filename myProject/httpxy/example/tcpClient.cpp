/*************************************************************************
  > File Name: udpClient.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Fri Nov 17 16:17:04 2017
 ************************************************************************/
#include <unistd.h>  
#include <sys/types.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <errno.h>  
#include <string.h>  

#include<iostream>
using namespace std;

int main(){
	int sock;  
	//1.创建客户端的socket  
	if((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0){  
		perror("socket");  
		exit(EXIT_FAILURE);  
	}  

	struct sockaddr_in serveraddr;  	
	memset(&serveraddr,0,sizeof(serveraddr));

	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(9999);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");   //允许所有地址


	connect(sock,(struct sockaddr*)&serveraddr,sizeof(sockaddr));

	char buf[1024]={0};
//	char sendBuf[1024]="GET /index.html HTTP1.0\r\n"; 正确路径 Get请求无参数
//	char sendBuf[1024]="POST /register.py HTTP1.0\r\n";  正确路径可执行文件
//	char sendBuf[1024]="POST /register2.cgi HTTP1.0\r\n";  正确路径非可执行文件
//	char sendBuf[1024]="POST /register9.py HTTP1.0\r\n"; 非正确路径
	char sendBuf[1024]="GET /book.py?name=abc&author=123 HTTP1.0\r\n";  //Get请求，有参数
	strcat(sendBuf,"Content-Length: 10\r\n\r\n");
	strcat(sendBuf,"12345&6789"); 
	send(sock,sendBuf,strlen(sendBuf),0);
	while(true){
		buf[1025]='\0';
		int n=read(sock,buf,sizeof(buf));
		if(n==0){
			cout<<"服务端关闭了连接"<<endl;
			break;
		}
		else if(n>0){
			cout<<buf<<endl;
		}
		memset(buf,0,sizeof(buf));
	}
	::close(sock);
}

