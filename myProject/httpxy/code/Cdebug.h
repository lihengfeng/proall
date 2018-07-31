/*************************************************************************
  > File Name: Debug.h
  > Mail: 17704623602@163.com 
  > Created Time: Fri Sep  8 11:00:23 2017
 ************************************************************************/
#ifndef CDEBUG_H
#define CDEBUG_H

#include<stdio.h>
#include<sys/time.h>
#include<ctime>

#include<string>
#include <sstream>
#include<iostream>

using std::string;
using std::stringstream;
using std::cout;
using std::cerr;
using std::endl;


		class Cdebug{
			public:
				Cdebug(const string& str1,const string& str2):fileName(str1),funName(str2){
				}
				~Cdebug(){
				}

		static string getTime(){
			time_t t=time(0);
			struct timeval tv;
			gettimeofday(&tv,NULL);
			struct tm* now = localtime(&t);
			std::stringstream ss;
			ss<<now->tm_hour<<':'
				<<now->tm_min<<':'
				<<now->tm_sec<<":   ";
			//因为time_t只能获取到秒，所以精确到毫秒需要timeval格式，并且用gettimeofday获取.
			//gettimeofday(&tv,NULL);
			//ss<<tv.tv_usec/1000<<"  ";
			return ss.str();
		};
		template<typename... Args> 
			static	void printValue(const string& fileName,const string& funName,const Args&... args){
				stringstream ss;
				ss<< getTime();
				ss<<"  ";
				ss<<fileName<<" :"<<funName<<"()  ";
				print(ss,args...);
				cout<<ss.str()<<endl;
			}
		template<typename... Args> 
			static void printError(const string& fileName,const string& funName,const Args&... args){
				stringstream ss;
				ss<< getTime();
				ss<<"  ";
				ss<<fileName<<" :"<<funName<<"()  ";
				print(ss,args...);
				cerr<<ss.str()<<endl;
			}


		template<typename T>
			static void print(stringstream& ss,const T&t){
				ss<<t;
			}
		template<typename T,typename... Args>
			static void print(stringstream& ss,const T&t,const Args&... args){
				ss<<t;
				print(ss,args...);
			}
		/*		static string  getTime();
				template<typename T>
					static void print(stringstream& ss,const T&t);
				template<typename T,typename... Args>
					static void print(stringstream& ss,const T&t,const Args&... args);
				template<typename... Args> 
					static void printValue(const string& fileName,const string& funName,const Args&... args);
				template<typename... Args> 
					static void printError(const string& fileName,const string& funName,const Args&... args);
*/
			private:
				const string funName;
				const string fileName;
		};

 
  
#define debug_value(args...)  Cdebug::printValue(__FILE__,__FUNCTION__,args)
#define debug_error(args...)  Cdebug::printError(__FILE__,__FUNCTION__,args)

#endif

