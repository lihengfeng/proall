/*************************************************************************
	> File Name: ProtobufServer.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Fri Oct 13 12:06:04 2017
 ************************************************************************/

#include"Person.pb.h"

#include<netxy/net/Epoller.h>
#include<netxy/net/TcpServer.h>
#include<netxy/codec/ProtobufDispatcher.h>
#include<netxy/codec/ProtobufCodec.h>


#include<iostream>
using namespace std;
using namespace std::placeholders;

using namespace netxy::base;
using namespace netxy::net;
using namespace netxy::codec;

void onPerson(google::protobuf::Message* mptr){
	Person *p2=dynamic_cast<Person*>(mptr);
	cout<<"p2->id="<<p2->id()<<endl;
	cout<<"p2->name="<<p2->name()<<endl;
	cout<<"p2->email="<<p2->email()<<endl;
}
void onSchool(google::protobuf::Message* mptr){
	School* p=dynamic_cast<School*>(mptr);
	cout<<"p->name="<<p->name()<<endl;
	cout<<"p->address="<<p->address()<<endl;
}
void onBook(google::protobuf::Message* mptr){
	Book *p=dynamic_cast<Book*>(mptr);
	cout<<"p->name="<<p->name()<<endl;
	cout<<"p->author="<<p->author()<<endl;
}

int main(){
	ProtobufDispatcher dispathcher;
	dispathcher.registerCallback<Person>(&onPerson);
	dispathcher.registerCallback<School>(&onSchool);
	dispathcher.registerCallback<Book>(&onBook);
	ProtobufCodec decode(dispathcher);
	Epoller ep;
	TcpServer ts(&ep);
	ts.setMessageCallback(std::bind(&ProtobufCodec::onMessage,&decode,_1));
	for(int i=0;i<5;i++)
	{
		int s=9999-i;
		cout<<"s="<<s<<endl;
		ts.listen(s);
	}
	ep.loop();
}
