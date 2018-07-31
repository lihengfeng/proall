#ifndef TIMEQUEUE_H
#define TIMEQUEUE_H

#include<netxy/base/TimeStamp.h>
#include<netxy/net/TimeFun.h>

#include<functional>
#include<vector>

using namespace std;
using namespace netxy::base;

namespace netxy{
	namespace net{
		class TimeQueue{
			public:
				typedef std::function<void()> Functor;

				TimeQueue();
				TimeQueue(const TimeQueue&  tq)=delete;
				TimeQueue& operator=(const TimeQueue&  tq)=delete;

				int  getFd(){
					return time_fd;
				}

				void addTime(TimeStamp time, const Functor& fun,int delaySeconds=0);
				void resetFd(const base::TimeStamp& ts);
				void doTimeOutEvent();
				TimeStamp setRecentlyTime();
			private:
				TimeStamp recently_time;
				std::vector<TimeFun> timeFun_list;
				int time_fd;
		};
	}
}

#endif

