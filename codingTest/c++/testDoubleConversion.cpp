/*************************************************************************
  > File Name: test1222.cpp
  > Author: lihengfeng
  > Mail: 17704623602@163.com 
  > Created Time: Fri Dec 22 21:52:57 2017
 ************************************************************************/
//比较 非内置类型构造函数上的连续隐氏转换，以及内置类型的连续隐氏转换 
//结果： 内置类型隐氏转换可以连续多步，非内置类型无法连续转换

#include<iostream>
using namespace std;

struct B;

struct A{
	A()=default;
	A(const B& b){
		cout<<"A(const B&)"<<endl;
	};  //单参数转换
};

struct B{
	operator A()const{
		cout<<"operaotr A()"<<endl;
	}; 
};

void  fun(const A& a){
}

struct So{
	So(string str){
		cout<<str<<endl;
	}
};

//测试能否二次转换
void fun2(const So& s){

}

class IntNum{
	public:
	IntNum(int value){
		cout<<"value="<<value<<endl;
	};  //必须只有一个参数的才可以自动转换，所以也叫转换构造函数，当然多个参数如果有默认实参也可以。
};

int main(){
	B b;
	A a=b;
	IntNum i1=5;    //正确，5转换为Intnum
	IntNum i2=5.3;     //正确，编译器先将5.3转换为5，然后5再到intnum； 

	So s="sss";  //error ，虽然可以让sss变为string,然后string再变为 So类型，但显然编译器无法推测处过程.
	//fun(b.operator A());
	//fun2("ssss");
}
