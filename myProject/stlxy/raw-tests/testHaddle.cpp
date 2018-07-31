/*************************************************************************
	> File Name: testHaddle.cpp
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Fri Dec  1 15:27:49 2017
 ************************************************************************/

#include<iostream>
#include<new>
using namespace std;

void f(){
	cout<<"out of memory"<<endl;
	abort();
};
class Wiget{
public:
	Wiget(){
	}
	~Wiget(){
		std::set_new_handler(oldHandler);
	}
	static void setHandler(std::new_handler f){
		handler=f;
	}
	static void* operator new(size_t size) throw(bad_alloc){
		oldHandler=std::set_new_handler(handler);
		//return ::operator new(size);
		void* p=::operator new(size);
		std::set_new_handler(oldHandler); //将handler还原为系统本身的handler，但只使用于operator new在调用out_of_handler后成功返回（不抛出异常）的情况，如果抛出异常就会跳过
		return p;
	}
private:
	static std::new_handler oldHandler;
	static std::new_handler handler;
	int i[10000000000000];
};
	std::new_handler Wiget::oldHandler=nullptr;
	std::new_handler Wiget::handler=nullptr;

int main(){
	Wiget::setHandler(f);
	Wiget* w=new Wiget;
	delete w;
/*
	std::set_new_handler(f);
	int* big=new int[11111000000000];
	delete big;
*/
}
