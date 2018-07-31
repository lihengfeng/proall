/*************************************************************************
	> File Name: testSharedPtr.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Thu Nov  9 16:46:02 2017
 ************************************************************************/

#include<iostream>
#include<memory>
#include<vector>
#include<thread>
using namespace std;

void deleter(int* p){
	delete p;
	cout<<"删除了p"<<endl;
}

void fun(){
	cout<<"fun"<<endl;
}
int main(){
	int *p=new int;
	int *p2=new int;
	shared_ptr<int> sp(p,deleter); 

	vector<shared_ptr<int>> v;
	v.push_back(sp);

	thread* t=new thread(&fun);
	t->join();
	delete t;

	shared_ptr<int> sp(p2,deleter); 
	unique_ptr<int> up(p2,deleter);   //错误，unique 使用删除器，需要传入删除器的函数类型，需要传入函数指针
	unique_ptr<int,decltype(deleter)> up(p2,deleter); //错误，decltype(函数) 只能得到函数类型，无法获得函数指针
	unique_ptr<int,decltype(deleter)*> up(p2,deleter);//正确，在decltype()后加上了* 


}
