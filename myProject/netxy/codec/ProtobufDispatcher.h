/*************************************************************************
  > File Name: Dispatcher.h
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Tue Nov  7 14:34:52 2017
 ************************************************************************/
#pragma once

#include <google/protobuf/message.h>

#include<map>
#include<iostream>
#include<functional>
using namespace std;

namespace netxy{
	namespace codec{

		class ProtobufDispatcher{
			public:
				typedef std::function<void(google::protobuf::Message*)> ProtobufMessageCallback; 

				ProtobufDispatcher(){
				}
				template<typename T>
					void registerCallback(const ProtobufMessageCallback& cb){
						//callbacks.insert({T::descriptor(),cb});
						callbacks[T::descriptor()]=cb;   //map小标操作，如果找不到下标值就创建一个pari,key为下标值
					}
				void onProtobufMessage(google::protobuf::Message* mptr){
					CallbackMap::const_iterator it = callbacks.find(mptr->GetDescriptor());
					if (it != callbacks.end())
					{
						it->second(mptr);
					}
					else
					{
						defaultCallback( mptr);
					}
				}
				void defaultCallback(google::protobuf::Message* mptr){
					cout<<"defaultCallback: typeName="<<mptr->GetTypeName()<<endl;
				}
			private:
				typedef std::map<const google::protobuf::Descriptor*,ProtobufMessageCallback> CallbackMap;
				CallbackMap callbacks;
		};
	}
}

