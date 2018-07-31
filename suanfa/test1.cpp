/*************************************************************************
  > File Name: test1.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Wed Nov  1 21:29:35 2017
 ************************************************************************/

#include<iostream>
using namespace std;

		double Power(double base, int exponent) {
			bool flag=false;
			if(exponent==0)
				return 1;
			if(exponent==1)        
				return base;
			if(exponent<0){
				exponent*=-1;
				flag=true;
			}
			double result=Power(base,exponent/2);
			result=result*result;
			if(exponent&1)
				result=result*base;
			if(flag)
				result=1/result;
			return result;
		}
int main(){

	double b=5;
	double s=Power(2,-2);

	cout<<s<<endl;

	int ar[4]={1,2,3,4};
	int i=1;
	ar[i--]=ar[i];
	cout<<ar[0]<<ar[1]<<endl;

}
