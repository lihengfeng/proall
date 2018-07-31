/*************************************************************************
	> File Name: TimeFun.h
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Sat Nov 11 14:10:26 2017
 ************************************************************************/

#include<netxy/base/TimeStamp.h>
#include<iostream>
using namespace std;

namespace netxy{
	namespace net{
		class TimeFun{
			public:
				typedef std::function<void()> Functor;

				TimeFun(const base::TimeStamp& time,const Functor& fun,int ds=0):ts(time),delaySeconds(ds){
					f=fun;  //因为function好像不能copy构造.
				}
				base::TimeStamp getTime(){
					return ts;
				}
				void run(){
					f();
				}
				bool restart(){
					if (delaySeconds<=0)
						return false;
					else 
						ts.addSeconds(delaySeconds);
					return true;
				}
				base::TimeStamp ts;
				Functor  f;
				int delaySeconds;
		};
	}
}
