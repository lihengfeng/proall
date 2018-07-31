/*************************************************************************
	> File Name: ../Epoller.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Wed Sep  6 23:21:44 2017
 ************************************************************************/

#include<netxy/net/Epoller.h>
#include<netxy/net/Manager.h>
#include<netxy/base/Cdebug.h>

#include<iostream>
#include<vector>

using namespace std;

namespace netxy{
namespace net{

		Epoller::Epoller():time_queue(){
			epoll_fd=epoll_create(500);
			setTimeManager();
		}
		void	Epoller::setTimeManager(){
			 ;
		    int time_fd=time_queue.getFd();
		  //  cout<<"time_fd="<<time_fd<<endl;
			Manager* m=new Manager(time_fd,this);
			m->setReadCallback(std::bind(&TimeQueue::doTimeOutEvent,&time_queue));
			m->setEvents(EPOLLIN|EPOLLHUP);
			addManager(m);
			 ;
		}

		bool  Epoller::updateEvents(Manager *m,int op){
			 ;
			assert(m!=nullptr);
			int ret=0;
			bool result=false;
			struct epoll_event ev;
			int fd=	m->getFd();
			int events=m->getEvents();
			ev.data.fd=fd;
			ev.events=events;
			switch(op){
				case 1:
					ret=epoll_ctl(epoll_fd,EPOLL_CTL_ADD,fd,&ev);
					break;
				case 2:
					ret=epoll_ctl(epoll_fd,EPOLL_CTL_DEL,fd,&ev);
					break;
				case 3:
					ret=epoll_ctl(epoll_fd,EPOLL_CTL_MOD,fd,&ev);
					break;
				default: 
					debug_error("op 的输入不符合规则");
					break;
			}
			if(!ret){
				result=true;
			}
			else
			{
				if(op==1) 
					cout<<"    epoll_ctl_add  失败";
				else if(op==2)
					cout<<"    epoll_ctl_del 失败 ";
				else if(op==3)
					cout<<"    epoll_ctl_mod  失败";
			}
			 ;
			return result;
		}
		void Epoller::addManager(Manager* m){
			 ;
			bool r=updateEvents(m,ADD);
			if(r){
				int fd=	m->getFd();
				mm.insert({fd,m});
			//	debug_error("addManager成功");
			}
			else
				debug_error("addManager失败");
			 ;
		}
		void Epoller::removeManager(Manager* m){   //addManager 与 removeManager不会产生线程不安全
			 ;
			bool r=updateEvents(m,DEL);
			if(r){
				int fd=	m->getFd();
				ManagerMap::iterator it=mm.find(fd);
				mm.erase(it);
			}
			else
				debug_error("removeManager失败");
			 ;
		}
		void Epoller::updateManager(Manager* m){
			 ;
			bool r=updateEvents(m,MOD);
			if(r){
				int fd=	m->getFd();
				ManagerMap::iterator it=mm.find(fd);
				mm.erase(it);
			//	debug_error("updateManager成功");
			}
			else
				debug_error("updateManager失败");
			 ;
		}

		void Epoller::runInLoopThread(const Function& fun){
			 ;
			if(isInLoopThread()){
				fun();
			}
			else{
				debug_error("isInLoopThread=false,需要放入addQueue执行");
				addQueueFunctor(fun);
			}
			 ;
		}

		void Epoller::addQueueFunctor(const Function& fun){
			 ;
			{
				LockGuard lock(mutex_);
				queue_functors.push_back(fun);
			}
			if(!isInLoopThread())
				weakup();
			 ;
		}
		void Epoller::doQueueFunctors(){
			 ;
			if(queue_functors.empty()){
				debug_error("queue为空，退出");
				 ;
				return ;
			}
			std::vector<Function> local_functors;    //新建一个空的，和pending交换后，pengding也会变为空.
			{
				LockGuard lock(mutex_);
				local_functors.swap(queue_functors);
			}
			isCallQueueFunctors=true;
			for(int i=0;i<local_functors.size();++i)
			{
				//Debug_value("for循环中i=",i);

				local_functors[i]();
			}
			 ;
		}

		void  Epoller::loop(){
		//	debug_error("进入loop()");
			setTid();
			int n;
			struct epoll_event events[30];
			while(true){
				n=epoll_wait(epoll_fd,events,30,500);
			//	if(n==0)
					//debug_error("epoll_wait返回的n=0");
				for(int i=0;i<n;i++)
				{
				//	Debug_value("在loop内for循环中 i=",i);
					int fd=events[i].data.fd;
					int es=events[i].events;
					ManagerMap::iterator it=mm.find(fd);
					if(it!=mm.end()){
						it->second->setRevents(es);
						it->second->doEvent();
					}
					else 
						debug_value("没有找到fd,该fd=",fd);
				}
				if(!queue_functors.empty())
					doQueueFunctors();
			}
			debug_error("离开loop()");
		}

		void Epoller::runInTime(base::TimeStamp ts,const Function& fun){
			time_queue.addTime(ts,fun);
		}
		void Epoller::runInAfter(int seconds,const Function& fun){
			base::TimeStamp ts;
			ts.addSeconds(seconds);
			time_queue.addTime(ts,fun);
		}
		void Epoller::runInEvery(base::TimeStamp ts,const Function& fun,int delaySeconds){
			time_queue.addTime(ts,fun,delaySeconds);
		}
}
}
