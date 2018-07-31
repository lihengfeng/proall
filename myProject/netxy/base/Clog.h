/*************************************************************************
	> File Name: log.h
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Thu Sep  7 17:26:50 2017
 ************************************************************************/
#pragma once

#include<ctime>

#include<string>
#include <sstream>
#include<iostream>
using namespace std;

string  getDate(){
	time_t t=time(0);
	struct tm* now = localtime(&t);
	std::stringstream ss;
	ss<<now->tm_year+1900<<'_'
	<<now->tm_mon<<'_'
	<<now->tm_mday;
	return ss.str();
}
string  getTime(){
	time_t t=time(0);
	struct tm* now = localtime(&t);
	std::stringstream ss;
	ss<<getDate()<<' ';
	ss<<now->tm_hour<<':'
	<<now->tm_min<<':'
	<<now->tm_sec;
	return ss.str();
}

int main(){
	cout<<getTime()<<endl;	
}
/*
class logWrite{
	write()
}
*/
