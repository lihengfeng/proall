/*************************************************************************
	> File Name: testLevelMutex.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Mon Nov 27 21:01:42 2017
 ************************************************************************/

#include<iostream>
#include<thread>
#include<mutex>
#include<cstdlib>

#include"../LevelMutex.h"

using namespace std;

LevelMutex mutex1(1000);
LevelMutex mutex2(600);
LevelMutex mutex3(100);
int main(){
	try{
	std::lock_guard<LevelMutex> lock1(mutex1);
	std::lock_guard<LevelMutex> lock3(mutex3);
	std::lock_guard<LevelMutex> lock2 (mutex2);
	}catch(exception& ex){ //如果没有catch，levelMutex中异常会直接将what中内容显示给屏幕，并且结束程序
		cout<<ex.what()<<endl;
	}
		cout<<"end"<<endl;
}
