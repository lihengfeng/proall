/*************************************************************************
  > File Name: ThreadPool.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Thu Nov  9 16:34:32 2017
 ************************************************************************/

#include"ThreadPool.h"
#include<iostream>

using namespace std; 

void ThreadPool::start(int threadNum){  //start时必须保证thread_list为空，防止覆盖已有的thread_list.
	assert(thread_list.empty());
	assert(threadNum > 0);
	is_running = true;
	thread_list.reserve(threadNum);
	for (int i = 0; i < threadNum; i++){
		std::thread* t=new std::thread(std::bind(&ThreadPool::runInThread, this,i));
		shared_ptr<thread> sp(t);
		thread_list.push_back(sp);
	}
};
void ThreadPool::stop(){
	{
		std::lock_guard<std::mutex> lock(mutex_);
		is_running = false;
		no_empty.notify_all();   //结束线程的deque_empty等待.因为如果不通知，线程会因为等待而无法运行到while(is_running)语句，从而无法结束.
	}
	std::for_each(thread_list.begin(),thread_list.end(),std::bind(&std::thread::join, _1));   //执行join后才能正确回收资源。
};

// Could block if maxQueueSize > 0
void ThreadPool::run(const Task& fun){
	if (thread_list.empty()){
		fun();
	}
	else{
		std::lock_guard<std::mutex> lock(mutex_);
		while (isFull()){
			no_full.wait(mutex_);
		}
		deque_.push_back(fun);
		no_empty.notify_one();
	}
};
void ThreadPool::runInThread(int i){
	thread::id id_=std::this_thread::get_id();
	tid_list.push_back(id_);
	if (threadInitCallback)
		threadInitCallback();
	while (is_running){
		Task task = getTask();
		if (task){   //为什么要判断是否为空？因为take中碰到is_running可能会返回空task（）;
			task();
		}
		else
			cout<<"getTask获得空的task."<<endl;
	}
		cout<<"this thread stop"<<endl;
};
ThreadPool::Task ThreadPool::getTask(){
	std::lock_guard<std::mutex> lock(mutex_);
	while (deque_.empty() && is_running)   //当deque_为空，且is_running时才需要等待.
	{
		no_empty.wait(mutex_);   //等待非空时才唤醒
	}
	Task task;
	if (!deque_.empty()){   //这里再次加个判断是因为循环可能是因为is_running跳出的，并不是deque不为空跳出。
		task = deque_.front();
		deque_.pop_front();
		no_full.notify_one();   //通知deque区不满，可以往里面添加le.
	}
	return task;
};
