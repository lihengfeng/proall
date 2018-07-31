/*************************************************************************
	> File Name: TuntuClient.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Wed Nov 15 17:55:13 2017
 ************************************************************************/
#include<netxy/base/TimeStamp.h>
#include<netxy/net/TcpClient.h>

#include<iostream>
using namespace std;
using namespace netxy::base;
using namespace netxy::net;

class TuntuClient{
	public:
		typedef	shared_ptr<ConnectSocketManager> ConnectSocketManagerPtr;
		TuntuClient(){
			tc.setMessageCallback(std::bind(&TuntuClient::onMessage,this,_1));
		}
		TuntuClient(int threadCount):tc(threadCount){
			tc.setMessageCallback(std::bind(&TuntuClient::onMessage,this,_1));
		}
		~TuntuClient(){
		}
		void connect(const char* ip,int port){
			csmp=tc.connect(ip,port);
			if(!csmp){
				cout<<"连接失败"<<endl;
				exit(0);
			}	
		}
		void send(int n){
			string str(n,'a');
			cout<<str<<endl;
			if(csmp){
				while(true)
			    	csmp->send(str);
			}
		}
		void onMessage(ConnectSocketManager*csm){ 
		}	
	private:
		int64_t oldTime;
		int64_t newTime;
		TcpClient tc;
		ConnectSocketManagerPtr csmp;
};
int main(){
	int n;
	TuntuClient dc(1);
	dc.connect("127.0.0.1",9999);
	cout<<"请输入每次发送的字节数:";
	cin>>n;
	dc.send(n);
	cout<<"end"<<endl;
}
