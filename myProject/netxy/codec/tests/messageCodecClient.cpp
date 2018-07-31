#include<netxy/net/ConnectSocketManager.h>
#include<netxy/net/TcpClient.h>
#include<netxy/codec/MessageCodec.h>

#include<iostream>
#include<sstream>
#include<string>


using namespace std;

using namespace netxy::base;
using namespace netxy::net;
using namespace netxy::codec;

typedef	shared_ptr<ConnectSocketManager> ConnectSocketManagerPtr;


int main(){
	TcpClient tc;
	MessageCodec encode;
	vector<ConnectSocketManagerPtr> v;
	v.reserve(100);
	for(int i=0;i<10;i++){
		ConnectSocketManagerPtr cp=tc.connect("127.0.0.1",9999-i);
		if(cp){
			v.push_back(cp);
		}
		else
			cout<<"csf"<<i<<"为空, port="<<9999-i<<endl;
	}
	std::string str;
	while(cin>>str){
		for(int i=0;i<v.size();i++){
			string s="no"+to_string(i)+": "+str;
			encode.send(v[i].get(),s);  
		}
	}
	cout<<"end"<<endl;
}
