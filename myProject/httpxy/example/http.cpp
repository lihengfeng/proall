/*************************************************************************
	> File Name: http.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Fri Nov 24 15:08:37 2017
 ************************************************************************/

#include"../code/HttpServer.h"
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

bool isNum(char* nums){
	char* c=nums;
	if(c==nullptr) 
		return false;
	while(*c!='\0'){
		if(*c<'0'||*c>'9')
			return false;
		c++;
	}
	return true;
}

int main(int argc,char**argv){
	if(argc!=2){
		cout<<"传递参数不符合规范，退出"<<endl;
		return 0;
	}
	if(!isNum(argv[1])){
		cout<<"传递参数不是int类型，退出"<<endl;
		return 0;
	}
	int port=atoi(argv[1]);
	HttpServer hs("myHttp");
	hs.listenPort(port);
	hs.start();
	cout<<"从accept退出，结束进程"<<endl;
	return 0;
}
