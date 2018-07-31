/*************************************************************************
  > File Name: MessageCodec.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Sun Nov 12 13:37:33 2017
 ************************************************************************/

#include<netxy/codec/MessageCodec.h>
#include<iostream>
using namespace std;
using namespace netxy::base;
using namespace netxy::net;

namespace netxy{
	namespace codec{

		void  MessageCodec::send(ConnectSocketManager* csm,string& message){
			int32_t mesLen=message.size();
			int32_t len=static_cast<int32_t>(mesLen+4);  //这里len=正文长度+checkSum长度
			int32_t be32=htonl(len);

			char cs[len+4];
			//消息段的头部为 段的长度(包括正文长度和4字节的检验和)
			memcpy(cs,&be32,sizeof(be32));
			//消息的正文
			memcpy(cs+4,message.data(),mesLen);

			//消息的adler检验和
			int32_t checkSum = static_cast<int32_t>(::adler32(message.data(),mesLen));
			debug_value("checkSum=",checkSum);
			int32_t nCheckSum=htonl(checkSum);
			memcpy(cs+len,&nCheckSum,4);
			csm->send(cs,len+4);
		}
		void MessageCodec::onMessage(ConnectSocketManager* csm){
			debug_value("进入messagecodec的messagen_buffer.size()=",csm->in_buffer.size());
			if(csm->in_buffer.getHeadLength()==0)
			{
				if(csm->in_buffer.size()>=4)
				{
					string strLen= csm->in_buffer.read(4);
					int32_t be32=*static_cast<int32_t*>((void*)strLen.data());
					int32_t len=ntohl(be32);
					if(len<kMinMessageLen||len>kMaxMessageLen){
						debug_error("headLength>kMaxMessageLen||headLength<kMinMessageLen");
						csm->close();
						return ;
					}
					csm->in_buffer.setHeadLength(len);
					debug_value("getHeadLenght=0,setHeadLength=",len);
				}
			}
			if(csm->in_buffer.getHeadLength()>0){
				int headLength=csm->in_buffer.getHeadLength();
				debug_value("getHeadLenght=",headLength);
				if(csm->in_buffer.size()>=headLength)
				{
					string content= csm->in_buffer.read(headLength-4);
					int32_t checkSum = static_cast<int32_t>(::adler32(content.data(),headLength-4));
					string checkSumStr= csm->in_buffer.read(4);
					int32_t nCheckSum=*static_cast<int32_t*>((void*)checkSumStr.data());
					int32_t expectCheckSum=ntohl(nCheckSum);
					debug_value("expectCheckSum=",expectCheckSum);
					debug_value("CheckSum=",checkSum);

					if(checkSum==expectCheckSum){
						cout<<"this message"<<content<<endl;
						if(messageCallback)
							messageCallback(csm);
						debug_value("in_buffer.size()=",csm->in_buffer.size());
						if(csm->in_buffer.size()>=4)
						{
							string strLen= csm->in_buffer.read(4);
							int32_t be32=*static_cast<int*>((void*)strLen.data());
							int32_t len=ntohl(be32);
							if(len<kMinMessageLen||len>kMaxMessageLen){
								debug_error("headLength>kMaxMessageLen||headLength<kMinMessageLen");
								csm->close();
								return ;
							}
							csm->in_buffer.setHeadLength(len);
							debug_value("结束一次读取，重新setHeadLength=",len);
						}
						else{ 
							csm->in_buffer.setHeadLength(0);
							debug_value("setHeadLength=",0);
						}
					}
					else{
						debug_error("checkSum!=expectCheckSum,关闭连接");
						csm->close();
						return ;
					}
				}
			}
		}
	}
}
