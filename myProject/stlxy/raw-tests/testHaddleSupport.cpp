/*************************************************************************
	> File Name: testHaddleSupport.cpp
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Fri Dec  1 19:17:53 2017
 ************************************************************************/

#include<iostream>
#include"HandlerSupport.h"
using namespace std;

void f(){
	cout<<"out of memory !!!!!!!!!"<<endl;
	abort();
};
class Book:public HandlerSupport<Book>{
public:
private:
	int i[1000000000];
};
int main(){
	Book::setHandler(f);
	Book* b=new Book();
	delete b;
	cout<<"end"<<endl;
}
