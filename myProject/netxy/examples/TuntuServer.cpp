/*************************************************************************
	> File Name: TuntuServer.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Wed Nov 15 17:59:16 2017
 ************************************************************************/
#include<netxy/net/TcpServer.h>

#include <sys/time.h>
#include <sys/timerfd.h>
#include <arpa/inet.h>  //nthol，htonl

#include<iostream>
#include<atomic>

using namespace std;
using namespace netxy::base;
using namespace netxy::net;

class TuntuServer{
	public:
		TuntuServer():ts(&ep){
			ts.setMessageCallback(std::bind(&TuntuServer::onMessage,this,_1));
			ep.runInEvery(TimeStamp::now(),std::bind(&TuntuServer::printTuntu,this),5);
		}
		explicit TuntuServer(int threadCount):ts(&ep,threadCount){
			ts.setMessageCallback(std::bind(&TuntuServer::onMessage,this,_1));
			ep.runInEvery(TimeStamp::now(),std::bind(&TuntuServer::printTuntu,this),5);
		}
		void listen(int port){
			ts.listen(port);
		}
		void start(){
			ts.start();
		}
		void onMessage(ConnectSocketManager* csm){  //接手客户端发来的时间，将当前时间发给客户端
			int size=csm->getData().size();
			countBytes+=size;
			countMessageNumber+=1;
		}
		void printTuntu(){
			int newBytes=countBytes;
			int newMessageNumber=countMessageNumber;
			TimeStamp endTime =TimeStamp::now();

			int bytes=newBytes - oldBytes;
			int mesNum=newMessageNumber - oldMessageNumber;
			if(mesNum==0)
				mesNum=1;
			int seconds=endTime.getSecondsSinceEpoch_()-startTime.getSecondsSinceEpoch_();

			printf("%4.3f M/S, %4.3f/S, %6.2f bytes per message",
					static_cast<float>(bytes)/seconds/1024/1024,
					static_cast<float>(mesNum)/seconds,
					static_cast<float>(bytes)/mesNum);

			startTime=endTime;
			oldBytes=newBytes;
			oldMessageNumber=newMessageNumber;
		}
	private:
		Epoller ep;
		TcpServer ts;
		atomic_int countBytes;
		atomic_int countMessageNumber;
		TimeStamp startTime;
		int oldBytes;
		int oldMessageNumber;
};

int main(){
	int n;
	cout<<"输入线程数来开启server:";
	cin>>n;
	TuntuServer server_(n);
	server_.listen(9999);
	server_.start();
}
