/*************************************************************************
	> File Name: testEnv.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Tue Nov 21 21:47:26 2017
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include <fcntl.h>
#include<iostream>
#include<string>
#include <sys/wait.h>
using namespace std;


int main(){
	char buf[1204]={0};
	int fd=open("cgiOut.txt",O_RDWR);
	read(fd,buf,1024);
	cout<<buf<<endl;
	int sout=dup(1);
	dup2(fd,1);
	string str("99999999");
	str="con="+str;
	putenv(const_cast<char*>(str.c_str()));

	pid_t pid=fork();
	if(pid==0){
		execl("testEnv.py","testEnv.py",NULL);
	}
	else if(pid>0){
		waitpid(pid,NULL,0);
		lseek(fd,0,SEEK_SET);
		dup2(sout,1);
		cout<<"execl结束"<<endl;
		char buf[1024]={0};
		read(fd,buf,1024);
		cout<<buf<<endl;
		close(fd);
		close(sout);
	}
}
