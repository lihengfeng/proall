/*************************************************************************
	> File Name: tests/testSprintf.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Thu Nov 23 10:45:48 2017
 ************************************************************************/

#include<iostream>
#include<string>
#include<string.h>
using namespace std;

class HttpServer{ //主要测试char[]能否在类中正常应用
	public:
		HttpServer(const char*name){
			sprintf(serverName,"Server: %s/0.1.0\r\n",name);
		}
		void print(){
			char buf[256];
			sprintf(buf,"123456789\r\n");
			strcat(buf,serverName);
			cout<<buf<<endl;
		}
	private:
			char serverName[128];
};
int main(){
	char buf[129];
	char buf2[129];
	string str("12345");
	sprintf(buf,"999%s",str.c_str());
	sprintf(buf2,"999%s",str.data());
	cout<<buf<<endl;

	HttpServer hs("qqqqqqqqqq");
	hs.print();
}
