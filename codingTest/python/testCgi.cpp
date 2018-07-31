/*************************************************************************
	> File Name: testCgi.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Tue Nov 21 19:50:51 2017
 ************************************************************************/
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include<iostream>
using namespace std;

//lseek与fsee();
//dup 与dup2
//execl 参数形式
//打开一个文件，read指针和write是同一个。

int main(){
	int fd1=open("11.txt",O_RDWR);
	int fd2=open("22.txt",O_RDWR);
	int sin=dup(0);
	int sout=dup(1);

	dup2(fd1,0);
	dup2(fd2,1);

	write(fd1,"1234567&7654321",15);   //这里写入后，
	lseek(fd1,0,SEEK_SET);


	execl("dd.py","dd.py",NULL);

	dup2(sin,0);
	dup2(sout,1);
}
