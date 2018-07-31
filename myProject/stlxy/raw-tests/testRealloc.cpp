/*************************************************************************
	> File Name: testRealloc.cpp
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Sat Dec  2 16:44:37 2017
 ************************************************************************/

#include <stdio.h>  
#include <stdlib.h>  
#include<iostream>
using namespace std;
int main(){
	char*oldPtr;
	char*newPtr;
	oldPtr=(char*)malloc(10);
	if(oldPtr!=nullptr)
		printf("%x\n",oldPtr);
	newPtr=(char*)realloc(oldPtr,5);
	if(newPtr!=nullptr)
		printf("%x\n",newPtr);
	//不能再释放oldPtr了，因为realloc如果返回成功(newPtr不为NULL)，说明oldPtr已经被释放
	//free(oldPtr); 重复释放
	free(newPtr);
}
