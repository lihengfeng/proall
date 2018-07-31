/*************************************************************************
	> File Name: Buffer.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Wed Nov  8 17:54:47 2017
 ************************************************************************/

#include<netxy/base/Cdebug.h>
#include<netxy/base/Buffer.h>


namespace netxy{
	namespace base{

		void Buffer::append(const string& str){ 
			append(str.data(),str.size());
		}
		void Buffer::append(const char*src,size_t n){
			bool r=true;
			int len=strlen(src);
			if(len<n)
			{
				debug_error("strlen(src)<n;会产生越界");
				exit(0);
			}
			if (n > end_storage - end_data)
				r=reconstruct(n);
			if(!r) {
				debug_error("reconstruct 分配失败");
				exit(0);
			}
			memmove(end_data, src, n);
			end_data = end_data + n;
		}

		void Buffer::pop_back(int n){
			if(n>size())
				n=size();
			start_data = start_data + n;
			if (start_data - start_storage > (capacity() / 3))
				forwardMove(size());
		}
		string Buffer::readAll(){
			int len=size();
			string str(start_data,len);
			clear();
			return str;
		}
		string Buffer::read(int n){
			if(n>size())
				n=size();
			string str(start_data,n);
			start_data = start_data + n;
			if (start_data - start_storage > (capacity() / 3))
				forwardMove(size());
			return str;
		}

		void Buffer::clear(){
			start_data =start_storage;
			end_data=start_data;
		}

		void Buffer::backwardMove(size_t n){ //移动end_data;
			end_data+=n;
		}
		void Buffer::forwardMove(size_t len){
			memcpy(start_storage, start_data,len);
			start_data = start_storage;
			end_data = start_data +len;    
		}
		
		bool Buffer::reconstruct(size_t n) { //重新分配内存
			bool result=true;
			size_t len = size();
			size_t old_size = capacity();   //这里的old_size代表原来空间的大小 不包括metadata的大小。
		//	char* old_metadata = metadata;

			size_t new_size = n - (end_storage - end_data) < old_size ? old_size * 2:old_size + n;
			char*  new_metadata = (char*)malloc(8 + new_size);
			try{     //因为 buffer的前半部分可能已经被取出，不需要再拷贝，所以需要跳过start-storage到start-data这一段空间
				memmove(new_metadata, metadata,8);
				memmove(new_metadata+8, start_data,len);
			}
			catch (...){    //如果memove拷贝失败，buffer的各个指针必须回归到原始状态，且释放新申请的空间，所以以下这样实现
				char* temp = metadata;
				metadata = new_metadata;
				new_metadata = temp;
				new_size=old_size; //这是为了下边的end_storage的正确还原
				result=false;
			}
			free(metadata);
			metadata = new_metadata;
			start_storage = (char*)(metadata + 8);
			start_data = start_storage;
			end_data = start_data + len;
			end_storage = start_storage + new_size;
			return result;
		}
  }
}


