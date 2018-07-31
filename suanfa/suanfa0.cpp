/*************************************************************************
  > File Name: suanfa0.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Wed Oct 25 17:13:02 2017
 ************************************************************************/

#include<iostream>
using namespace std;

#include<iostream>
using namespace std;
int nest(int i)
{
	if (i < 0 )
		return 0;
	else if (i == 0)
		return 1;
	else
		return nest(i-1) + nest(i-2) + i;
}
int main( )
{
	cout << nest(7)<< endl;
	return 1;
}
