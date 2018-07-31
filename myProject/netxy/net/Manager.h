#ifndef MANAGER_H
#define MANAGER_H

#include<netxy/base/Cdebug.h>

#include<iostream>

#include <functional>

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


#include <sys/epoll.h>


namespace netxy{
	namespace net{
		class Epoller;

		class Manager
		{
			public:
				typedef std::function<void()> EventCallback;
				//	typedef std::function<void(ConnectSocketManager *)> MessageCallback;

				Manager(int fid,Epoller* ep) :epoller(ep), fd(fid), events(0), revents(0){

				};
				Manager(const Manager& other) = delete;
				Manager& operator=(Manager& other) = delete;
				virtual ~Manager(){
				};
				virtual void close(){
					if(activeCloseCallback)
						activeCloseCallback();
					::close(fd);
				};

				virtual void doRead(){
					if (readCallback)
						readCallback();
				};
				virtual void doWrite(){
					if (writeCallback)
						writeCallback();
				}
				virtual void doPassvieClose(){
					if (passiveCloseCallback)
						passiveCloseCallback();
				};

				int getFd(){
					return fd;
				}
				void setEvents(int e){    //用于最开始生成Manager时设置
					events = e;
				}
				void addEvents(int e){   //添加，与e进行或，从而让添加的位变为1
					events=events | e;
				}
				void removeEvents(int e){   //删除，与e的非进行与，从而让删除的位变为0
					events = events&~e;
				}
				int getEvents(){
					return events;
				}
				void setRevents(int revt){
					revents = revt;
				}
				int getRevents(){
					return revents;
				}


				void setReadCallback(const EventCallback& cb){
					readCallback = cb;
				};
				void setWriteCallback(const EventCallback& cb){
					writeCallback = cb;
				};
				void setErrorCallback(const EventCallback& cb){
					errorCallback = cb;
				};
				void setPassiveCloseCallback(const EventCallback& cb){
					passiveCloseCallback= cb;
				};
				void setActiveCloseCallback(const EventCallback& cb){
					activeCloseCallback= cb;
				};
				void setConnectCallback(const EventCallback& cb){
					connectCallback = cb;
				};

				void doEvent();
				void updateEvent(int e);

			protected:
				const int k_none_event = 0;
				const int k_read_event = EPOLLIN | EPOLLPRI;
				const int k_write_event =EPOLLOUT;

				EventCallback readCallback;
				EventCallback writeCallback;
				EventCallback errorCallback;
				EventCallback passiveCloseCallback;
				EventCallback activeCloseCallback;
				EventCallback connectCallback;

				bool isConnecting =true;

				int fd;
				int events=0;
				int revents=0;

				Epoller* epoller;
		};
	}
}


#endif // !SOCKET_H
