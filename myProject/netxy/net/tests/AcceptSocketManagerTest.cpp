/*************************************************************************
  > File Name: AcceptSocketManagerTest.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Sat Sep  2 20:57:19 2017
 ************************************************************************/
#include"../Epoller.h"
#include"../AcceptSocketManager.h"

#include <sys/epoll.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <malloc.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <stdarg.h>
#include <fcntl.h>


#include <iostream>

#include<map>
using namespace std;
using namespace netxy;
using namespace netxy::base;
using namespace netxy::net;

int client_fd;
struct sockaddr_in client_addr;

void setNonBlock(int fd){
	int flags = fcntl(fd, F_GETFL, 0); 
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);
};


void createConnect(int fd,int epoll_fd){
	struct epoll_event ev;	
	client_fd=accept(fd,(struct sockaddr*)NULL,NULL);
	if(client_fd<0)
		cout<<"accpet失败,client_fd="<<client_fd<<endl;
	else if(client_fd>0)
	{
		cout<<"accpet完成了,client_fd="<<client_fd<<endl;
		ev.data.fd=client_fd;
		ev.events=EPOLLIN|EPOLLOUT|EPOLLET;
		epoll_ctl(epoll_fd,EPOLL_CTL_ADD,client_fd,&ev);
	}
}

int createListen(int port){
	struct sockaddr_in server_addr;
	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);  //获取本机的ip地址
	server_addr.sin_port=htons(port);

	int fd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	cout<<"bind()"<<endl;
	bind(fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	cout<<"listen()"<<endl;
	listen(fd,20);
	return fd;
}
void setEpollEvent(int epoll_fd,int event_fd,int events){
	struct epoll_event ev;	
	ev.data.fd=event_fd;
	ev.events=events;
	epoll_ctl(epoll_fd,EPOLL_CTL_ADD,event_fd,&ev);
}

int main(){
	typedef	std::map<int,Manager*> ManagerMap;

	struct epoll_event ev,events[30];
	char rec_buf[32];

	
	Epoller* ep;
	ManagerMap mm;

	int	epoll_fd=epoll_create(100);	

	int server_fd=createListen(9999);

	setEpollEvent(epoll_fd,server_fd,EPOLLIN);

	AcceptSocketManager* asm1=new AcceptSocketManager(server_fd,ep);
	asm1->setReadCallback(std::bind(&createConnect,server_fd,epoll_fd));
	mm.insert({server_fd,asm1});


	for(int j=0;j<100;j++){
		int n=epoll_wait(epoll_fd,events,30,500);
		std::cout<<"j="<<j<<std::endl;

		for(int i=0;i<n;i++)
		{
			std::cout<<"i="<<i<<std::endl;
			int fd=events[i].data.fd;
			int rev=events[i].events;

			std::cout<<"fd="<<fd<<std::endl;
			std::cout<<"rev="<<rev<<std::endl;

			ManagerMap::iterator it=mm.find(fd);
			if(it!=mm.end()){
			 it->second->setRevents(rev);
			 it->second->doEvent();
			}
			if(fd==client_fd){
				int rec_len=
					recv(client_fd,rec_buf,32,0);
				rec_buf[rec_len]='\0';
				cout<<"rec_buf="<<rec_buf<<endl;
				char send_buf[50]="会送消息";
				send(client_fd,&send_buf,50,0);
				sleep(2);
				close(client_fd);
			}
		}
		sleep(2);
	}

	close(server_fd);
}

