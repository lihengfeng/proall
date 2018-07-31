/*************************************************************************
  > File Name: suanfa3.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Wed Nov  1 23:53:37 2017
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;

void f(int n,string& str){
	if(n==1)
		str.append("1");
	else if(n==2)
		str.append("2");
	else {
		if(n&1){
			f((n-1)/2,str);
			str.append("1");
		}
		else{
			f(n/2-1,str);
			str.append("2");
		}
	}    
};

int main(){
	int n;
	string str;
	cin>>n;
	f(n,str);
	cout<<str<<endl;
}
