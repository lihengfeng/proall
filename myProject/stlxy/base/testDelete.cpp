/*************************************************************************
	> File Name: testDelete.cpp
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Wed Dec 13 18:26:23 2017
 ************************************************************************/

#include<iostream>
#include<new>
using namespace std;

int main(){
	void* p=::operator new(1024);
	void* q=p+128;
	::operator delete(q);
}
