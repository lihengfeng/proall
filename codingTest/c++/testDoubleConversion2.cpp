/*************************************************************************
	> File Name: test1223.cpp
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Sat Dec 23 17:23:17 2017
 ************************************************************************/

#include<iostream>
using namespace std;

struct A{
	A()=default;
	A(const int& b){
		cout<<"A(const int&)"<<endl;
	};  //单参数转换
};
struct B{
	B()=default;
	B(const double& b){
		cout<<"A(const double&)"<<endl;
	};  //单参数转换
};

//两种重载方法
void mainc(const A&);  
void mainc(const B&);
//直观来看，int是直接转换，

int main(){
	short s=6;
	mainc(s);
	mainc(10);
}
