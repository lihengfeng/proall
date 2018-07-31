/*************************************************************************
  > File Name: Epoller.h
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Tue Sep  5 11:14:08 2017
 ************************************************************************/

#ifndef  EPOLL_H
#define EPOLL_H

#include<netxy/net/TimeQueue.h>
#include<netxy/base/TimeStamp.h>

#include<sys/epoll.h>
#include<assert.h>

#include<iostream>
#include<map>
#include<vector>
#include<thread>
#include<mutex>
#include<functional>


#define ADD 1
#define DEL 2
#define MOD 3

using namespace std;
namespace netxy{
namespace net{

	class Manager;

	class Epoller{
	public:
		typedef std::function<void()>  Function;
		typedef map<int,Manager*> ManagerMap;

		typedef std::lock_guard<std::mutex> LockGuard; 

		Epoller();
		Epoller(const Epoller* other)=delete;
		Epoller& operator=(Epoller* other)=delete;

		void setTimeManager();

		void setTid(){
			tid=std::this_thread::get_id();
			//Debug_value("setTid() tid=",tid);
		}
		bool  updateEvents(Manager *m,int op);
		void addManager(Manager* m);
		void removeManager(Manager* m);
		void updateManager(Manager* m);

		bool isInLoopThread(){
			return tid==std::this_thread::get_id();
		}
		void runInLoopThread(const Function& fun);
		void addQueueFunctor(const Function& fun);

		void doQueueFunctors();

		void loop();
		
		void runInTime(base::TimeStamp,const Function& fun);
		void runInAfter(int,const Function& fun);
		void runInEvery(base::TimeStamp, const Function& fun,int);

		void weakup(){};
	private: 
		std::thread::id tid; 
		std::mutex mutex_;

		bool isCallQueueFunctors=false;
		int epoll_fd;

		ManagerMap mm;
		std::vector<Function> queue_functors;//保存所有外部线程的函数

		TimeQueue time_queue;
	};
}
}

#endif
