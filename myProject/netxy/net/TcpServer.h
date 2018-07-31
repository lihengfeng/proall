#ifndef TCPSERVER_H
#define TCPSERVER_H

#include<netxy/base/TimeStamp.h>
#include<netxy/net/Epoller.h>
#include<netxy/net/EpollerPool.h>
#include<netxy/net/Manager.h>
#include<netxy/net/AcceptSocketManager.h>
#include<netxy/net/ConnectSocketManager.h>


#include<functional>
#include<map>
#include<vector>
#include<thread>
#include<mutex>



using namespace std;
using namespace netxy::base;

namespace netxy{
	namespace net{


		//这时实现time_heel的关键模板。细节之后填充
		class Entry{
			public:
				Entry(){

				}
				Entry(ConnectSocketManager* addr, size_t n) :csm(addr), index(n){
				}
				Entry(const Entry& other ):csm(other.csm),index(other.index){
				}

				~Entry(){
					if (csm->getTimeWheelIndex() == index)
					{
						debug_error("Entry中csm超时，准备close");
						csm->close();
					}
				}
				void setConnectSocketManager(ConnectSocketManager* addr){
					csm = addr;
				}
				void setIndex(size_t  n){
					index = n;
				}

			private:
				ConnectSocketManager* csm;
				size_t  index;
		};


		class TcpServer{
			public:
				typedef std::lock_guard<std::mutex> LockGuard; 
				typedef struct sockaddr SA;

				typedef std::function<void()> EventCallback;
				typedef std::function<void(ConnectSocketManager*)> MessageCallback;

				typedef  std::map<int, AcceptSocketManager*> AcceptSocketMap;
				typedef  std::map<int, ConnectSocketManager*> ConnectSocketMap;

				typedef std::vector<Entry> entryList;

		/*		TcpServer():pool(1){
					init();
				}
				explicit TcpServer(int threadCount):pool(threadCount){
					init();
				}
			*/	
				explicit TcpServer(Epoller* ep):epoller(ep),pool(1){
					init();
				}

				TcpServer(Epoller* ep,int threadCount) :pool(threadCount),epoller(ep){
					init();
				}
				~TcpServer(){
					shutdown();
				}

				void init(){
					for(int i=0;i<20;i++)
						time_wheel[i].reserve(100);
					TimeStamp ts;
					epoller->runInEvery(ts,std::bind(&TcpServer::doTimeWheel,this),5);
				}
				void start(){
					epoller->loop();
				}

				void setConnectCallback(const EventCallback& cb){
					connectCallback = cb;
				};
				void setMessageCallback(const MessageCallback& cb){
					messageCallback = cb;
				};

				void shutdown();
				void listen(int port);   //监听本地的port端口

			private:
				void doTimeWheel();  //线程问题，1 time_wheel++完，其他线程获取刚加的time_wheel，2 这里map删除，其他地方进行添加. 

				void acceptSocketRead(int fd);
				void acceptSocketActiveClose(AcceptSocketManager* as);      //主动的关闭accept所要做的事情,
				void connectSocketRead(ConnectSocketManager* csm);    //这里就是当有connectRead事件时，就更新该connectFd的timeWheel，
				void connectSocketPassiveClose(int sd);   //被动的关闭connect连接，说明连接的对面关闭了

				bool isDoingTimeWheel=false;

				EpollerPool pool;
				Epoller* epoller;

				AcceptSocketMap accept_map;
				ConnectSocketMap connect_map;

				EventCallback connectCallback;
				MessageCallback messageCallback;

				entryList time_wheel[20];
				int time_wheel_index=0;

				Entry entry;

				std::mutex mutex_;
		};
	}
}


#endif // !TCPSERVER_H
