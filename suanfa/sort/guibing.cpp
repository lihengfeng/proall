/*************************************************************************
	> File Name: guibing.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Fri Oct 27 10:44:15 2017
 ************************************************************************/

#include<iostream>
using namespace std;
void h(int a[],int f,int m,int e,int c[]){
	int k=0;
	int i=f,j=m+1;
	int temp=0;
	while(i<=m&&j<=e){
		if(a[i]<a[j])
			temp=a[i++];
		else	
			temp=a[j++];
		c[k++]=temp;
	}
	while(i<=m)
		c[k++]=a[i++];
	while(j<=e)
		c[k++]=a[j++];
	for(int i=0;i<k;i++)
		a[f+i]=c[i];
};
void fun(int a[],int f,int e,int temp[]){
	int m=(f+e)/2;
	if(f<e){
		fun(a,f,m,temp);
		fun(a,m+1,e,temp);
		h(a,f,m,e,temp);
	}
};

int main(){
//	int a[6]={1,4,0,-3,2,7};
	int a[6]={0,0,0,-3,0,0};
	int c[6]={0};
	fun(a,0,5,c);
	for(int i=0;i<=5;i++)
	{
		cout<<a[i]<<" "<<endl;
	}
}
