#include"../Manager.h"
#include"../ConnectSocketManager.h"
#include"../AcceptSocketManager.h"

#include<iostream>

using namespace std;
using namespace netxy;
using namespace netxy::base;
using namespace netxy::net;

class A{
public:
	void fun(int n){
		cout << "n=" << n<<endl;
	}
};

void func(int n){
	cout << "n=" << n << endl;
};

int main(){
	A a1;
	A a2;

	int a = 5;
	Epoller* ep = new Epoller();
	Manager* m = new Manager(5,ep);
	Manager* m2 = new Manager(5, ep);

	m->setReadCallback(std::bind(&A::fun, a1, 5));
	m->setReadCallback(std::bind(A::fun, a1, 5));

	m2->setWriteCallback(std::bind(func,5));
	m2->setWriteCallback(std::bind(&func, 5));


	m->doRead();
	m2->doRead();

	cout << "getEvents()=" << m->getEvents() << endl;
	cout << "getEvents()=" << m2->getRevents() << endl;

	m->addEvent(POLLIN | POLLPRI);
	m->setRevents(POLLOUT);
	

	m->doEvent();
	m2->doEvent();
	//测试m的set一系列函数

	//测试m的

}
