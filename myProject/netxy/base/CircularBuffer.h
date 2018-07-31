#ifndef CIRCULARBUFFER_H
#define  CIRCULARBUFFER_H

#include<new>

namespace netxy{
	namespace base{
		template<typename T>
		class CircularBuffer{
		public:
			CircularBuffer(){   //���Ĭ�ϵĻ��������10��T���͵Ŀռ�
				start_storage = malloc(sizeof(T)*10);
				start_data = start_storage;
				end_storage = start_storage + n;
				end_data = start_data;
			}
			explicit CircularBuffer(size_t n){
				start_storage = malloc(sizeof(T)*n);
				start_data = start_storage;
				end_storage = start_storage + n;
				end_data = start_data;
			}

			size_t capacity(){
				 return end_storage - start_storage;
			}
			size_t size(){
				if (end_data > start_data)
					return end_data - start_data;
				else if (end_data<start_data)
					return (end_data - start_storage) + (end_storage - start_data);
				else if (isEmpty) return 0;
				else if (isFull) return end_storage-start_storage;
			}
			bool empty(){
				return isEmpty;
			}
			bool full(){
				return isFull;
			}
			void push_back(const T& x){
				//�����Ӵ���С���ڴ��������˵����������λ��δ����ֵ������δ��ʼ���ģ���Ҫ�ó�ʼ������֮������λ�ö�������ֵ�����Բ���=������.
				if (add_times<end_storage-start_storage) 
					new(end_data)T(x);
				else
					*end_data = x;
				++end_data;
				if (end_data == end_storage) end_data = start_storage;
				isEmpty = false;
				if (end_data == start_data) isFull = true;
			}

			T pop_front(){
				T x = *start_data;
				start_data++;
				isFull = false;
				if (start_data == end_data) isEmpty = true;
				return x;
			}
		private:	
			T* start_data;
			T* end_data;
			T* start_storage;
			T* end_storage;

			bool isEmpty = true;
			bool isFull = false;
			size_t add_times=0;  //��Ӵ���   
		};
	}
}

#endif
