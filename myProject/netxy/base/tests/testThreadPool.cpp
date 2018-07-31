
#include<netxy/base/CountDownLatch.h>
#include<netxy/base/ThreadPool.h>


#include<iostream>

using namespace std;
using namespace netxy::base;


class A{
public:
	void fun(int n){
		cout << "n=" << n << endl;
	}
};

void print(const std::string& str){
	std::cout << str<<std::endl;
	sleep(1);
};

void test(int n){
	cout<< "Test ThreadPool with max queue size = "<<n<<endl;
	ThreadPool tp(n);
	tp.start(5);
	for(int i=0;i<40;++i){
		char buf[32];
		snprintf(buf, sizeof buf, "task %d", i);
		tp.run(std::bind(print, std::string(buf)));
	}	
	cout<<"DONE"<<endl;
	cout<<"DONE"<<endl;
	cout<<"DONE"<<endl;

	//这里为什么要用countDownLatch，因为这个保证了主线程等待工作线程全部完成。
	//因为ThreadPool中deque存的事件是顺序取出，当CountLownLatch被取出时，其他事件一定也被取出了，除非其他事件执行时间很长，一般都能保证其他事件执行完成。
	CountDownLatch cdl(1);
	tp.run(std::bind(&CountDownLatch::countDown,&cdl));
	
	cdl.wait();
	tp.stop();
}

int main(){
	//test(5);
	test(10);
	//test(50);
}
