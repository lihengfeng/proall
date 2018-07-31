/*************************************************************************
  > File Name: suanfa6.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Tue Oct 24 12:45:52 2017
 ************************************************************************/

#include<iostream>
using namespace std;

int main(){
	int n;
	while(cin>>n){
		int len[10001];
		int a[10001];  //存放数字
		int max2=0;
		for(int i=0;i<n;i++)
			cin>>a[i];
		for(int i=0;i<n;i++)
			len[i]=1;
		for(int i=0;i<n;i++){
			for(int j=0;j<i;j++)
				if(a[j]<a[i])
					len[i]=max(len[i],len[j]+1);
			//len[i]=max(len[i],len[j]+1);
			if(len[i]>max) 
				max2=len[i];
		}
		cout<<max2<<endl;        
	}
}
