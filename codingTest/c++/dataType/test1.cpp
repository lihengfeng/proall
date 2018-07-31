/*************************************************************************
	> File Name: test1.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Tue Oct 17 14:41:49 2017
 ************************************************************************/

#include<iostream>
#include<string.h>
using namespace std;

//a，是指针指，代表 (int[])*类型，所以a+1的地址是加一行地址
//*(a+1) 是指针，int*类型
//a[1] 是指针，int*类型

int main(){
	int a[2][3]={{1,2,3},{2,3,4}};
	cout<<"a[0]="<<a[0]<<endl;
	cout<<"(a+0)="<<a+0<<endl;
	cout<<"*(a+0)="<<*(a+0)<<endl;
	cout<<"a[0]+1="<<a[0]+1<<endl;

	char arr[] = {4, 3, 9, 9, 2, 0, 1, 5};
	cout<<"sizeof(arr)="<<sizeof(arr)<<endl;
	cout<<"strlen(arr)="<<strlen(arr)<<endl;
	

}
