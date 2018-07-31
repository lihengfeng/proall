/*************************************************************************
  > File Name: TimeStamp.h
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Mon Nov 13 22:30:39 2017
 ************************************************************************/

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
				explicit TimeStamp(int64_t us){
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

				void addSeconds(int64_t s){
					secondsSinceEpoch_ += s;
					microSecondsSinceEpoch_ += s * 1000 * 1000;
				}
				int64_t getSecondsSinceEpoch_(){
					return  secondsSinceEpoch_;
				}
				int64_t getSecondsSinceEpoch_() const{
					return  secondsSinceEpoch_;
				}
				int64_t getMicroSecondsSinceEpoch_() {
					return  microSecondsSinceEpoch_;
				}
				int64_t getMicroSecondsSinceEpoch_() const{
					return  microSecondsSinceEpoch_;
				}

				static TimeStamp now();

				static const int64_t kMicroSecondsPerSecond = 1000 * 1000;
			private:
				int64_t microSecondsSinceEpoch_;
				int64_t secondsSinceEpoch_;
		};

	}
}

#endif
