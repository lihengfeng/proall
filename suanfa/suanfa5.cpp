/*************************************************************************
  > File Name: suanfa5.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Mon Oct 23 22:10:20 2017
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

void reOrderArray(vector<int> &array) {
	vector<int> arr2;
	int len=array.size();
	int j=0;
	bool flag=false;  //表明是否由奇数
	for(int i=0;i<len;i++){
		if(array[i]&1){  //奇术
			j=i-arr2.size();
			array[j]=array[i];
			flag=true;
		}
		else
			arr2.push_back(array[i]);
	}
	if(!flag) j=-1;
	int len2=arr2.size();
	for(int i=0;i<len2;i++)
		array[j+i+1]=arr2[i];
}

int main(){
	//vector<int> v={1,2,3,4,5,6};
	//vector<int> v={6,1,1,1,1,1};
	vector<int> v={2,2,2,2};
	reOrderArray(v);
	for(int i=0;i<v.size();i++)
		cout<<" "<<v[i]<<endl;

}
