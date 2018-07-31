/*************************************************************************
	> File Name: testPlaceNew.cpp
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Sat Dec  2 14:46:27 2017
 ************************************************************************/

#include<unistd.h>
#include<iostream>
#include<new>
#include<string>
using namespace std;
int main(){
	void* p=malloc(30);
	string* str=new (p) string("12345678");
	cout<<p<<endl;
	cout<<str<<endl;
	cout<<*str<<endl;
	delete str;
}
