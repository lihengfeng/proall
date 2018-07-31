/*************************************************************************
	> File Name: ../base/TimeStamp2.h
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Wed Nov 15 15:17:56 2017
 ************************************************************************/

#include<iostream>
using namespace std;

#ifndef TIMESTAMP_H 
#define TIMESTAMP_H

#include<netxy/base/Cdebug.h>

#include <sys/time.h>
#include <sys/timerfd.h>

#include<functional>
#include<iostream>
using namespace std;

namespace netxy{
	namespace base{
		class TimeStamp{
			public:
				TimeStamp(){   //如果没有参数，默认构造出当前的时间
					struct timeval tv;
					gettimeofday(&tv, NULL);
					secondsSinceEpoch_=tv.tv_sec;
					microSecondsSinceEpoch_=secondsSinceEpoch_ * kMicroSecondsPerSecond + tv.tv_usec;
				};
				explicit TimeStamp(size_t us){
					secondsSinceEpoch_ = us/kMicroSecondsPerSecond;
					microSecondsSinceEpoch_ = us;
				}
				TimeStamp(const TimeStamp& ts):secondsSinceEpoch_(ts.getSecondsSinceEpoch_()),microSecondsSinceEpoch_(ts.getMicroSecondsSinceEpoch_()){
				}

				TimeStamp& operator=(const TimeStamp& ts){
					this->secondsSinceEpoch_ = ts.getSecondsSinceEpoch_();
					this->microSecondsSinceEpoch_ = ts.getMicroSecondsSinceEpoch_();
					return *this;
				}
				bool operator>(const TimeStamp& ts){  
					return microSecondsSinceEpoch_ > ts.microSecondsSinceEpoch_;
				}
				bool operator<(const TimeStamp& ts){
					return microSecondsSinceEpoch_ < ts.microSecondsSinceEpoch_;
				}
				bool operator==(const TimeStamp& ts){
					return microSecondsSinceEpoch_ == ts.microSecondsSinceEpoch_;
				}

				void addSeconds(size_t s){
					secondsSinceEpoch_ += s;
					microSecondsSinceEpoch_ += s * 1000 * 1000;
				}
				size_t getSecondsSinceEpoch_(){
					return  secondsSinceEpoch_;
				}
				size_t getSecondsSinceEpoch_() const{
					return  secondsSinceEpoch_;
				}
				size_t getMicroSecondsSinceEpoch_() {
					return  microSecondsSinceEpoch_;
				}
				size_t getMicroSecondsSinceEpoch_() const{
					return  microSecondsSinceEpoch_;
				}

				static TimeStamp now();

				static const int kMicroSecondsPerSecond = 1000 * 1000;
			private:
				size_t microSecondsSinceEpoch_;
				size_t secondsSinceEpoch_;
		};

	}
}

#endif
