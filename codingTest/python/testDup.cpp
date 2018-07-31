/*************************************************************************
  > File Name: testDup.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Mon Nov 20 17:32:37 2017
 ************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
//STDIN_FILENO标准输入描述符（0）
////STDOUT_FILENO标准输出描述符（1）
////STDERR_FILENO标准错误描述符（2）

#include<iostream>
using namespace std;

int main(){
	pid_t pid;
	int sfd=dup(1);   //保留stdout指向的打开描述符，目的是为了在后面还原stdout
	int fd=open("11.txt",O_RDWR);

	if((pid=fork())<0){
		perror("pid");
		exit(1);
	}
	if(pid==0){
		dup2(fd,1);//将stdout指向 fd所指的打开文件
	}
	else{ 
		dup2(fd,1);    
		write(1,"11111",5);
	}
	if(-1==(dup2(sfd,1))){   //还原stdout
		perror("dup2(1,sfd)");
		exit(1);
	}
	write(1,"22222",5);
	close(fd);
	close(sfd);
	printf("3333333");
}
