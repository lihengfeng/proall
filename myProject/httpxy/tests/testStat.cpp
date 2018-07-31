/*************************************************************************
	> File Name: tests/testStat.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Wed Nov 22 22:22:49 2017
 ************************************************************************/

#include <sys/stat.h>
#include<iostream>
#include<string>
using namespace std;

int main(){
	struct stat st;
	string path="host/index.html";
	if(stat(path.c_str(),&st)==-1){
		cout<<"文件不存在"<<endl;
	}
}
