#ifndef EPOLLERPOOL_H
#define EPOLLERPOOL_H

#include<netxy/base/ThreadPool.h>

#include<netxy/net/Epoller.h>

#include<thread>
#include<vector>

using namespace netxy::base;

namespace netxy{
	namespace net{
		class EpollerPool{
			public:
				EpollerPool(){
					init(10);
				}
				explicit EpollerPool(int n):thread_count(n){
					init(n);
				}
				~EpollerPool(){
					remove();
				}
				void init(int);
				void remove();
				Epoller* getNextEpoller();
			private:
				int thread_count=10;   //如果要在类内给静态赋初始值，必须把静态变量声明为const或者constext
				int position=0;     
				ThreadPool thread_pool;
				std::vector<Epoller*> epoller_list;
		};
	}
}


#endif // !EPOLLERPOLL_H


