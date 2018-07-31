/*************************************************************************
  > File Name: ProtobufCodec.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Sun Nov 12 13:40:25 2017
 ************************************************************************/
#include<netxy/codec/ProtobufCodec.h>
#include<iostream>
using namespace std;
using namespace netxy::net;
using namespace netxy::base;

namespace netxy{
	namespace codec{

		void ProtobufCodec::send(ConnectSocketManager*csm,google::protobuf::Message& message){
			const std::string& typeName = message.GetTypeName();
			int32_t typeLen=static_cast<int32_t>(typeName.size()+1);
			int32_t byte_size = message.ByteSize();
			int len=4+typeLen+byte_size+4;   //len=记录类型的长度的4字节+类型长度+序列化所占字节数+检验和所在字节数

			int32_t nlen= ::htonl(len);
			int32_t ntypeLen= ::htonl(typeLen);

			char s[len+4];
			memcpy(s,&nlen,sizeof(nlen));
			memcpy(s+4,&ntypeLen,sizeof(ntypeLen));
			memcpy(s+8,typeName.c_str(),typeLen);  //string.c_str()返回带有'\0';
			message.SerializeToArray(s+8+typeLen, byte_size);

			//取出除了除记录长度数值外所有，计算检验和
			int32_t checkSum = static_cast<int32_t>(::adler32(s+4,len-4));
			int32_t nCheckSum=::htonl(checkSum);
			memcpy(s+len,&nCheckSum,4);

			debug_value("len=",len);
			debug_value("typeLen=",typeLen);
			debug_value("typeName=",typeName);
			debug_value("byte_size=",byte_size);
			debug_value("checkSum=",checkSum);
			csm->send(s,len+4);
		}

		void ProtobufCodec::onMessage(ConnectSocketManager* csm){
			debug_value("进入Protobuf的buffer.size()=",csm->in_buffer.size());
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
				int32_t len=csm->in_buffer.getHeadLength();
				debug_value("getHeadLenght=",len);
				if(csm->in_buffer.size()>=len)
				{

					string content= csm->in_buffer.read(len-4);  //data=typeLen+ typeName+protobufData
					string checkSumStr= csm->in_buffer.read(4);

					int32_t checkSum = static_cast<int32_t>(::adler32(content.data(),len-4));
					int32_t nCheckSum=*static_cast<int32_t*>((void*)checkSumStr.data());
					int32_t expectCheckSum=ntohl(nCheckSum);
					debug_value("expectCheckSum=",expectCheckSum);
					debug_value("CheckSum=",checkSum);

					if(checkSum==expectCheckSum){
						int32_t ntypeLen=*static_cast<int32_t*>((void*)content.data());
						int32_t typeLen=ntohl(ntypeLen);
						string typeName(content.data()+4,typeLen-1);
						debug_value("typeLen=",typeLen);
						debug_value("typeName=",typeName);

						google::protobuf::Message* mptr= createNewMessage(typeName);
						if(mptr!=NULL){
							mptr->ParseFromArray(content.data()+4+typeLen,len-8-typeLen);
							dispathcher.onProtobufMessage(mptr);
							delete mptr;
						}
						else
							debug_error("没有符合的type");
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
		google::protobuf::Message* ProtobufCodec::createNewMessage(string& typeName){
			google::protobuf::Message* mptr= NULL;
			const google::protobuf::Descriptor* descriptor =
				google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(typeName);
			if (descriptor)
			{
				const google::protobuf::Message* prototype =
					google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
				if (prototype)
				{
					mptr= prototype->New();
				}
			}
			return mptr;
		}

	}
}
