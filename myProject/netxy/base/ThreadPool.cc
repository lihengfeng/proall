#include"ThreadPool.h"
#include"Cdebug.h"

#include"CountDownLatch.h"


namespace netxy{
	namespace base{

			void ThreadPool::start(int threadNum){  //startʱ���뱣֤thread_listΪ�գ���ֹ�������е�thread_list.
				assert(thread_list.empty());
				assert(threadNum > 0);
				is_running = true;
				thread_list.reserve(threadNum);
				for (int i = 0; i < threadNum; i++){
					std::thread* t=new std::thread(std::bind(&ThreadPool::runInThread, this,i));
					thread_list.push_back(t);
				}
			};
			void ThreadPool::stop(){
				{
					std::lock_guard<std::mutex> lock(mutex_);
					is_running = false;
					no_empty.notify_all();   //�����̵߳�deque_empty�ȴ�.��Ϊ�����֪ͨ���̻߳���Ϊ�ȴ����޷����е�while(is_running)��䣬�Ӷ��޷�����.
				}
				std::for_each(thread_list.begin(),thread_list.end(),std::bind(&std::thread::join, _1));   //ִ��join�������ȷ������Դ��
			};

			// Could block if maxQueueSize > 0
			void ThreadPool::run(const Task& fun){
				if (thread_list.empty()){
					debug_error("thread_list is empty, do fun()");
					fun();
				}
				else{
					std::lock_guard<std::mutex> lock(mutex_);
					while (isFull()){
						no_full.wait(mutex_);
					}
					deque_.push_back(fun);
					no_empty.notify_one();
					//debug_error("add succeed, notify_one()");
				}
			};
			void ThreadPool::runInThread(int i){
				thread::id id_=std::this_thread::get_id();
				tid_list.push_back(id_);
				if (threadInitCallback)
					threadInitCallback();
				while (is_running){
					Task task = getTask();
					if (task){   //ΪʲôҪ�ж��Ƿ�Ϊ�գ���Ϊtake������is_running���ܻ᷵�ؿ�task����;
						task();
					}
					else
						debug_error("getTask��ÿյ�task.");
				}
				debug_error("this thread stop");
			};
			ThreadPool::Task ThreadPool::getTask(){
				std::lock_guard<std::mutex> lock(mutex_);
				while (deque_.empty() && is_running)   //��deque_Ϊ�գ���is_runningʱ����Ҫ�ȴ�.
				{
					no_empty.wait(mutex_);   //�ȴ��ǿ�ʱ�Ż���
				}
				Task task;
				if (!deque_.empty()){   //�����ٴμӸ��ж�����Ϊѭ����������Ϊis_running�����ģ�������deque��Ϊ��������
					task = deque_.front();
					deque_.pop_front();
					no_full.notify_one();   //֪ͨdeque���������������������le.
				}
				return task;
			};
	}
}

