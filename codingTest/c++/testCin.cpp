/*************************************************************************
	> File Name: testCin.cpp
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Wed Jan  3 22:51:47 2018
 ************************************************************************/

#include<iostream>
#include<string>

using namespace std;
int main(){
	string str1,str2;
	char cs[10],rs[10];
	char c,r;
//	cin.get(cs,5);
	cin.getline(rs,5,'d');
//	cin.get(rs,5);
//	getline(cin,str1);
//	getline(cin,str2);

//	cin.get()

	cin.get(c);
	cin.get(r);

	cout<<str1<<endl;
//	cout<<cs<<endl;
	cout<<rs<<endl;
	cout<<(int)c<<endl;
	cout<<(int)r<<endl;
}
