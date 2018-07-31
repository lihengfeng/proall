/*************************************************************************
	> File Name: testStract.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Tue Nov 21 13:42:51 2017
 ************************************************************************/
#include<string.h>

#include<iostream>
#include<string>
using namespace std;

int main(){
	ostream& os=cout;
	char buf[1024];
	sprintf(buf,"wanghao\r\n");
	strcat(buf,"lihengfeng\r\n");
	strcat(buf,"haha\r\n");
	os<<buf<<endl;

	string str(buf);
	str.append("baobao");
	os<<str<<endl;
}
