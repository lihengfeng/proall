/*************************************************************************
  > File Name: ConnectSocketManager.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Sat Nov 11 15:48:42 2017
 ************************************************************************/

#include<netxy/net/ConnectSocketManager.h>

#include<sys/socket.h>
#include<thread>
#include<mutex>

#include<iostream>
using namespace std;

namespace netxy{
	namespace net{
		void ConnectSocketManager::doRead(){
			if(!isConnecting)
				debug_error("close connecting,doRead do not use");
			else{
				if (readCallback)
					readCallback();
				size_t free_length = in_buffer.freeSize();
				char buffer[65536];
				struct iovec vec[2];
				vec[0].iov_base = in_buffer.end();
				vec[0].iov_len = free_length;
				vec[1].iov_base = &buffer;
				vec[1].iov_len =65536;
				size_t length=readv(fd,vec,2);
				if (length == 0){   //如果=0,说明对面已经关闭，或者半关闭
					debug_error("read length=0, doClose");
					doPassvieClose();
				}
				else if (length > free_length){
					debug_value("length>freeSize,local has data,append into in_buffer");
					in_buffer.backwardMove(free_length); //backwardMove是用来调节buffer内部的end_data指针的.
					in_buffer.append(buffer, length - free_length);
				}
				else{ 
					debug_value("length<free,data all in in_buffer");
					in_buffer.backwardMove(length); //backwardMove是用来调节buffer内部的end_data指针的.
				}
				if (messageCallback)
					messageCallback(this);
			}
		}

		void ConnectSocketManager::doWrite(){      //如果一次write就把全部数据发送了，调用stopWrite结束写事件.
			;
			if(!isHalfClose&&!isConnecting){
				bool	isError=false;
				if (out_buffer.size() > 0)      
				{
					int len = out_buffer.size();
					int n = ::write(fd, out_buffer.begin(), out_buffer.size());
					if (n >= 0)
					{
						debug_value("send length=",n);
						out_buffer.pop_back(n);
					}
					else if(n<0){
						if(errno!=EWOULDBLOCK)
							isError=true;
						debug_error("throw error");
					}
				}
				if(out_buffer.empty()||isError){
					debug_error("no data to write||throw error");
					removeEvents(EPOLLOUT);
					epoller->updateManager(this);
					isWriting = false;   //设置isWriting=false;
					if (isHalfClose)   //检查如果有半关闭了，就执行shutdownInloop
						shutdownWriteInLoopThread();
				}
				if (writeCallback)
					writeCallback();
			}
			else
				debug_error("disconnect ，doWrite do not use");
			;
		};

		//TODO 有个可能问题：当close后，如果在penddingFunctor中有用到该ConnectManager怎么办？


		void ConnectSocketManager:: doPassvieClose(){    //收到对面端口发来的关闭，所以用close(fd)关闭
			if(isConnecting){
				isConnecting = false;//这里设置为false,是为了防止doEvent中读到clse后还继续执行后面的事件
				//这里测试先删掉,
				//	epoller->addQueueFunctor(std::bind(&Epoller::removeManager, epoller, this));  
				epoller->removeManager(this);
				if (passiveCloseCallback)
					passiveCloseCallback();
				::close(fd);     //close放在后边，确保epoller中删除时，不会出现相同的fd
			}
			else
				debug_error("已经关闭,doPassvieClose无效了");
		};  


		void ConnectSocketManager::send(const char* p,int len){
			string str(p,len);
			send(str);
		}
		//发送相关
		void ConnectSocketManager::send(const std::string& message){
			if (!isHalfClose&&isConnecting){
				if (epoller->isInLoopThread())
					sendInLoopThread(message);
				else
					epoller->runInLoopThread(std::bind(&ConnectSocketManager::sendInLoopThread, this, message));
			}
			else{
				debug_error("已经关闭了套接字或者半关闭，所以不要再发送数据了");
			}
		}

		void ConnectSocketManager::sendInLoopThread(std::string message){   //因为采用边沿触发.所以在需要写时注册写，在写完后撤销掉写事件。
			size_t  write_len = 0;
			if (out_buffer.empty()){
				write_len=write(fd, message.data(), message.size());
			}
			if(write_len<0)
			{
				if(errno==EWOULDBLOCK)
					write_len=0;
				else debug_error("未知错误");
			}
			if (write_len>=0&&write_len<message.size()){  //如果第一次write没写完，或者out_buffer本身有数据，就需要append到out_buffer后面.
				debug_value("没有发送完全，剩余写入out_buffer");
				out_buffer.append(message.data() + write_len, message.size() - write_len);
				if (!isWriting)   //判断isWriting，如果isWriting为true，说明之前已经在监听写事件，不用改变.
					addEvents(EPOLLOUT);
				epoller->updateManager(this);
				isWriting = true;
			}
			else if(write_len>=message.size())
				debug_value("send all final");
			;
		}
		string ConnectSocketManager::getData(){
			return in_buffer.readAll();
		}

		//主动调用close
		void ConnectSocketManager::close(){
			if (epoller->isInLoopThread())
				closeInLoopThread();
			else
				epoller->runInLoopThread(std::bind(&ConnectSocketManager::closeInLoopThread, this));
		}
		void ConnectSocketManager::closeInLoopThread(){  //主动调用是半关闭
			if(isConnecting){
				if(closeType==2)  //2代表半关闭类型
					shutdownWrite();
				else
					doPassvieClose();
			}
			else debug_error("已经关闭，不要重复close()");
		}
		void ConnectSocketManager::shutdownWrite(){
			if (epoller->isInLoopThread())
				shutdownWriteInLoopThread();
			else
				epoller->runInLoopThread(std::bind(&ConnectSocketManager::shutdownWriteInLoopThread,this));
		}

		void ConnectSocketManager::shutdownWriteInLoopThread(){
			if(!isHalfClose){
				isHalfClose = true;
				if (!isWriting){
					debug_error("debug_close write port");
					::shutdown(fd, SHUT_WR);    //关闭socket的写端口. 这里使用shutwodn
				}
			}
		}
		void  ConnectSocketManager::defaultMessageCallback(){
			if(!in_buffer.empty()){
				cout<<"in_buffer="<<in_buffer.readAll()<<endl;
			}
		}

	}
}



