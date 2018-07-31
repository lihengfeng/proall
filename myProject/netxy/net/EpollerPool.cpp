/*************************************************************************
  > File Name: EpollerPool.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Sat Nov 11 13:59:05 2017
 ************************************************************************/

#include<netxy/net/EpollerPool.h>
using namespace std;

namespace netxy{
	namespace net{
		void EpollerPool::init(int n){
			thread_pool.start(n);
			for (int i = 0; i < thread_count; i++){
				Epoller* epoller = new Epoller();  //这里用Epoller epoller是错误的.
				epoller_list.push_back(epoller);
				thread_pool.run(std::bind(&Epoller::loop, epoller));
			}

		}
		void EpollerPool::remove(){
			 ;
			for (std::vector<Epoller*>::iterator it = epoller_list.begin(); it != epoller_list.end(); it++)
				delete *it;
		}

		Epoller* EpollerPool::getNextEpoller(){
			 ;
			Epoller* ep= epoller_list[position];
			++position;
			if (position == epoller_list.size())
				position = 0;
			return ep;
		}
}
}




