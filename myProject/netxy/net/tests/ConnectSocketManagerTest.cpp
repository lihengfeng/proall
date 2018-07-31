/*************************************************************************
  > File Name: ConnectSocketManagerTest.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Sat Sep  2 17:56:24 2017
 ************************************************************************/
#include"../Manager.h"
#include"../ConnectSocketManager.h"


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
#include <fcntl.h>


#include<map>
#include<iostream>
using namespace std;
using namespace netxy;
using namespace netxy::base;
using namespace netxy::net;

void setNonBlock(int fd){
	int flags = fcntl(fd, F_GETFL, 0); 
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}


void cread(int fd){
	int rec_len;
	char rec_buf[50];	
		 rec_len=recv(fd,&rec_buf,32,0);
		if(rec_len==-1)
			cout<<"缓冲区没有数据"<<endl;
		else if(rec_len>0)
			cout<<"缓冲区有数据,rec_len="<<rec_len<<endl;
	rec_buf[rec_len]='\0';
	cout<<"rec="<<rec_buf<<endl;
}
void cwrite(int client_fd){
	char buf[32]="lihengfeng-wanghao";
	int send_len=strlen(buf);
	cout<<"send_len="<<send_len<<endl;
	int send_ret;
	send_ret=send(client_fd,&buf,send_len,0);
	cout<<"send_ret="<<send_ret<<endl;
	if(send_ret==0)
		cout<<"send失败"<<endl;
	else if(send_ret==EAGAIN)
		cout<<"send失败,空间不够"<<endl;
	else if(send_ret==send_len)
		cout<<"send完毕了把"<<endl;
	else 
		cout<<"send完全的失败"<<endl;
}

void passiveClose(){
		cout<<"收到关闭信号,别动关闭"<<endl;
}

int main(){
	typedef map<int,Manager*> ManagerMap;

	ManagerMap mm;
	Epoller ep;
	sockaddr_in client_addr;
	struct epoll_event ev,events[30];
	int epoll_fd=epoll_create(20);

	memset(&client_addr, 0, sizeof(client_addr));    //填充整个server_addr
	client_addr.sin_family=AF_INET;
	client_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	client_addr.sin_port=htons(9999);

	int	client_fd=socket(AF_INET,SOCK_STREAM,0);
	setNonBlock(client_fd);

	int ret = connect(client_fd, (struct sockaddr*)&client_addr, sizeof(client_addr));
	int err=(ret==0)?0:errno;
	switch(err){
		case 0:
			cout<<"之前已经连接成功"<<endl; break;
		case EINPROGRESS:
		case EINTR:
		case EISCONN:
			{
				cout<<"连接成功"<<endl;
				ConnectSocketManager* csm=new ConnectSocketManager(client_fd,&ep);
				csm->setReadCallback(std::bind(&cread,client_fd));
				//csm->setWriteCallback(std::bind(&cwrite,client_fd));
				csm->setPassiveCloseCallback(std::bind(&passiveClose));
				ev.data.fd=client_fd;
				ev.events=EPOLLIN|EPOLLOUT|EPOLLET;
				epoll_ctl(epoll_fd,EPOLL_CTL_ADD,client_fd,&ev);
				mm.insert({client_fd,csm});
				break;
			}
		default:
			cout<<"连接失败"<<endl;
			close(client_fd);
			return 0;
	}

	cwrite(client_fd);
	int j=0;
	while(1){
		j++;
		int n=epoll_wait(epoll_fd,events,30,500);
		std::cout<<"j="<<j<<std::endl;

		for(int i=0;i<n;i++){
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
		}
		sleep(1);
	}

	sleep(2);
	close(client_fd);

	client_fd=-1; //防止重复关闭
}
