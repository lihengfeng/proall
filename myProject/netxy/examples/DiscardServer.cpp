/*************************************************************************
  > File Name: DiscardServer.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Tue Nov 14 13:49:31 2017
 ************************************************************************/
#include<netxy/net/TcpServer.h>

#include <sys/time.h>
#include <sys/timerfd.h>
#include <arpa/inet.h>  //nthol，htonl

#include<iostream>

using namespace std;
using namespace netxy::base;
using namespace netxy::net;

class DiscardServer{
	public:
		DiscardServer():ts(&ep){
			ts.setMessageCallback(std::bind(&DiscardServer::onMessage,this,_1));
		}
		explicit DiscardServer(int threadCount):ts(&ep,threadCount){
			ts.setMessageCallback(std::bind(&DiscardServer::onMessage,this,_1));
		}
		void listen(int port){
			ts.listen(port);
		}
		void start(){
			ts.start();
		}

		void onMessage(ConnectSocketManager* csm){  //接手客户端发来的时间，将当前时间发给客户端
			char s[8];
			string str=csm->getData();
			int64_t reciveTime=*static_cast<int64_t*>((void*)str.data()); 
			cout<<"receiveTime="<<reciveTime<<endl;

			int64_t	sendTime=TimeStamp::now().getMicroSecondsSinceEpoch_();
			memcpy(s,&sendTime,sizeof(sendTime));
			int64_t time2=*static_cast<int64_t*>((void*)s);
			
			cout<<"snedTime="<<sendTime<<endl;
			cout<<"time2="<<time2<<endl;

			csm->send(s,8);
		}
	private:
		Epoller ep;
		TcpServer ts;
};

int main(){
	DiscardServer server_(1);
	server_.listen(9999);
	server_.start();
}
