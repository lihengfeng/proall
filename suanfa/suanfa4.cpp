/*************************************************************************
	> File Name: suanfa4.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Thu Nov  2 00:04:39 2017
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;

int main(){
	string str;
	cin>>str;
	int len=str.size();
	int k=str[0];
	int n=1;
	for(int i=1;i<len;i++)
	{
		if(str[i]!=k){
			n++;
			k=str[i];
		}
	}
	cout<<(float)len/n<<endl;
}
