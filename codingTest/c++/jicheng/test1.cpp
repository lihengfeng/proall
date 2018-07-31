/*************************************************************************
	> File Name: test1.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Thu Oct 26 15:26:39 2017
 ************************************************************************/
//验证继承中函数内部调用形式
//void f()==void f(A* this);
//结果，调用父类的函数，this指针就是父类类型，所以this->p();得到是父类函数
//结果，调用子类的函数，this指针就是子类类型，所以this->p();得到是子类函数
//变量同理，this->变量，this是什么类型，就是调用的那个类型的变量
#include<iostream>
using namespace std;

class A{
public:
	virtual void f(){  //能否使用private变量，取决调用的父类的函数还是子类函数，
		cout<<"a.f()="<<endl;
		g();
	}
	void g(){
		cout<<"a.g()="<<endl;
		p();
	}
	void p(){
		cout<<"a.p()="<<endl;
	}
};
class B:public A{
public:
	void f(){  //能否使用private变量，取决调用的父类的函数还是子类函数，
		cout<<"b.f()="<<endl;
		g();
	}
	void g(){
		cout<<"b.g()="<<endl;
		p();
	}
	void p(){
		cout<<"b.p()="<<endl;
	}
	void h(){
		cout<<"b.h()="<<endl;
	}
};

int main(){

	B b;
	b.f();  //a.g,a.p()
	b.g();  //a.g,a.p()
	A* a=new B();
	a->f();
	cout<<"=================="<<endl;
	a->A::f();
	a->g();
}
