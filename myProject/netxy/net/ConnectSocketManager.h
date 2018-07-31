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

				//禁止使用拷贝和赋值
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

				int closeType=1; //默认1 为全关闭
				bool isWriting=false;
				bool isHalfClose= false;

				int  time_wheel_index=100;   //这里设置除了0-20的任何正数都可以，因为0-20是time_wheel的下标，默认不要和其冲突.
		};
	}
}



#endif // !ConnectSocketManager_H
