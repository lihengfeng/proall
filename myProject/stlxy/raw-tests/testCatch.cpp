/*************************************************************************
	> File Name: ../raw-tests/testCatch.cpp
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Sun Dec  3 16:55:46 2017
 ************************************************************************/

#include<iostream>
#include <exception>
#include <vector>
using namespace std;
void fun(){
	char buf[3]="12";
	cout<<buf[5]<<endl;
	vector<int> v{1,2,3};
	cout<<v[5]<<endl;
}
int main(){
	try{
		fun();
	}catch(exception& e){
		cout<<"exception"<<endl;
		cout<<e.what()<<endl;
	}
	cout<<"end"<<endl;
}
