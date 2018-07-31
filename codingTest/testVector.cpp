/*************************************************************************
	> File Name: test.cpp
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Thu Dec 28 16:41:59 2017
 ************************************************************************/

#include<iostream>
#include<string>
#include<vector>
using namespace std;
namespace A{
	void fun();
}
	void A::fun(){
		cout<<"ss";
	}
namespace B{
	/*
	void A::fun(){
		cout<<"ss";
	}*/
}


int main(){
	vector<string> v1(10);
	cout<<"size()="<<v1.size()<<endl;
	vector<string> v2(10.2);
	cout<<"size()="<<v2.size()<<endl;
	vector<string> v3('0');
	cout<<"size()="<<v3.size()<<endl;
	vector<string> v4('0',"hi");
	cout<<"size()="<<v4.size()<<endl;
	vector<string> v5{"hi"};   
	cout<<"size()="<<v5.size()<<endl;
	vector<string> v6{10};      
	cout<<"size()="<<v6.size()<<endl;

	vector<string> v7{10,"hi"};
	cout<<"size()="<<v7.size()<<endl;
	vector<string> v72{10.3,"hi"};
	cout<<"size()="<<v72.size()<<endl;
	vector<string> v73{'c',"hi"};
	cout<<"size()="<<v73.size()<<endl;
	
	
	cout<<"============="<<endl;
	vector<int> v8{10};       
	cout<<"size()="<<v8.size()<<endl;
	vector<int> v9{10,20};       
	cout<<"size()="<<v9.size()<<endl;
	vector<int> v10{10.2};       
	cout<<"size()="<<v10.size()<<endl;
	vector<int> v11{'x','c'};       
	cout<<"size()="<<v11.size()<<endl;

	vector<char> v12{10};       
	cout<<"size()="<<v12.size()<<endl;
	//虽然有{},但值不符合列表初始化，而且也无法当作值初始化的参数
//	vector<string> v9{"hi",6};
}
