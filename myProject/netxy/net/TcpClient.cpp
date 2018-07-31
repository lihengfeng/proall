/*************************************************************************
  > File Name: TcpClient.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Sat Nov 11 18:33:21 2017
 ************************************************************************/

#include<netxy/net/TcpClient.h>
#include<netxy/base/Cdebug.h>
#include<netxy/net/Manager.h>

#include <sys/epoll.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <malloc.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <stdarg.h>
#include <fcntl.h>

#include<memory>

using namespace std;
using namespace std::placeholders;

namespace netxy{
	namespace net{

		shared_ptr<ConnectSocketManager> TcpClient::connect(const char* ip,int port){
			sockaddr_in server_addr;
			memset(&server_addr, 0, sizeof(server_addr));    //填充整个server_addr
			server_addr.sin_family=AF_INET;
			server_addr.sin_addr.s_addr=inet_addr(ip);
			server_addr.sin_port=htons(port);

			int	client_fd=socket(AF_INET,SOCK_STREAM,0);
			int flags = fcntl(client_fd, F_GETFL, 0); 
			fcntl(client_fd, F_SETFL, flags | O_NONBLOCK);

			ConnectSocketManager* csm=nullptr;

			int ret = ::connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
			int err=(ret==0)?0:errno;
			switch(err){
				case 0:
					debug_error("之前已经连接成功i；");
					break;
				case EINPROGRESS:
				case EINTR:
				case EISCONN:
					csm=connecting(client_fd);
					break;
				case EAGAIN:
				case EADDRINUSE:
				case EADDRNOTAVAIL:
				case ECONNREFUSED:
				case ENETUNREACH:
					retry(client_fd);
					break;
				default:
					debug_error("connect fault");
					::close(client_fd);
					break;
			}
			shared_ptr<ConnectSocketManager> sp(csm,[](ConnectSocketManager*csm){  //这里还有点问题，暂时没解决方案。
					csm->close();		
					});
			return sp;
		}

		ConnectSocketManager* TcpClient::retry(int fd){
			debug_error("需要重连");
		}

		ConnectSocketManager* TcpClient::newConnectSocketManager(int fd){
			Epoller* ep = epool.getNextEpoller();
			ConnectSocketManager* csm = new ConnectSocketManager(fd, ep);
			csm->setCloseType(2);  //2代表半关闭型
			csm->setEvents(EPOLLIN|EPOLLHUP);
			csm->setPassiveCloseCallback(std::bind(&TcpClient::connectSocketPassiveClose, this,csm));

			if(messageCallback)
				csm->setMessageCallback(messageCallback);

			ep->addManager(csm);
			connect_map.insert(std::make_pair(fd, csm));
			return csm;
		}

		ConnectSocketManager* TcpClient::connecting( int fd){   //如果connect连接到并且返回EISCONN,就执行该局
			return newConnectSocketManager(fd);
		}


		void TcpClient::connectSocketPassiveClose(ConnectSocketManager* csm){   //被动的关闭connect连接，说明连接的对面关闭了
			cout<<"TcpClient::connectSocketPassiveClose"<<endl;
			ConnectSocketMap::iterator it= connect_map.find(csm->getFd());
			if (it != connect_map.end())
				connect_map.erase(it);
			delete csm;
		}

	}
}

