/*************************************************************************
	> File Name: test.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Wed Oct 11 20:22:58 2017
 ************************************************************************/
//测试静态变量在继承中，
//结果：静态变量在父类和子类公用。
#include<iostream>

using namespace std;

class A{
public:
	virtual	void f(){
		cout<<"a.fff"<<endl;
	}
	static int n;
};
int A::n=6;
class B:public A{
public:
	void f(){
		cout<<"b.fff"<<endl;
	}
	
};


int main(){
//	cout<<a;
	B b;
	A a;//出现的是父类的虚函数，说明虚表生成是由a构造的
	cout<<"a.n="<<a.n<<endl;
	b.n=10;
	cout<<"a.n="<<a.n<<endl;
}



