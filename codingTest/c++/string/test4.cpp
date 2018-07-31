/*************************************************************************
	> File Name: test4.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Wed Oct 18 15:31:10 2017
 ************************************************************************/

#include<iostream>
using namespace std;

int main(){
	char ch[20],b,c;
	string str;
//	cin>>b;  //缓冲区的enter不会被读出,也不会被丢弃。所以缓冲区还有enter,所以如果只输入一个字符，然后按enter，getline，就会读出enter，并结束，str为空字符串，
	cin.get(c);  //等价于 b=cin.get();缓冲区的,空格,enter会被读出,所以缓冲区只有enter，get也能读到值

	getline(cin,str); //缓冲区enter会被读出，但不会被送入str,所以缓冲区没有neter了,而且键盘输入只有enter,也会结束，不过str是空字符串。
//	cin.get(str,5,'0');   ///第一个参数不能是string类型.
	cin.get(ch,5,'0');   ///缓冲区的enter也会被读出/

	//	cout<<"ch="<<ch<<endl;  
//	cout<<"b="<<(int)b<<endl;  
		cout<<"c="<<(int)c<<endl;  
	cout<<"str="<<str<<" str.empty="<<str.empty()<<endl;  

}
