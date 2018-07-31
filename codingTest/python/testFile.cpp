/*************************************************************************
	> File Name: testFile.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Tue Nov 21 20:56:25 2017
 ************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include<iostream>
using namespace std;

int main(){
	int fd1=open("11.txt",O_RDWR);
	int fd2=open("22.txt",O_RDWR);

	char buf[20];
	read(fd2,buf,20);
	cout<<buf<<endl;

	write(fd2,"999999999",10);

	close(fd1);
	close(fd2);


}
