#ifndef CONNECTSOCKETMANAGER_H
#define CONNECTSOCKETMANAGER_H

#include<netxy/net/Manager.h>
#include<netxy/net/Epoller.h>
#include<netxy/base/Buffer.h>

#include<string>

using namespace std::placeholders;
using namespace netxy::base;

namespace netxy{
	namespace net{
		class ConnectSocketManager :public Manager{
			public:
				typedef std::function<void(ConnectSocketManager *)> MessageCallback;
				typedef std::function<void(string& message)> SendCallback;

				ConnectSocketManager(int fid,Epoller*ep) :Manager(fid,ep){
					messageCallback=&ConnectSocketManager::defaultMessageCallback;
				};

				//��ֹʹ�ÿ����͸�ֵ
				ConnectSocketManager(ConnectSocketManager& other) = delete;
				ConnectSocketManager& operator=(ConnectSocketManager& other) = delete;

				~ConnectSocketManager(){
					if(isConnecting)
						doPassvieClose();
				};

				void doRead();
				void doWrite();      
				void  doPassvieClose();   

				void send(const char* p,int len);
				void send(const std::string& message);
				void sendInLoopThread(std::string message);  
				string getData();

				void close();
				void closeInLoopThread(); 

				void shutdownWrite();
				void shutdownWriteInLoopThread();

				void  defaultMessageCallback();

				void setCloseType(int n){
					closeType=n;
				}
				void setMessageCallback(const MessageCallback& cb){
					messageCallback = cb;
				};
				void setTimeWheelIndex(size_t index){
					time_wheel_index = index;
				}
				int getTimeWheelIndex(){
					return time_wheel_index;
				}

				Buffer in_buffer;
				Buffer out_buffer;
			private:
				MessageCallback messageCallback;
				SendCallback sendCallback;

				int closeType=1; //Ĭ��1 Ϊȫ�ر�
				bool isWriting=false;
				bool isHalfClose= false;

				int  time_wheel_index=100;   //�������ó���0-20���κ����������ԣ���Ϊ0-20��time_wheel���±꣬Ĭ�ϲ�Ҫ�����ͻ.
		};
	}
}



#endif // !ConnectSocketManager_H
