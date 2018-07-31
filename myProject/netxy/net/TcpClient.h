#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include<netxy/net/ConnectSocketManager.h>
#include<netxy/net/Epoller.h>
#include<netxy/net/EpollerPool.h>

#include<iostream>
#include<functional>
#include<vector>
#include<map>
#include<memory>

using namespace std;


namespace netxy{
	namespace net{
		class TcpClient{
			public:
				typedef std::function<void()> EventCallback;
				typedef std::function<void(ConnectSocketManager *)> MessageCallback;
				typedef std::map<int, ConnectSocketManager*> ConnectSocketMap;

				TcpClient():epool(){
				}
				TcpClient(int threadCount):epool(threadCount){
				}
				~TcpClient(){
					for(ConnectSocketMap::iterator it=connect_map.begin();it!=connect_map.end();it++){
						it->second->setCloseType(1);
						it->second->close();
					}
				}

				shared_ptr<ConnectSocketManager> connect(const char* ip,int port);


				ConnectSocketManager* newConnectSocketManager(int fd);

				ConnectSocketManager* connecting( int fd);   //���connect���ӵ����ҷ���EISCONN,��ִ�иþ�
				ConnectSocketManager* retry(int fd);



				void connectSocketPassiveClose(ConnectSocketManager* csm);  //�����Ĺر�connect���ӣ�˵�����ӵĶ���ر���


				void setConnectCallback(const EventCallback& cb){
					connectCallback = cb;
				};
				void setMessageCallback(const MessageCallback& cb){
					messageCallback = cb;
				};

				void shutdown(){
				};
			private:
				EpollerPool epool;

				EventCallback connectCallback;
				MessageCallback messageCallback;

				ConnectSocketMap connect_map;
		};
	}
}


#endif // !TcpClient_h
