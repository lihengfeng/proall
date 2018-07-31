/*************************************************************************
	> File Name: ThreadSafeQueue.h
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Sun Dec 10 22:39:00 2017
 ************************************************************************/

#include<queue>
#include<iostream>
#include<memory>
#include<condition_variable.h>

using namespace std;
template<typename T>
class ThreadSafeQueue{
public:
	ThreadSafeQueue(){
	}

	ThreadSafeQueue(const ThreadSafeQueue& other){
		std::lock_guard<std::mutex> lock(mutex_);
		dataQueue=other.dataQueue;
	}

	ThreadSafeQueue& operator=(const ThreadSafeQueue& other)=delete; 

	bool empty() const{
		std::lock_guard<std::mutex> lock(mutex_);
		return dataQueue.empty();
	}
	size_t size() const{
		std::lock_guard<std::mutex> lock(mutex_);
		return dataQueue.size();
	}

	void push(const T& value){
		std::lock_guard<std::mutex> lock(mutex_);
		dataQueue.push(value);
		cond.notify_one();
	}
	bool tryPop(const T& value){
		std::lock_guard<std::mutex> lock(mutex_);
		if(dataQueue.empty()) //这里不能使用this.empty(),因为empty中也会获取锁，从而造成死锁
			return false;
		value=dataQueue.front();
		dataQueue.pop();
		return true;
	}
	
	std::shared_ptr<T> tryPop(){
		std::lock_guard<std::mutex> lock(mutex_);
		if(dataQueue.empty())
			return std::shared_ptr<T>();
		//throw empty_queue(); 
		std::shared_ptr<T> res( make_shared<T>(dataQueue.front()));
		dataQueue.pop();
		return res;
	}
	
	void waitPop(const T& value){
		std::unique_lock<std::mutex> lock(mutex_);
		cond.wait(lock,[]{return !dataQueue.empty()});
		value=dataQueue.front();
		dataQueue.pop();
	}
	std::shared_ptr<T> waitPop(){
		std::unique_lock<std::mutex> lock(mutex_);
		cond.wait(lock,[]{return !dataQueue.empty()});
		std::shared_ptr<T> res( make_shared<T>(dataQueue.front()));
		dataQueue.pop();
		return res;
	}

private:
	std::queue<T> dataQueue;
	std::condition_variable cond;
	std::mutex mutex_;

};
