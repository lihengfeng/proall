/*************************************************************************
  > File Name: TcpServer.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Sat Nov 11 20:14:03 2017
 ************************************************************************/

#include<netxy/net/TcpServer.h>
using namespace std;

namespace netxy{
	namespace net{

		void TcpServer::listen(int port){   //监听本地的port端口
			struct sockaddr_in server_addr;
			memset(&server_addr,0,sizeof(server_addr));
			server_addr.sin_family=AF_INET;
			server_addr.sin_addr.s_addr=htonl(INADDR_ANY);  //获取本机的ip地址
			server_addr.sin_port=htons(port);

			int sd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
			if (sd < 0)
			{
				debug_error("创建accpcket出错了,跳出");
				exit(0);
			}
			debug_value("bind",port);

			int ret = ::bind(sd, (struct sockaddr*)&server_addr, sizeof(server_addr));
			if (::listen(sd,20) ==-1){
				printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);
				exit(0);
			}

			//AcceptSocketManager* as = createAccpetSocketManager(sd);
			AcceptSocketManager* as = new AcceptSocketManager(sd,epoller);
			as->setEvents(EPOLLIN|EPOLLHUP);
			as->setAcceptCallback(std::bind(&TcpServer::acceptSocketRead,this,_1));
			as->setActiveCloseCallback((std::bind(&TcpServer::acceptSocketActiveClose, this, as)));
			epoller->addManager(as);
			accept_map.insert({ sd, as });
		};

		void TcpServer::shutdown(){
			for (AcceptSocketMap::iterator it = accept_map.begin(); it != accept_map.end(); it++)
			{
				AcceptSocketManager* as = it->second;
				as->close();
			}
			for (ConnectSocketMap::iterator it = connect_map.begin(); it != connect_map.end(); it++)
			{
				ConnectSocketManager* csf = it->second;
				csf->close();
			}
		};	 

		void TcpServer::doTimeWheel(){  //线程问题，1 time_wheel++完，其他线程获取刚加的time_wheel，2 这里map删除，其他地方进行添加. 
			isDoingTimeWheel=true;
			time_wheel_index = (++time_wheel_index) % 20;
			debug_error("clear index=",time_wheel_index);
			time_wheel[time_wheel_index].clear();
			isDoingTimeWheel=false;
		}

		void TcpServer::acceptSocketRead(int fd){
			int index=isDoingTimeWheel? time_wheel_index-1:time_wheel_index;   //通过isDoingTime，来防止误删除.
			debug_error("index=",time_wheel_index);
			Epoller* ep = pool.getNextEpoller();
			ConnectSocketManager* csm =new ConnectSocketManager(fd,ep);
			csm->setCloseType(1);  //调用close后读端和写端全部关闭
			csm->setEvents(EPOLLIN|EPOLLHUP);
			//设置callback
			csm->setReadCallback(std::bind(&TcpServer::connectSocketRead, this, csm));
			csm->setPassiveCloseCallback(std::bind(&TcpServer::connectSocketPassiveClose,this,fd));
			if(messageCallback)
				csm->setMessageCallback(messageCallback);
			csm->setTimeWheelIndex(index);
			entry.setConnectSocketManager(csm);
			entry.setIndex(index);
			time_wheel[index].push_back(entry);
			ep->addManager(csm);
			{
				LockGuard lock(mutex_);
				connect_map.insert({fd,csm});
			}
		}
		void TcpServer::acceptSocketActiveClose(AcceptSocketManager* as){      //主动的关闭accept所要做的事情,
			AcceptSocketMap::iterator it=accept_map.find(as->getFd());
			if (it!=accept_map.end())
			{	accept_map.erase(it);
				debug_error("找到对应的fd了，删除");
			}
			else
				debug_error("没有找到对应的fd了，");
		}
		void TcpServer::connectSocketRead(ConnectSocketManager* csm){    //这里就是当有connectRead事件时，就更新该connectFd的timeWheel，
			int index=isDoingTimeWheel? time_wheel_index-1:time_wheel_index;
			entry.setConnectSocketManager(csm);
			entry.setIndex(index);
			time_wheel[index].push_back(entry);
			//csm->setTimeWheelIndex(time_wheel_index);   //会出现线程不安全的状况。因为可能执行entry时tiem_index=1.但是当执行csm->setTime().时，time_index在其他线程中加1了
			csm->setTimeWheelIndex(index);
			entry.setIndex(100);
		}
		void TcpServer::connectSocketPassiveClose(int sd){   //被动的关闭connect连接，说明连接的对面关闭了
			 ;
			{	
				LockGuard lock(mutex_);
				ConnectSocketMap::iterator it = connect_map.find(sd);
				if (it != connect_map.end()){
					connect_map.erase(it);
					debug_error("找到对应的fd了，删除");
				}
				else 
					debug_error("没有找到对应的fd");
			}
		}


	}
}


