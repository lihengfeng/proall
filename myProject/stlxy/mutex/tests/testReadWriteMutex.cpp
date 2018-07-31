/*************************************************************************
	> File Name: testReadWriteMutex.cpp
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Thu Nov 30 19:09:59 2017
 ************************************************************************/
#include "ReadWriteMutex.h"

#include <unistd.h>

#include <string>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

ReadWriteMutex rw_mutex;

void readm(int i){
	cout<<"rw_mutex.readLock():"<<i<<endl;
	rw_mutex.readLock();
	cout<<"read:"<<i<<endl;
	sleep(5);
	rw_mutex.readUnLock();
}
void writem(int i){
	cout<<"rw_mutex.writeLock():"<<i<<endl;
	rw_mutex.writeLock();
	cout<<"write:"<<i<<endl;
	sleep(5);
	rw_mutex.writeUnLock();
}
void f1(){
	thread t1(readm,1);
	sleep(1);
	thread t5(writem,5);
	sleep(1);
	thread t2(readm,2);
	thread t4(readm,4);
//	thread t3(writem,3);
	t1.detach();
	t2.detach();
//	t3.detach();
	t4.detach();
	t5.detach();
}
void f2(){
	thread t1(readm,1);
	thread t2(readm,2);
	thread t3(writem,3);
	thread t4(readm,4);
	t1.detach();
	t2.detach();
	t3.detach();
	t4.detach();
}

int main(){
	f1();
	for(int i=0;i<30;i++)
	{
		cout<<i<<endl;
		sleep(1);
	}
}
//预测结果，连续输出1,2,4，5秒后输出3
