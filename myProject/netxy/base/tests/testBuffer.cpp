/*************************************************************************
	> File Name: testBuffer.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Mon Nov 13 11:27:55 2017
 ************************************************************************/

#include<netxy/base/Buffer.h>

#include<iostream>
using namespace std;
using namespace netxy::base;

int main(){
	Buffer b;
	char c[124]="ABCDEFG";
	string str("123456789");
	b.append(c,7);
	cout<<"b.size()="<<b.size()<<endl;
	b.append(str);
	cout<<"b.size()="<<b.size()<<endl;

	cout<<"b.read(5)="<<b.read(5)<<endl;
	cout<<"b.size()="<<b.size()<<endl;

	cout<<"b.readAll()="<<b.readAll()<<endl;
	cout<<"b.size()="<<b.size()<<endl;
	b.append("abcdefg",7);
	cout<<"b.size()="<<b.size()<<endl;
	b.clear();
	cout<<"b.size()="<<b.size()<<endl;

	b.append("abcdefg",10);
	cout<<"b.size()="<<b.size()<<endl;
	cout<<"b.readAll()="<<b.readAll()<<endl;

}
