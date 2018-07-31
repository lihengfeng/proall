/*************************************************************************
	> File Name: test4.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Sun Oct 29 16:52:04 2017
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;

int main(){
	cout<<sizeof(short)<<endl;
	cout<<sizeof(int)<<endl;
	cout<<sizeof(long)<<endl;
	cout<<sizeof(float)<<endl;
	cout<<sizeof(double)<<endl;
	cout<<sizeof(long double)<<endl;

	float f=1.0;
	double d=1.0;

	// 错误 string str(10)
	string str(10,'c');

	short s1=5;
	short s2=5;
	float f1=5;
	float f2=5;
	cout<<"=============="<<endl;
	cout<<sizeof(s1+s2)<<endl;       //short自动转换为 int  
	cout<<sizeof('a'+'b')<<endl;         //字符串自动转换为 int
	cout<<sizeof(f1+f2)<<endl;    //float 应该转换为 double的，但测试没有符合

	//当int 与 unsigned int 相遇时，int转换为 unsigned，
	unsigned int u=5;
	int i=-10;
	bool b=u<i;  //结果表明u<i/
	cout<<"u<i?"<<b<<endl;
	cout<<"u+i="<<u+i<<endl;

}
