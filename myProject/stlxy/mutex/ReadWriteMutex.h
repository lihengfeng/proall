/*************************************************************************
	> File Name: ReadWriteMutex.h
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Thu Nov 30 16:15:11 2017
 ************************************************************************/

#include<mutex>
#include<condition_variable>

using std::mutex;
using std::lock_guard;

class ReadWriteMutex{
public:
	ReadWriteMutex():readCount(0){
	}
	void readLock(){
		std::unique_lock<mutex> lock(mutex_);
		while(readCount<0)
			cond.wait(lock);
		++readCount;
	}
	void readUnLock(){
		std::lock_guard<mutex> lock(mutex_);
		--readCount;
		if(readCount==0)
			cond.notify_one();//唤醒一个写操作
	}
	void writeLock(){
		std::unique_lock<mutex> lock(mutex_);
		while(readCount!=0)
			cond.wait(lock);  //
		--readCount;
	}
	void writeUnLock(){
		std::lock_guard<mutex> lock(mutex_);
		//readCount++;

		readCount=0;//这里直接将readCount=0，可以让read和write都能有机会停止等待，
		cond.notify_all();//唤醒所有读和写操作
	}

private:
	std::mutex mutex_;
	std::condition_variable cond;  
	//=0.说明无线程使用， 
	//>0.代表有readCount个read线程同时使用，加了读锁 
	//<0.已经加了写锁
	int readCount=0;  
};
