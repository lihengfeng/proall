/*************************************************************************
  > File Name: suanfa8.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Tue Oct 24 21:56:12 2017
 ************************************************************************/
利用字符重复出现的次数，编写一个方法，实现基本的字符串压缩功能。比如，字符串“aabcccccaaa”经压缩会变成“a2b1c5a3”。若压缩后的字符串没有变短，则返回原先的字符串。
给定一个string iniString为待压缩的串(长度小于等于10000)，保证串内字符均由大小写英文字母组成，返回一个string，为所求的压缩后或未变化的串。
测试样例
"aabcccccaaa"
返回："a2b1c5a3"
"welcometonowcoderrrrr"
返回："welcometonowcoderrrrr"""""""""


#include<iostream>
#include<sstream>
#include<string>
using namespace std;

int main(){
	//string iniString="eeeeeasdddeeeooooomm";
	string iniString="eeeee";
	int len=iniString.size();
	if(len==0){
		cout<<iniString<<endl;
		return ;
	}
	int n=1;
	char t=iniString[0];
	stringstream ss;
	ss<<t;
	for(int i=1;i<len;i++){
		if(iniString[i]==t){
			++n;
		}
		else{
			ss<<n;
			t=iniString[i];
			ss<<t;    //另外做法， to_string(int)转换为str
			n=1;
		}
	}
	ss<<n;
	string str=ss.str();
	cout<<"str.szie()="<<str.size()<<" len="<<len<<endl;
	if(str.size()<len) 
		cout<<str<<endl;
	cout<<iniString<<endl;
}

