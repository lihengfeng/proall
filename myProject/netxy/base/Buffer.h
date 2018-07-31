/*************************************************************************
	> File Name: Buffer.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Wed Nov  8 17:54:47 2017
 ************************************************************************/
#ifndef BUFFER_H
#define BUFFER_H

#include<netxy/base/Cdebug.h>

#include<string.h>

#include<iostream>
#include<string>

using std::cin; 
using std::cout; 
using std::string; 

namespace netxy{
	namespace base{
		

	class Buffer{
	public:
		Buffer(){
			init(100);
		}
		explicit Buffer(int n){
			init(n);
		}
		~Buffer(){
			free(metadata);
		}
		void init(int n){
			metadata =(char*)malloc(8 + n);
			start_storage = (char*)(metadata + 8);
			start_data = start_storage;
			end_storage = start_storage +n;
			end_data = start_data;
		}
		bool empty(){
			return end_data == start_data;
		}
		bool full(){
			return end_data==end_storage;
		}
		size_t capacity(){   //总共数据的到空间大小，不考虑metadata所占用的空间
			return end_storage - start_storage;
		}
		size_t size(){
			return end_data - start_data;
		}
		size_t freeSize(){
			return end_storage - end_data;
		}

		char* begin(){ 
			return start_data;
		}
		char* end(){
			return end_data; 
		}

		void setHeadLength(int n){
			headLength=n;
		}
		int getHeadLength(){
			return headLength;
		}
		void append(const string & src);
		void append(const char*src,size_t n);
		void pop_back(int n);
		string readAll();
		string read(int n);
		void clear();

		void backwardMove(size_t n); //移动end_data;
		void forwardMove(size_t len);  //移动startdata
	private:
		bool reconstruct(size_t n);  //重新分配内存
		
		char* metadata;     //负责记录buffer的存储情况.
		char* start_data;
		char* end_data;
		char* start_storage;
		char* end_storage;

		bool isEmpty = true;
		bool isFull = false;

		int headLength=0;
	};
  }
}

#endif
