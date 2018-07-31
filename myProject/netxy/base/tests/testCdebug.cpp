/*************************************************************************
	> File Name: testCdebug.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Wed Nov  8 16:20:35 2017
 ************************************************************************/

#include<netxy/base/Cdebug.h>
#include<iostream>
using namespace std;
using namespace netxy::base;

int main(){

	debug_value(999,666,",sss=",0000);
debug_value("xxx=",9444);
debug_error("yyy=",3333333,"i,dwadw=",777);
debug_error("yyy=",9999);

}
