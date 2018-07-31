
#ifndef THREADPOLL_H
#define THREADPOLL_H


#include<assert.h>

#include<functional>
#include<string>
#include <deque>
#include <vector>
#include <map>
//线程相关
#include<thread>
#include<mutex>
#include<condition_variable>
#include <algorithm>
#include<memory>

#ifdef _WIN32  
#include <process.h>  
#define getpid _getpid  
#else  
#include <unistd.h>  
#endif  

using namespace std::placeholders;

class ThreadPool
{
	public:
		typedef std::function<void()> Task;
		typedef std::map<std::thread::id,std::string> ThreadNameMap;

		ThreadPool(){
		};
		explicit ThreadPool(int n):maxQueueSize(n){
		};

		//一般的析构函数需要处理的几点:
		//先释放资源
		//如果有需要delete的指针对象就delete
		//如果有需要处理的容器就处理容器
		//如果有正在运行的事务就等待事务完成处理

		~ThreadPool(){
			if(is_running)
				stop();
		};

		void setThreadInitCallback(const Task& cb){
			threadInitCallback = cb;
		}
		bool isFull() const{
			return (int)deque_.size()>= maxQueueSize;
		};

		void start(int threadNum);  
		void stop();
		void run(const Task& fun);

	private:
		Task getTask();
		void runInThread(int i);

		std::function<void()>  threadInitCallback;
		bool is_running = false;
		int maxQueueSize = 30;
		std::deque<Task> deque_;
		std::vector<std::shared_ptr<std::thread>> thread_list;
		std::vector<std::thread::id> tid_list;

		std::mutex mutex_;
		std::condition_variable_any no_empty;
		std::condition_variable_any no_full;
};

#endif
