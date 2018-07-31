/*************************************************************************
  > File Name: MessageCodec.h
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Sat Oct 21 16:53:37 2017
 ************************************************************************/

#include<netxy/base/adler32.h>
#include<netxy/base/Cdebug.h>
#include<netxy/net/ConnectSocketManager.h>

#include<string.h>
#include <arpa/inet.h>  //nthol，htonl

#include<iostream>
#include<string>
#include<functional>

using namespace std;
using namespace netxy::base;
using namespace netxy::net;

namespace netxy{
	namespace codec{

		class MessageCodec{
			public:
				typedef std::function<void(ConnectSocketManager *)> MessageCallback;

				MessageCodec(){
				}
				MessageCodec(const MessageCallback& mc ):messageCallback(mc){
				}

				void  send(ConnectSocketManager* csm,string& message);
				void onMessage(ConnectSocketManager* csm);

			private:
				MessageCallback messageCallback;
				const static int kMinMessageLen =4; 
				const static int kMaxMessageLen = 64*1024*1024; // same as codec_stream.h kDefaultTotalBytesLimit
		};
	}
}
