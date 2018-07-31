/*************************************************************************
	> File Name: testUnion.cpp
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Tue Nov 28 14:36:13 2017
 ************************************************************************/

#include<iostream>
using namespace std;

//union默认所有成员都是public,=struct
//union定义的类不能继承其他类
//union定义的类不能被继承
union UA{
	//可以有构造函数
	UA(){
	}
	~UA(){//可以由析构函数
	}
	//错误 union中不能有虚函数
	virtual Fun(){
	}
private:
	int &a; //不能有引用

}

//可以声明不带民资的union类型，但是不能有成员函数
union{
	//错误，匿名union不能有成员函数
	void f();
	//不能含有privte成员
	private:
	int na;
	//错误，也不能有protected成员
	protected:
	int nb;
}
//在定义union的作用域，该union中成员都是可以直接实用的，也就是不需要带上union名字
na=6; //这里de na代表的是上边匿名union的na
nb=0; //这里de nb代表的是上边匿名union的bn

int main(){
}
