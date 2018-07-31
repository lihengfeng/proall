/*************************************************************************
	> File Name: ../raw-tests/testMutexVector.cpp
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Mon Dec  4 14:39:30 2017
 ************************************************************************/
#include <unistd.h>

#include<iostream>
#include<vector>
#include<mutex>
#include<thread>
using namespace std;

std::vector<mutex> mutexs(16);
void f(int index){
	std::lock_guard<std::mutex> lock(mutexs[index]);                                           cout<<"index="<<index<<endl;
	sleep(10);
}
int main(){
	thread t1(f,1);
	thread t2(f,2);
	thread t3(f,3);
	thread t4(f,1);
	t1.join();
	t2.join();
	t3.join();
}
