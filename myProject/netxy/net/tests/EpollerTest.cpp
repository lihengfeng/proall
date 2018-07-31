/*************************************************************************
  > File Name: AcceptSocketManagerTest.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Sat Sep  2 20:57:19 2017
 ************************************************************************/
#include"../AcceptSocketManager.h"
#include"../ConnectSocketManager.h"
#include"../Epoller.h"
#include"../EpollerPool.h"

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
using namespace std::placeholders;

using namespace netxy;
using namespace netxy::base;
using namespace netxy::net;

int client_fd;
struct sockaddr_in client_addr;

void fun1(){
	debug_error("执行fun1");	
}
void fun2(){
	debug_error("执行fun2");	
}
void fun3(){
	debug_error("执行fun3");	
}
void setNonBlock(int fd){
	int flags = fcntl(fd, F_GETFL, 0); 
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);
};
int k=1;

void showMessage(ConnectSocketManager* csm,Epoller* ep){
	if(!csm->in_buffer.empty()){
		cout<<"调用第k次="<<k<<endl;
		cout<<"in_buffer="<<csm->in_buffer.readAll()<<endl;
		csm->in_buffer.clear();
		string str="llllllllllaaaaaaaaaaa";
		csm->send(str);
		ep->runInLoopThread(&fun2);
		ep->runInAfter(5,&fun3);
		ep->runInAfter(15,&fun2);
		ep->runInAfter(3,&fun1);
		k++;
	}
}

void createConnect(int fd,EpollerPool* epool,Epoller* ep2 ){
	struct epoll_event ev;	
	client_fd=accept(fd,(struct sockaddr*)NULL,NULL);
	if(client_fd<0)
		cout<<"accpet失败,client_fd="<<client_fd<<endl;
	else if(client_fd>0)
	{
		cout<<"accpet完成了,client_fd="<<client_fd<<endl;
		Epoller* ep=epool->getNextEpoller();
		ConnectSocketManager* csm=new ConnectSocketManager(client_fd,ep);
		csm->setMessageCallback(std::bind(&showMessage,_1,ep2));
		csm->setEvents(EPOLLIN|EPOLLHUP);
		ep->addManager(csm);
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
//下一次要改动某个使用比较的多名字，需要在改动前用*查找
int main(){
	EpollerPool epool;

	struct epoll_event ev,events[30];
	char rec_buf[32];


	Epoller* ep=epool.getNextEpoller();


	int server_fd=createListen(9999);


	AcceptSocketManager* asm1=new AcceptSocketManager(server_fd,ep);
	asm1->setReadCallback(std::bind(&createConnect,server_fd,&epool,ep));
	asm1->setEvents(EPOLLIN|EPOLLHUP);

	ep->addManager(asm1);

	sleep(4);
	ep->runInLoopThread(&fun1);

	ep->loop();

	close(server_fd);
}

