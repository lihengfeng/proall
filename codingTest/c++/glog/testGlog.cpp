/*************************************************************************
  > File Name: testGlog.cpp
  > Author: lihengfeng
  > Mail: 17704623602@163.com 
  > Created Time: Wed Jan  3 18:10:32 2018
 ************************************************************************/


/*
int main()

{
	google::InitGoogleLogging("init");
	google::SetLogDestination(google::GLOG_INFO, "./myInfo");
	LOG(WARNING) << "thisis the 1st warning!";
	return 0;
}*/

#include<iostream>
#include <glog/logging.h>
#include <glog/raw_logging.h>



class GLogHelper

{

	public:

		GLogHelper(char*program)

		{

			google::InitGoogleLogging(program);

			FLAGS_stderrthreshold = google::INFO;

			FLAGS_colorlogtostderr = true;

			FLAGS_v = 3;

		}

		~GLogHelper()

		{

			google::ShutdownGoogleLogging();

		}

};



int main()

{

	GLogHelper("start");

	LOG(ERROR) <<"LOG";

	VLOG(3) <<"VLOG";

	DLOG(ERROR) <<"DLOG";

	DVLOG(3) <<"DVLOG";

	SYSLOG(ERROR) <<"SYSLOG";

	PLOG(ERROR) <<"PLOG";

	RAW_LOG(ERROR,"RAW_LOG");

}
