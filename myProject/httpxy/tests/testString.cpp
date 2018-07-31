/*************************************************************************
  > File Name: tests/testString.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Wed Nov 22 12:45:54 2017
 ************************************************************************/

#include<sstream>
#include<iostream>
#include<string>
using namespace std;


int fun(void){
	string method("cccc");
	string url("cccc");
	string params("cccc");
	if(method=="GET"){
		//static_cast不能把const* 转换为非const*
		//char *c=static_cast<char*>(url.c_str());
		char *c=const_cast<char*>(url.c_str());
		while((*c!='?')&&(c!='\0')){
			c++;
		}
		if(*c=='?'){
		}
	}
};
int main(){
	char buf[128]="12345678 444 333    777";
	string str(buf); 
	cout<<str<<endl;
	cout<<"str.size()="<<str.size()<<endl;

	//这段测试strigstream 如果碰到多个空格，能否正常分割
	istringstream iss(buf);
	string str1; 
	string str2; 
	string str3; 
	iss>>str1;
	iss>>str2;
	iss>>str3;

	cout<<str1<<endl;
	cout<<str2<<endl;
	cout<<str3<<endl;
	
	char *c=const_cast<char*>(str1.c_str());
	while((*c!='4')&&(c!='\0')){
		c++;
	}
	if(*c=='4'){
		*c='\0';
	}
	//如果只是将'c'设置为'\0',str1既显示'\0'之前又显示'\0'之后.
	cout<<"str1="<<str1<<endl;
	cout<<"str1.size()="<<str1.size()<<endl;
	//通过重新构造string,能够只显示'\0'之前.
	str1=string(str1.c_str());
	cout<<"str1="<<str1<<endl;
	cout<<"str1.size()="<<str1.size()<<endl;
	

	//测试string(char*)类型
	string str4(c+1);
	cout<<"str4="<<str4<<endl;
	cout<<"str4.size()="<<str4.size()<<endl;

	//测试引用的string拼接后能否影响被引用的string。
	string &path=str1;
	path=path+"000000";
	cout<<"str1="<<str1<<endl;
	cout<<"str1.size()="<<str1.size()<<endl;



}
