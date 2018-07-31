
#ifndef THREADPOLL_H
#define THREADPOLL_H


#include<assert.h>

#include<functional>
#include<string>
#include <deque>
#include <vector>
#include <map>
//�߳����
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

		//һ�������������Ҫ����ļ���:
		//���ͷ���Դ
		//�������Ҫdelete��ָ������delete
		//�������Ҫ����������ʹ�������
		//������������е�����͵ȴ�������ɴ���

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
