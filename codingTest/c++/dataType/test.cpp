/*************************************************************************
	> File Name: test.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Thu Oct 26 16:04:34 2017
 ************************************************************************/
//分母和分子，有一个float，结果就是float

#include<iostream>
using namespace std;

int main(){

	float f=5/2;
	cout<<f<<endl;
	f=5.0/2;
	cout<<f<<endl;
	f=5/2.0;
	cout<<f<<endl;
	f=(float)5/2;
	cout<<f<<endl;
	f=5/(float)2;
	cout<<f<<endl;
}
