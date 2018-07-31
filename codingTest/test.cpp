/*************************************************************************
	> File Name: test.cpp
	> Author: lihengfeng
	> Mail: 17704623602@163.com 
	> Created Time: Tue Dec 26 16:16:32 2017
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;
class A{
public:
private:
//	string str("sss"); 类内不能()初始化
	string str{"sss"};  //类内可以列表初始化
};
int main(){
	string str("sss"); 

/*不能单个int来初始化，因为int不知道默认生成什么字符,但是vector可以，因为vector中类有默认初始值
	string str2(10); 
*/
	string str2(10,'c'); 
	int i();
	int i2;
	int *pi1=new int; //
	int *pi2=new int(); //值初始化为0；*pi2的值为0
	cout<<i<<"="<<i2<<endl;
	
	cout<<*pi1<<"="<<*pi2<<endl;

	const int ci=43;
	auto& p=ci;
	auto& q=43;
}
