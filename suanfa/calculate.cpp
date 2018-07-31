/*************************************************************************
  > File Name: suanfa4.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Sun Oct 22 22:21:58 2017
 ************************************************************************/

#include<iostream>
using namespace std;


//解析，这里采用是将n右移，然后和1与计算1的个数，但这种情况遇到n是负数，会出错，因为负数最高位为1，右移导致无限循环，
//负数的算数右移会加1,因为考虑的是负数/2，也是负数，
//也就是 n>>1; n右移1位，这里的
class Solution {
	public:
		int  NumberOf1(int n) {
			int count = 0;
			if(n < 0){
				n = n & 0x7FFFFFFF;
				++count;
			}
			while(n != 0){
				count += n & 1;
				n = n >> 1;
			}
			return count;
		}
}
//第二种方法,第二种方法不用对负数，进行处理，因为传进来的负数本身就是计算它的补码中1的个数。
void f(int n){
	int count=0;
	while(n){
		n=n&(n-1);
		count++;

	}
}
