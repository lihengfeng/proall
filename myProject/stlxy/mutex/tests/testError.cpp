/*************************************************************************
	> File Name: tests/testError.cpp
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Tue Nov 28 13:18:09 2017
 ************************************************************************/

#include<iostream>
using namespace std;
Class {
public:
	//构造函数处理异常
	//（1）参数上的异常，属于调用表达式的异常，归上层调用者管理，
	//如果是成员函数初始化的异常，需要由构造函数处理
	A(int i):index(i){  //

	}
	~A{  //析构函数中如果出现异常，一定在内部处理，不能抛到外层中，因为析构函数必须要释放掉资源
		try{
		}catch(my_error& er){
		}

	}
private:
};
int main(){
	try{

}
