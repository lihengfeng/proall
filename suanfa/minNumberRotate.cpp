/*************************************************************************
  > File Name: suanfa3.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Sun Oct 22 20:03:18 2017
 ************************************************************************/

#include<iostream>
using namespace std;

class Solution {
	public:
		int minNumberInRotateArray(vector<int> rotateArray) {
			int len=rotateArray.size();
			int l=0;int r=len-1;
			if(len==0)
				return 0;
			if(rotateArray[0]<rotateArray[len-1])
				return rotateArray[0];
			int m;
			while(l<=r){
				m=(l+r)/2;
				if(rotateArray[m]<rotateArray[m-1]&&rotateArray[m]<rotateArray[m+1])
					break;
				else if(rotateArray[m]>rotateArray[m-1]&&rotateArray[m]>rotateArray[m+1])
					return rotateArray[m+1];
				else {
					if(rotateArray[m]>rotateArray[0])
						l=m+1;
					else if (rotateArray[m]<rotateArray[0])
						r=m-1;
				}
			}
			return rotateArray[m];
		}
};
