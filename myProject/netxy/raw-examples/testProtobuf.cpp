/*************************************************************************
  > File Name: ProtoCodec.h
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Fri Nov  3 13:48:25 2017
 ************************************************************************/
#pragma once

#include"person.pb.h"

#include <google/protobuf/message.h>

#include <arpa/inet.h>
#include<iostream>
using namespace std;

 const static int kHeaderLen = sizeof(int32_t);
   const static int kMinMessageLen = 2*kHeaderLen + 2; // nameLen + typeName + checkSum
     const static int kMaxMessageLen = 64*1024*1024; // same as codec_stream.h kDefaultTotalBytesLimit

int main(){
	void* buf=malloc(512);

	google::protobuf::Message* messageToSend;
	Person person;
	person.set_id(1);
	person.set_name("li heng");
	person.set_email("Running?");

	messageToSend=&person;

	// google::protobuf::Message  message1=person; 因为message是纯虚函数，所以不能实例化出对象
	google::protobuf::Message&  message1=person; 
	google::protobuf::Message&  message2=*messageToSend;

	const std::string& typeName1 = message1.GetTypeName();
	cout<<typeName1<<endl;
	int32_t typeLen=static_cast<int32_t>(typeName1.size()+1);
	cout<<"len="<<typeLen<<endl;
	int32_t net_typeLen= ::htonl(typeLen);
	cout<<"nlen="<<net_typeLen<<endl;

	int32_t byte_size = message1.ByteSize();

	int32_t len=kHeaderLen+typeLen+byte_size+kHeaderLen; 
	char buf[];
	memcpy(&len,kHeaderLen);
	memcpy(&typeLen,kHeaderLen);


	int32_t hlen= ::ntohl(nlen);
	cout<<"hlen="<<hlen<<endl;

	//SerializeToArray(buf,);
	cout<<"byte_size()="<<byte_size<<endl;
	//	uint8_t* start = reinterpret_cast<uint8_t*>(buf);
	//	message1.SerializeWithCachedSizesToArray(start);
	message1.SerializeToArray(buf, byte_size);

	google::protobuf::Message* mptr= NULL;
	const google::protobuf::Descriptor* descriptor =
		google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(typeName1);
	if (descriptor)
	{
		const google::protobuf::Message* prototype =
			google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
		if (prototype)
		{
			mptr= prototype->New();
		}
	}
	
//	const char* data=static_cast<char*>(buf);
	mptr->ParseFromArray(buf,byte_size);
	Person* p2=dynamic_cast<Person*>(mptr);
	cout<<p2->name()<<endl;
	/*	cout<<mstr->GetTypeName()<<endl;
	//	p2.ParseFromArray(buf,byte_size);
	//	delete buf;
	*/	
	free(buf);

}
