/*************************************************************************
	> File Name: testShared.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Thu Nov 16 16:10:25 2017
 ************************************************************************/

#include<iostream>
#include<memory>
using namespace std;


shared_ptr<int> fun1(){
//	int* ap=new int();
	int* ap=new int(8);
	shared_ptr<int> sp(ap,[](int* p){
		delete p; 
		cout<<"ddd"<<endl;		
	});
	return sp; 
}
weak_ptr<int> fun2(){
//	int* ap=new int();
	int* ap=nullptr;
	shared_ptr<int> sp(ap);
	weak_ptr<int> w(sp);
	return w; 
}

int main(){
	shared_ptr<int> obj=fun1();
//	weak_ptr<int> wp=fun2();
//	shared_ptr<int> obj(wp.lock());
	if(obj){
		cout<<"正常:"<<endl;
	}
	else
		cout<<"连接不成功"<<endl;
}

