/*************************************************************************
	> File Name: Manager.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Wed Sep  6 23:05:16 2017
 ************************************************************************/

#include<netxy/base/Cdebug.h>
#include<netxy/net/Manager.h>
#include<netxy/net/Epoller.h>

#include<iostream>
using namespace std;


namespace netxy{
namespace net{

	void Manager::updateEvent(int e){
			int tmp = e;
			int count = 0;
			while (count){
				if (tmp % 2 == 1)
					count++;
				tmp = tmp / 2;
			}
			if (count == 1)  addEvents(e);  //如果count==1，说明e中1只有一个，说明是为了添加该位上的1
			else if (count == 7) removeEvents(e);
			else std::cout << "event不符合规范" << std::endl;
	}

	void Manager::doEvent(){
			//std::cout << "doEvent() "<< std::endl;

			if (revents&(EPOLLIN | EPOLLPRI | EPOLLRDHUP)){
				doRead();
			}
			if (revents&EPOLLHUP){
				doPassvieClose();
			}
			if (isConnecting){
				if (revents&EPOLLOUT){
					if (writeCallback) writeCallback();
				}
			}
	}
	}
}

