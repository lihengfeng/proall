/*************************************************************************
	> File Name: test6.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Thu Oct 19 12:07:42 2017
 ************************************************************************/
//验证string的构造方法

#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main(){
	
	string str1("www");
	string str2="www";
//string str3(5); //一个参数的只能是字符串,但是 vector可以这样使用 vector<int> v(5);
	string str3(10,'c');
	string str4('1','c'); //这里把'1'当做ascll，然后转为int类型
//	string str4=(10,'c');  错误，只有一个参数的才能转换 string(10,'c')。

	cout<<str1<<endl;
	cout<<str2<<endl;
	cout<<str3<<endl;
	cout<<str4<<endl;

	vector<int> v1('c');  //可以
	//vector<char> v4='c';   //不可以
//	vector<char> v4=6;   //不可以
	vector<char> v2(10,'b');  //可以
	//vector<char> v6=(10,'c');  //不可以
	vector<char> v7=vector<char>(10,'c');  //可以
	vector<char> v3(v2);  
	vector<char> v5=v2;

	vector<char> v8={'1','c','7'}; //可以
	vector<char> v9{'1','c','5'};  //
	vector<int*> v0('u'); //可以,但是把字符的ascll当作了 int,相当于 v0(117);
	vector<int> v01('u',7); //可以,因为是把'u'当作ascll 117  v0(117,7);
//	vector<int> v02('u',7,'v'); //不可以,即使把'u'当作ascll没，参数也吵了
//	vector<char> v0('u','c','d','e'); //

	cout<<"v1.size()="<<v1.size()<<endl;
	cout<<"v2.size()="<<v2.size()<<endl;
	cout<<"v7.size()="<<v7.size()<<endl;
	cout<<"v8.size()="<<v8.size()<<endl;
	cout<<"v9.size()="<<v9.size()<<endl;
	cout<<"v0.size()="<<v0.size()<<endl;
	cout<<"v01.size()="<<v01.size()<<" i="<<v01.front()<<endl;
	//cout<<"v02.size()="<<v02.size()<<endl;


//cout<<"v0.size()="<<v0.size()<<endl;

}

