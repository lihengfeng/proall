/*************************************************************************
	> File Name: test.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Fri Oct 13 17:44:37 2017
 ************************************************************************/

//验证类内变量哪些不显示初始化和不类内初始化会出错。
//结果，
//（1）引用类型会出错
//（2） const 内置类型会出错
//（3）没有默认构造函数的类会出错
//注意： const 类类型不会出错（前提：类内又默认构造函数）

#include<iostream>
#include<vector>
using namespace std;

//const int k;

int f=5; 

class B{
public:
	B(){}
	int i=3;
};

class A{
public:
	A(){}
	const int ci=9;
	const B b;
	int i;
//	int & c;  //出错
	int & i2=f;  //
};

int main(){
//	const int c;  //出错，const内置类型必须赋给初始置
//	const char c;
	const B b;
	A a;
	cout<<a.b.i<<endl;
	cout<<"a.i2="<<a.i2<<endl;
	return 0;
}
