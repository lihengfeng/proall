/*************************************************************************
  > File Name: DiscardClient.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Tue Nov 14 20:02:47 2017
 ************************************************************************/

//  示例意图： 计算客户端和服务端之间传播时延， 另外计算服务端相比客户端的时钟偏移
//
#include<netxy/base/TimeStamp.h>
#include<netxy/net/TcpClient.h>

#include <sys/time.h>
#include <sys/timerfd.h>
#include <arpa/inet.h>  //nthol，htonl

#include<iostream>
using namespace std;
using namespace netxy::base;
using namespace netxy::net;

class DiscardClient{
	public:
		typedef	shared_ptr<ConnectSocketManager> ConnectSocketManagerPtr;
		DiscardClient(){
			tc.setMessageCallback(std::bind(&DiscardClient::onMessage,this,_1));
		}
		DiscardClient(int threadCount):tc(threadCount){
			tc.setMessageCallback(std::bind(&DiscardClient::onMessage,this,_1));
		}
		~DiscardClient(){
		}
		void connect(const char* ip,int port){
			csp=tc.connect(ip,port);
			if(!csp){
				cout<<"连接失败"<<endl;
				exit(0);
			}	
		}
		void send(){
			//	struct timeval tv;
			//	gettimeofday(&tv, NULL);
			//	oldTime=tv.tv_sec*1000*1000+tv.tv_usec;
			//	int64_t sendTime=::htonl(oldTime);
			// 	string strTime(to_string(sendTime)); 这种方法是错误的，因为一位生成一个ascll,
			char s[8];
			oldTime=TimeStamp::now().getMicroSecondsSinceEpoch_();
			memcpy(s,&oldTime,sizeof(oldTime));
			int64_t time2=*static_cast<int64_t*>((void*)s);

			cout<<"oldTime="<<oldTime<<endl;
			cout<<"time2="<<time2<<endl;

			if(csp)
				csp->send(s,8);
		}
		void onMessage(ConnectSocketManager*csm){  //当前时间-发送时间得到传播时延， 然后求得服务端时钟偏移量

			newTime=TimeStamp::now().getMicroSecondsSinceEpoch_();
			int64_t delayTime=(newTime-oldTime)/2;
			cout<<"delayTime="<<delayTime<<endl;

			string str=csm->getData();
			int64_t reciveTime=*static_cast<int64_t*>((void*)str.data()); 
			cout<<"receiveTime="<<reciveTime<<endl;

			int clockOffset=reciveTime-(oldTime+delayTime);
			cout<<"clockOffset="<<clockOffset<<endl;
		}	
	private:
		int64_t oldTime;
		int64_t newTime;
		ConnectSocketManagerPtr csp;
		TcpClient tc;
};
int main(){
	DiscardClient dc(1);
	dc.connect("127.0.0.1",9999);
	for(int i=0;i<10;i++){
		dc.send();
		sleep(1);
	}
	cout<<"end"<<endl;
}
