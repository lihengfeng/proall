/*************************************************************************
	> File Name: test5.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Sat Nov  4 14:30:25 2017
 ************************************************************************/
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class we{  //类内初始值不能使用圆括号的直接初始化
public:
//	int i2(5);  //错误
	int i=5;

//	string s("wew");  //错误
	string s3="wew";  
	string s2{"wew"};  
};
int main(){
	int i(5);
	int arr[5]={1,2,4,5};
	//int s[5]=arr;  //错误
//	int &a=5 ;  //错误
	const int &a2=5;
/*
 * int *q=5;  //错误，int不能给int*
	int p=q; //错误。int*不能给int
*/
	string s("wew");
	string s2="wew";
	string s3=s2+"////"+"==";
	//string s4="////"+"=="+s3  //错误;

	vector<int> vi(10);
	vector<int> vi2{10}; //1
	vector<int> vi3{10,20}; //2
	vector<string> vs(10);
	vector<string> vs2{10};
	vector<string> vs3{10,"www"};
	cout<<"vi.szie()="<<vi.size()<<endl;
	cout<<"vi2.szie()="<<vi2.size()<<endl;
	cout<<"vi3.szie()="<<vi3.size()<<endl;
	cout<<"vs.szie()="<<vs.size()<<endl;
	cout<<"vs2.szie()="<<vs2.size()<<endl;
	cout<<"vs3.szie()="<<vs3.size()<<endl;
}
