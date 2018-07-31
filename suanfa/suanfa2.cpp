/*************************************************************************
  > File Name: suanfa2.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Wed Nov  1 22:30:29 2017
 ************************************************************************/

#include<iostream>
#include<vector>

using namespace std;

		void  sort1(vector<int> &array) {
			int len=array.size();
			for(int i=0;i<len;i++){
				int k=array[i];
				int j=i-1;
				if(k&1){
					cout<<"k"<<endl;
					while(j>=0&&!(array[j]&1)){
						array[j+1]=array[j];
						j=j-1;
					}
				}
				array[j+1]=k;
			}
		}
int main(){

	vector<int> v={1,23,22,5,5,21,5,2,3,8,4,7,0,3};
	sort1(v);
	for(int i=0;i<v.size();i++)
		cout<<" "<<v[i];

	v[3]=6;
	bool b=!(v[3]&1);
	cout<<" wo shi "<<b<<endl;

}
