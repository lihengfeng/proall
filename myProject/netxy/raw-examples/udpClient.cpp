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
	if((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0){  
		perror("socket");  
		exit(EXIT_FAILURE);  
	}  

	struct sockaddr_in serveraddr;  	
	memset(&serveraddr,0,sizeof(serveraddr));

	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(9999);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");   //允许所有地址

	char buf[128]={0};

	while( fgets(buf,sizeof(buf),stdin)!=NULL ){
		
		//向serveraddr的端口发送数据, 
		//sendto中间 加 0 不知道干啥的
		sendto(sock,buf,sizeof(buf),0,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

		memset(buf,0,sizeof(buf));
	}
	::close(sock);
}

