/*************************************************************************
	> File Name: ThreadSafeSatack.h
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Sat Dec 16 14:16:31 2017
 ************************************************************************/

#include <exception>
#include<stack>
#include<iostream>
#include<mutex>
#include<memory>
#include<condition_variable>

class emptyStackError:public std::exception{
	public:
		const char* what() const throw(){
			return "stack empty!";
		}
};

template<typename T>
class ThreadSafeStack{
public:
	ThreadSafeStack(){
	}
	ThreadSafeStack(const ThreadSafeStack& rhs):mutex_(),cond(){
		std::lock_guard<std::mutex> lock(mutex_);
		dataStack=rhs.dataStack;
	}


	//禁用赋值运算符,这时为了保证this对象内mutex和condition_variable变量状态的正确性，
	ThreadSafeStack& operator=(const ThreadSafeStack& rhs)=delete;

	ThreadSafeStack(ThreadSafeStack&& rhs)=delete;
	ThreadSafeStack& operator=(ThreadSafeStack&& rhs)=delete;

	//对于empty和size函数，允许const的ThreadStack使用，所以把两个函数设置为const函数
	bool empty() const{
		std::lock_guard<std::mutex> lock(mutex_);
		return dataStack.empty();
	}
	size_t size() const{
		std::lock_guard<std::mutex> lock(mutex_);
		return dataStack.size();
	}

	void push(const T& value){
		std::lock_guard<std::mutex> lock(mutex_);
		dataStack.push(value);
		cond.notify_one();
	}
	//注意： 参数不能是const T&&, 因为value值要被改动
	void pop(T& value){
		std::lock_guard<std::mutex> lock(mutex_);
		if(dataStack.empty()) //这里不能使用this.empty(),因为this.empty中也会获取锁，从而造成锁的嵌套
			throw emptyStackError();
		value=dataStack.top();
		dataStack.pop();
	}
	
	std::shared_ptr<T> pop(){
		std::lock_guard<std::mutex> lock(mutex_);
		if(dataStack.empty())
			throw emptyStackError();
		std::shared_ptr<T> res(std::make_shared<T>(dataStack.top()));
		dataStack.pop();
		return res;
	}
	void waitPop(T& value){
		std::unique_lock<std::mutex> lock(mutex_);
		cond.wait(lock,[this]{return !dataStack.empty();});
		value=dataStack.top();
		dataStack.pop();
	}
	std::shared_ptr<T> waitPop(){
		std::unique_lock<std::mutex> lock(mutex_);
		cond.wait(lock,[this]{return !dataStack.empty();});
		std::shared_ptr<T> res(std::make_shared<T>(dataStack.top()));
		dataStack.pop();
		return res;
	}
private:
	std::stack<T> dataStack;
	std::condition_variable cond;
	std::mutex mutex_;
};
