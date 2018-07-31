/*************************************************************************
  > File Name: test6.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Sat Nov  4 17:25:50 2017
 ************************************************************************/

#include<iostream>
using namespace std;

//  int i=9;   //如果链接其他文件中，也有i的定义，会出错

namespace ll{
	extern int a;   //声明
	extern int b;   //声明
}

extern int i=0;   //声明

namespace zz{
	void fun(){
		extern int d;
		extern int e;
		cout<<"d="<<d<<endl;
		cout<<"e="<<e<<endl;
	}
};
int h=10;
int main(){
	zz::fun();

	cout<<i<<endl; //在链接时，查找它的定义
	cout<<h<<endl; //在链接时，查找它的定义
	cout<<ll::a<<endl; //在链接时，查找它的定义
	//	cout<<ll::b<<endl; //在链接时，查找它的定义
}
