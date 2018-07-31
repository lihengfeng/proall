/*************************************************************************
	> File Name: testUnion.cpp
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Mon Dec  4 19:37:44 2017
 ************************************************************************/

#include<iostream>
using namespace std;
union obj{
	obj* next;
	char address[1];
	int value;
};
int main(){
	char cs[128]={'c'};
	char* cptr=cs;
	obj*volatile p=reinterpret_cast<obj*>(cptr); 
	p->value=5;
	cout<<p->value<<endl;
}
