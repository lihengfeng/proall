/*************************************************************************
	> File Name: testThread.cpp
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Thu Nov 30 20:30:15 2017
 ************************************************************************/

#include<iostream>
#include<thread>
#include<unistd.h>

//测试thread中对于参数是引用类型的函数是否还需要拷贝传给他的变量

using namespace std;
class A{
public:
	A(){
	}
	A(const A&& other){
		cout<<""<<endl;
	}
	A(const A& other){
		cout<<"copy"<<endl;
	}
private:
};

void fun(A& a){
	cout<<"fun"<<endl;
}
int main(){
	A a;
	fun(a);
	thread t1(fun,a);
	sleep(2);
}
