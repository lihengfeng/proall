/*************************************************************************
	> File Name: test1.cpp
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Wed Nov 29 14:33:32 2017
 ************************************************************************/
//测试foreach对临时对象的支持

#include<iostream>
#include<vector>
#include<functional>
#include<algorithm>
using namespace std;

template<typename T>
class Print{
public:
	Print(){
	}
	Print(const Print& p){
		cout<<"copy"<<endl;
	}
	void operator()(const T& value){
		cout<<value<<" ";
	}
};

//参数推导
template<typename InputIterator,typename Function>
Function forEach(const InputIterator &begin,const InputIterator &end,Function f){
	InputIterator it=begin;
	for(;it!=end;++it)
		f(*it);
	return f;
};
//特例化一个模板时，必须为每个模板参数都提供实参
/*
template<>
Function forEach<InputIterator*,Function>(InputIterator begin,InputIterator end,Function f){
	InputIterator it=begin;
	for(;it!=end;++it)
		f(*it);
	return f;
};
*/

//函数的特例化似乎不成立
/*
  template<typename InputIterator,typename Function>
Function forEach<InputIterator*,Function>(InputIterator begin,InputIterator end,Function f){
	InputIterator it=begin;
	for(;it!=end;++it)
		f(*it);
	return f;
};
*/


class Book{
public:
	void fun() {
		cout<<"fun";
	}
	//划重点：下面不是const成员，const成员函数中const在最后
	const void constFunError() {
		cout<<"constFun";
	}
	void constFun() const {
		cout<<"constFun";
	}
};

int main(){
	Print<int> p;
	Print<int> p2(p);
	vector<int> v{1,2,4,5,6,7};
	for(auto vl:v){
		p(vl);
	}

	//Print<int>()是一个临时对象，不是函数调用
	forEach(v.begin(),v.end(),Print<int>());

	//for_wach搭配lamba表达式
	forEach(v.begin(),v.end(),[](const int& i){
			cout<<"lamad表达式中 i="<<i<<endl;
	});


	//测试const引用是否能使用非const成员函数,
	//结果：不能使用非const，
	Book b;
	const Book& b2=b;
	b2.constFun();
	//  b2.fun(); 错误，const引用类不能使用非const成员函数
}
