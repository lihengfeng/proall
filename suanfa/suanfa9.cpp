/*************************************************************************
  > File Name: suanfa9.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Wed Oct 25 11:14:51 2017
 ************************************************************************/

#include<iostream>
using namespace std;


int main(){
	int m=0;
	int n=0;
	cin>>m;
	cin>>n;
	int f[10000]={0};  //代表m个0个盘子
	f[0]=1;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=m;j++)
			f[j]=f[j]+f[j-i];   //f[1]=1;  f[2]=f[2]+f[1]  0+1+1
	cout<<f[m]<<endl;
}
