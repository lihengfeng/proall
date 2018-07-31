/*************************************************************************
	> File Name: Httpxy.h
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Mon Nov 20 18:58:46 2017
 ************************************************************************/

#include<iostream>
using namespace std;

int main(){
	int sock;
	int clientFd;
	//指明ipv4，无连接的updsocket
	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0){  
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
		perror("bind");
		exit(1);
	}
	if(listen(sock,20)<0){
		perror("listen");
		exit(1);
	}
	if((clientFd=accept(sock,(struct sockaddr*)&clientaddr,sizeof(clientaddr)))<0){
		perror("accept");
		exit(1);
	}
	char buf[32];
	int n=read(clientFd,buf,32);


}


