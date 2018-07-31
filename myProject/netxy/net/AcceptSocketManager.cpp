/*************************************************************************
  > File Name: AcceptSocketManager.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Sat Nov 11 15:08:08 2017
 ************************************************************************/

#include<netxy/net/AcceptSocketManager.h>

#include <sys/socket.h>
using namespace std;

namespace netxy{
	namespace net{
		void AcceptSocketManager::doRead(){
			
			int	cd=::accept(fd,(struct sockaddr*)NULL,NULL);
			if(readCallback)
				readCallback();
			if (acceptCallback)
				acceptCallback(cd);
		};
	}
}

