/*************************************************************************
	> File Name: testMove.cpp
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Thu Nov 30 20:53:27 2017
 ************************************************************************/

#include<iostream>
#include<string>
#include<string.h>
using namespace std;
int lf(){
	int a=5;
	return a;
}
//返回引用，所以表达式是右值
int& rf(){
	int a=5;
	return a;
}

int main(){
	const int& ci=5*9;
	const int& ci2=lf();
	int&& rci3=lf();  //右值引用到右值
	cout<<ci<<endl;
	cout<<ci2<<endl;
	rf()=6;

	string&& str1=string("12345");
	cout<<str1<<"="<<str1.size()<<endl;

	string str("12345");
	//下列出现了错误
	strcat(const_cast<char*>(str.c_str()),"zzzzzz");
	cout<<str<<"="<<str.size()<<endl;
	string&& str2=std::move(str);
	str2.append("dss");
	cout<<str2<<"="<<str2.size()<<endl;
	cout<<str<<"="<<str.size()<<endl;
	//int& i=5;  错误，5是常量表达式，是右值，int&是左值引用
	//lf()=6;
	//int& ci3=lf();
	//int&& ci3=rf();
}
