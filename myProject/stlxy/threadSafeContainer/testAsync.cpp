/*************************************************************************
	> File Name: testAsync.cpp
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Mon Dec 11 12:09:39 2017
 ************************************************************************/
#include<unistd.h>

#include<iostream>
#include <future>
int find_the_answer_to_ltuae(){
	sleep(3);
	return 8;
}

void do_other_stuff(){
	std::cout<<"do struff "<<std::endl;
}
int main()
{
	std::future<int> the_answer=std::async(std::launch::deferred | std::launch::async,find_the_answer_to_ltuae);
	sleep(3);
	do_other_stuff();
	the_answer.wait();
	std::cout<<"The answer is "<<the_answer.get()<<std::endl;
	//std::cout<<"The answer is "<<the_answer.get()<<std::endl;
}

