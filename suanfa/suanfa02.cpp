/*************************************************************************
	> File Name: suanfa02.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Wed Oct 25 17:18:13 2017
 ************************************************************************/

#include<iostream>
using namespace std;

int main(void)
{
	std::string str1("trend");
	std::string str2("micro");
	std::string& strs = str1;
	std::string* ptrs = &str1;
	strs = str2;
	cout<<strs<<endl;
	cout<<str1<<endl;
	ptrs = &str2;
	//enum team { my , your = 9 , his , her = his + 3};
	//printf("%d %d %d %d\n",my , your , his , her);
	return 0;
}
