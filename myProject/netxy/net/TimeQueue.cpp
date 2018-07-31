/*************************************************************************
  > File Name: TimeQueue.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Sat Nov 11 14:11:30 2017
 ************************************************************************/

#include<netxy/base/Cdebug.h>
#include<netxy/net/TimeQueue.h>

#include<assert.h>
#include <sys/time.h>
#include <sys/timerfd.h>
#include <string.h>

#include<map>
#include<iostream>
namespace netxy{
	namespace net{

		TimeQueue::TimeQueue(){
			time_fd = timerfd_create(CLOCK_REALTIME, 0);
			assert(time_fd!=-1);
		}
		void TimeQueue::addTime(TimeStamp time, const Functor& fun,int delaySeconds){
			assert(delaySeconds>=0);
			TimeFun tf(time, fun,delaySeconds);
			timeFun_list.push_back(tf);
			if (time < recently_time||timeFun_list.size()==1){   
				recently_time = time;
				resetFd(time);
			}
		}
	void TimeQueue::resetFd(const base::TimeStamp& ts)
	{//更新timefd的里的超时时间
			int64_t seconds = ts.getSecondsSinceEpoch_();
			int64_t nseconds =(ts.getMicroSecondsSinceEpoch_()%(1000*1000))*1000;
			struct itimerspec new_value;
			struct itimerspec old_value;
			bzero(&new_value,sizeof new_value);
			if(timeFun_list.empty()){ //队列内无值，停止定时器
				debug_error("timeFun_list is empty(), stop timerfd");
				int ret=timerfd_settime(time_fd,1,&new_value,NULL);
				assert(ret!=-1);
				 ;
				return ;
			}
			new_value.it_value.tv_sec = static_cast<time_t>(seconds);
			new_value.it_value.tv_nsec = static_cast<long>(nseconds);
			int ret=timerfd_settime(time_fd,1, &new_value, NULL);
			//cout<<"timefd_settime()的返回值ret="<<ret<<endl;
			assert(ret!=-1);
			 ;
		}
		void TimeQueue::doTimeOutEvent(){//执行超时函数
			TimeStamp now;

			for (std::vector<TimeFun>::iterator it = timeFun_list.begin(); it != timeFun_list.end(); ){   
				if (it->getTime()< now){    //判断是否大于当前时间，如果大于后就判断是否是循环的timeStamp,不是循环的就删除
					it->run();
					if(it->restart()){	//调用restart，如果是重复进行restart就会成功，并且返回true。
						it++;
					}
					else{ 
						debug_error("run end. timeFun is not circulTime. erase");
						it=timeFun_list.erase(it); //删除元素，返回值指向已删除元素的下一个位置,因为删除不会影响迭代器的++，所以可以在for循环里删
					}
				}
				else it++;
			}
			setRecentlyTime();
			resetFd(recently_time);
		}

		TimeStamp TimeQueue::setRecentlyTime(){  //求出距离当前时间最近的定时器
			base::TimeStamp min_time(0);
			if(!timeFun_list.empty()){
				min_time =timeFun_list.front().getTime();
				for (std::vector<TimeFun>::iterator it = timeFun_list.begin(); it != timeFun_list.end(); ++it){
					if (it->getTime() > min_time)
						min_time = it->getTime();
				}	
			}
			recently_time = min_time;
		}
	}
}


