/*************************************************************************
	> File Name: testIntToString.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Wed Nov 15 15:47:53 2017
 ************************************************************************/
#include<netxy/base/TimeStamp.h>

#include<iostream>
#include<string>
#include<string.h>
using namespace std;
using netxy::base::TimeStamp;


int main(){
	char s[8];

	int64_t time=TimeStamp::now().getMicroSecondsSinceEpoch_();
	cout<<time<<endl;

	string str(to_string(time));
	cout<<str<<endl;
	cout<<"str.size()="<<str.size()<<endl;

	memcpy(s,str.data(),sizeof(int64_t));
	int64_t time2=*static_cast<int64_t*>((void*)s);
	cout<<time2<<endl;

	memcpy(s,&time,sizeof(time));
	int64_t time3=*static_cast<int64_t*>((void*)s);
	cout<<time3<<endl;
}

