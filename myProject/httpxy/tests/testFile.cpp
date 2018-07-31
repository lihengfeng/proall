/*************************************************************************
	> File Name: tests/testFile.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Wed Nov 22 14:52:35 2017
 ************************************************************************/

#include<iostream>
#include<string>
#include<fstream>
using namespace std;

void cat(ifstream& fs){  //发送文件内容
	string str;
	while(getline(fs,str)){
		int len=str.size();
		cout<<str<<endl;
		cout<<"len="<<len<<endl;
	}
}
int main(){
	string str;
	ifstream ifs;
	ifs.open("1.dat");
	if(ifs){
		cat(ifs);
	}
	else
		cout<<"fs.open error"<<endl;
	ifs.close();
}
