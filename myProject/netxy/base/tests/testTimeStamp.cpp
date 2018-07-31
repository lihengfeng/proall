/*************************************************************************
	> File Name: test/TimeStampTest.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Mon Sep 11 16:32:20 2017
 ************************************************************************/
#include<netxy/base/TimeStamp.h>
#include<iostream>
#include <sys/time.h>
#include <sys/timerfd.h>
using namespace std;
using namespace netxy::base;

int main(){
	struct timeval tv;
	gettimeofday(&tv,NULL);
	cout<<tv.tv_sec<<"seconds "<<tv.tv_usec<<"useconds"<<endl;
	TimeStamp ts;
	cout<<ts.getSecondsSinceEpoch_()<<"seconds "<<ts.getMicroSecondsSinceEpoch_()<<"useconds"<<endl;
	ts.addSeconds(1000);
	cout<<"ts+1000="<<ts.getSecondsSinceEpoch_()<<"seconds "<<ts.getMicroSecondsSinceEpoch_()<<"useconds"<<endl;
	TimeStamp ts2=ts.now();
	cout<<"ts2="<<ts2.getSecondsSinceEpoch_()<<"seconds "<<ts2.getMicroSecondsSinceEpoch_()<<"useconds"<<endl;
	bool result=ts<ts2;
	bool result2=ts>ts2;
	ts2=ts;
	bool result3=(ts==ts2);
	cout<<"ts2="<<ts2.getSecondsSinceEpoch_()<<"seconds "<<ts2.getMicroSecondsSinceEpoch_()<<"useconds"<<endl;

	cout<<result<<endl;
	cout<<result2<<endl;
	cout<<result3<<endl;
	return 0;
}

