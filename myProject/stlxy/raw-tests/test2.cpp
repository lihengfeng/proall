/*************************************************************************
	> File Name: test2.cpp
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Wed Nov 29 16:08:42 2017
 ************************************************************************/
//for_each使用两个参数以上的函数

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
using namespace std::placeholders;

void f1(int n){
	cout<<n<<endl;
}
void f2(const char*s,int n){
	cout<<s<<n<<endl;
}

template<typename T>
class Print{
public:
	Print(){
	}
	Print(const char* s):ptr(s){
	}
	Print(const Print& p){
		cout<<"copy"<<endl;
	}
	void operator()(const T& value){
		cout<<ptr<<value<<endl;
	}
private:
	const char* ptr=nullptr;
};

int main(){
	vector<int> v{1,2,4,5,6,7};
	for_each(v.begin(),v.end(),f1);
	char*c= "n=";
	for_each(v.begin(),v.end(),std::bind(f2,c,_1));
	for_each(v.begin(),v.end(),std::bind(f2,"n=",_1));

	//使用重载()的类+临时对象 
	for_each(v.begin(),v.end(),Print<int>("value="));
	//直接使用lambda
	//lambda的捕获列表中只能使用当前作用域中的局部变量或者非const变量
	//但是对于不在当前函数的变量或者静态局部变量可以直接函数体内部使用
	char *s="value=";
	auto f=[s](int n){
		cout<<s<<n<<endl;
	};
	for_each(v.begin(),v.end(),f);

}
