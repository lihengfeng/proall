/*************************************************************************
	> File Name: testCondition.cpp
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Sun Dec 10 21:26:05 2017
 ************************************************************************/

#include<iostream>
#include<queue>
template<typename T>
class ThreadSafeQueue{
public:

	ThreadSafeQueue(){
	}

	bool empty(){
	}
	size_t size(){
	}
	T front(){
	}
	
	void push(const T& t){
	}

	bool tryPop(const T& t){
	}
	std::shared_ptr<T> tryPop(){
	}

	void waitPop(const T& t){
	}
	std::shared_ptr<T> waitPop(){
	}

private:
	std::mutex mutex_;
	std::condition_variable<std::mutex> cond;
	std::unqiue_mutex<std::mutex> lock();
};
int main(){
}
