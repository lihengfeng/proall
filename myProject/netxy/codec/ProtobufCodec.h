/*************************************************************************
  > File Name: ProtobufCodec.h
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Mon Nov  6 21:08:20 2017
 ************************************************************************/
#pragma once

#include"Person.pb.h"

#include<netxy/base/adler32.h>
#include<netxy/base/Cdebug.h>
#include<netxy/net/ConnectSocketManager.h>
#include<netxy/codec/ProtobufDispatcher.h>

#include <google/protobuf/message.h>

#include <arpa/inet.h>

#include<iostream>
#include<functional>
#include<string>
using namespace std;
using namespace netxy::net;
using namespace netxy::base;

namespace netxy{
	namespace codec{

		class ProtobufCodec{
			public:
				//typedef std::function<void(ConnectSocketManager *)> MessageCallback;
				ProtobufCodec(ProtobufDispatcher& dp):dispathcher(dp){
				}

				void send(ConnectSocketManager*csm,google::protobuf::Message& message);

				void onMessage(ConnectSocketManager* csm);
			private:
				google::protobuf::Message* createNewMessage(string& typeName);

				ProtobufDispatcher& dispathcher;

				const static int kMinMessageLen =4; 
				const static int kMaxMessageLen = 64*1024*1024; // same as codec_stream.h kDefaultTotalBytesLimit
		};
	}
}
