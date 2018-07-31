#pragma once

#include<mutex>

class MutexGuard{
	MutexGuard(std::mutex& m):mutex_(m),tid(0){
		mutex_.lock();
	}

	~MutexGuard(){
		tid = 0;
		mutex_.unlock();
	}
	void lock(){
		tid = CurrentThread::tid();
		mutex_.lock();
	}
	void unlock(){
		mutex_.unlock();
		tid = 0;
	}
	private:
	friend class Condition;
	std::mutex& mutex_;
	int tid;
};
