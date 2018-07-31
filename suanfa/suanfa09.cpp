/*************************************************************************
  > File Name: suanfa09.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Wed Oct 25 17:37:39 2017
 ************************************************************************/

#include<iostream>
using namespace std;

int main( )
{
	int k=0;
	char c='A';
	do{
		switch (c++)
		{
			case 'A': k++; break;
			case 'B': k--;
			case 'C': k+=2; break;
			case 'D': k=k%2; break;
			case 'E': k=k*10; break;
			default: k=k/3;
		}
		k++;
	}while(c<'G');
	cout<<k<<endl;
}
