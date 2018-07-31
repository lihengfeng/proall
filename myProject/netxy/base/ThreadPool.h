
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
#include <memory>

#ifdef _WIN32  
#include <process.h>  
#define getpid _getpid  
#else  
#include <unistd.h>  
#endif  


using namespace std;
using namespace std::placeholders;

namespace netxy
{
	namespace base{
		class ThreadPool
		{
		public:
			typedef std::function<void()> Task;
			typedef std::map<thread::id,string> ThreadNameMap;

			ThreadPool(){
			};
			explicit ThreadPool(int n):maxQueueSize(n){
			};


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
			const int maxQueueSize = 30;

			std::deque<Task> deque_;
			std::vector<shared_ptr<thread>> thread_list;
			std::vector<std::thread::id> tid_list;

			std::mutex mutex_;
			std::condition_variable_any no_empty;
			std::condition_variable_any no_full;
		};
	}
}

#endif
