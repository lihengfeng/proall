/*************************************************************************
  > File Name: test20.cpp
  > Author: lihengfeng
  > Mail: 17704623602@163.com 
  > Created Time: Sat Dec 23 20:02:15 2017
 ************************************************************************/

#include<iostream>
using namespace std;

constexpr int getMess(int i){
	using F= int; //ok 可以含有typedef声明这样的非执行语句
	typedef int intPtr; //ok
//	cout<<"laji"<<endl;  //error  不能含有除return语句之外的执行语句
	return 43;
}


int main(){
	// int i=8;  如果这里是非const的，那么下边arr无法正常初始化，数组的参数必须是常量变量(const)或者常量表达式(constexpr)
	const int i=8;
	constexpr int i2=8;
	int arr[i]={1,24,3};
	int arr2[i2]={2,3,4,5};
	cout<<arr[2]<<endl;
}
