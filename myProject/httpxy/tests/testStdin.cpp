/*************************************************************************
	> File Name: testStdin.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Tue Nov 21 15:06:28 2017
 ************************************************************************/
//测试stdin缓冲区的请款
#include<string.h>

#include<iostream>
#include<string>
using namespace std;


//几个往键盘中写的函数
//fputs("");
//fprintf("");
//ungtec('',stdin)  ,把单个字符读入stdin的键盘缓冲区，但是还需要从键盘中输入'\n'才能触发.
//
//sprintf();  往地址中写

int main(){
	char buf[128];
	
	ungetc('c',stdin);   //往键盘缓冲区读入一个字符，键盘缓冲区不等于cin的输入缓冲区，cin是从系统缓冲区读入的.所以需要再键盘上按下'\n',将键盘中东西送入系统缓冲区
	ungetc('s',stdin);
	ungetc('n',stdin);

	//fprintf(1 ,"123456789");   //错误, 第一个参数是file*类型 
	//fputs("content-length",1);   //第二参数是file类型，不能传文件描述符,虽然 1 是stdout的文件描述 
	//fputs("content-length",stdout);
	//fprintf(stdout,"123456789");   

	char c=getchar();  //直接从键盘缓冲区读，不需要按下'\n',
	cout<<c<<endl;

	gets(buf,sizeof(buf));
	//fgets(buf,sizeof(buf));
	cout<<buf<<endl;

	string str;  
	cin>>str;  //这里读取不成功，必须键盘上按'\n'之后才能正常读.
	cout<<str<<endl;


}
