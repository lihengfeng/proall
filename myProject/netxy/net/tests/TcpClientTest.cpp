/*************************************************************************
	> File Name: TcpClientTest.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Mon Nov 13 16:05:10 2017
 ************************************************************************/

#include<netxy/base/Cdebug.h>
#include<netxy/net/ConnectSocketManager.h>
#include<netxy/net/TcpClient.h>

#include<string>
#include<iostream>
#include<vector>
#include<memory>

using namespace std;
using namespace netxy::base;
using namespace netxy::net;

typedef	shared_ptr<ConnectSocketManager> ConPtr;
int main(){
	vector<ConPtr> v;
	v.reserve(10);
	TcpClient tc;
	for(int i=0;i<10;i++){
		ConPtr cp=tc.connect("127.0.0.1",9999-i);
		if(!cp){
			debug_error(9999-i,"port , 连接不成功");
		}
		else
			v.push_back(cp);
	}

	string str;
	while(cin>>str){
		for(int i=0;i<v.size();i++){
			string s="no"+to_string(i)+": "+str;
			v[i]->send(s);
		}
	}
	cout<<"end"<<endl;
}
