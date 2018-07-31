/*************************************************************************
	> File Name: suanfa1.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Sun Oct 22 15:43:10 2017
 ************************************************************************/

#include<iostream>
#include<string.h>
using namespace std;

int main(){
	char*str="hello world the";
	char*str2=str;
	int length=strlen(str);
	cout<<length<<endl;
	int sp=0;
	while(*str!='\0'){
		if(*str++==32)
			sp++;
	}
	int len=length+sp*2;
	cout<<sp<<endl;
	char c[len+1];
	int j=0;
	while(*str2!='\0')
	{
		if(*str2==32)
		{
			c[j++]='%';
			c[j++]='2';
			c[j++]='0';
		}
		else
			c[j++]=*str2;
		str2++;
	}
	c[j]='\0';
	str=c;
	cout<<c<<endl;
	cout<<str<<endl;
}
