/*************************************************************************
	> File Name: udpServer.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Fri Nov 17 16:17:11 2017
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
	//指明ipv4，无连接的updsocket
	if((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0){  
		perror("socket");  
		exit(EXIT_FAILURE);  
	}  
	struct sockaddr_in myaddr;  	
	struct sockaddr_in clientaddr;  	

	memset(&myaddr,0,sizeof(myaddr));
	memset(&clientaddr,0,sizeof(clientaddr));
	//需要获取sockaddr_in的长度，在revcfrom中使用
	socklen_t cliLen;

	myaddr.sin_family=AF_INET;
	myaddr.sin_port=htons(9999);
	myaddr.sin_addr.s_addr=htonl(INADDR_ANY);   //允许所有地址发送到这个socket

	//绑定,指明socket的端口和地址，同时告诉接受哪些地址的数据
	if(bind(sock,(struct sockaddr*)&myaddr, sizeof(myaddr))<0){
		perror("bind fauler");
		exit(0);
	}

	char buf[128]={0};

	cliLen=sizeof(clientaddr);

	while(true){
		printf("waiting for a packet...\n");
		//从sock取出数据到buffer,
		int n=recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr*)&clientaddr,&cliLen);

		if(n==-1){
			perror("revcfrom");
			exit(0);
		}
		else if(n>0){
			printf("clientaddr.sin_addr= %s \n",inet_ntoa(clientaddr.sin_addr));
			fputs(buf,stdout);
		}
		memset(buf,0,sizeof(buf));
	}
	::close(sock);
}
