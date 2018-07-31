/*************************************************************************
	> File Name: test.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Wed Oct 11 20:21:30 2017
 ************************************************************************/
//考察 oop中 隐藏， 子类对象隐藏父类的同名函数


#include<iostream>
using namespace std;

class A{
public:
	virtual void f(){
		cout<<"a.f"<<endl;
	}
	void g(){
		cout<<"a.g"<<endl;
	}
	void h(){
		cout<<"a.h"<<endl;
	}
	virtual void p(){
		cout<<"a.p()"<<endl;
	}
	
};
class B{
public:
	void f(int c){   //子类不是虚函数，父类是虚函数的同命不同惨的情况
		cout<<"b.f(int)"<<endl;
	}
	virtual	void h(int c){//子类是虚函数，父类不是虚函数的同命不同惨的情况
		cout<<"b.h(int)"<<endl;
	}
	void g(int c){//子类不是虚函数，父类不是虚函数的同命不同惨的情况
		cout<<"b.g(int)"<<endl;
	}
	virtual void p(int c){//子类是虚函数，父类是虚函数的同命不同惨的情况
		cout<<"b.p(int)"<<endl;
	}
};

int main(){
	A a;
	B b;
	b.f();
	b.g();
	b.h();
	b.p();

}

