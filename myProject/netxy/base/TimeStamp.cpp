/*************************************************************************
	> File Name: base/TimeStamp.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Mon Nov 13 22:47:10 2017
 ************************************************************************/

#include<netxy/base/TimeStamp.h>

#include<iostream>
using namespace std;

namespace netxy{
	namespace base{
		TimeStamp TimeStamp::now()
		{
			struct timeval tv;
			gettimeofday(&tv, NULL);
			int64_t seconds = tv.tv_sec;
			return TimeStamp(seconds * kMicroSecondsPerSecond + tv.tv_usec);
		}
	}
}
