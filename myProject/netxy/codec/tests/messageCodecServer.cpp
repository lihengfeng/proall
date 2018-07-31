/*************************************************************************
	> File Name: TcpServerTest.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Fri Oct 13 12:06:04 2017
 ************************************************************************/

#include<netxy/net/Epoller.h>
#include<netxy/net/TcpServer.h>
#include<netxy/codec/MessageCodec.h>

#include<iostream>
using namespace std;
using namespace std::placeholders;

using namespace netxy::base;
using namespace netxy::net;
using namespace netxy::codec;

int main(){
	MessageCodec decode;
	Epoller ep;
	TcpServer ts(&ep);
	ts.setMessageCallback(std::bind(&MessageCodec::onMessage,&decode,_1));
	for(int i=0;i<20;i++)
	{
		int s=9999-i;
		cout<<"s="<<s<<endl;
		ts.listen(s);
	}
	ep.loop();
}
