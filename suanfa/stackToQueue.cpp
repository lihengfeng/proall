/*************************************************************************
  > File Name: suanfa2.cpp
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Sun Oct 22 18:21:22 2017
 ************************************************************************/
//用两个堆栈实现一个队列

#include<iostream>
#include<assert.h>
#include<stack>
using namespace std;

class Solution
{
	public:
		void push(int node) {
			stack1.push(node);
		}

		int pop() {
			if(stack2.empty()){
				while(!stack1.empty()){
					int node=stack1.top();
					stack2.push(node);
					stack1.pop();
				}
			}
			assert(!stack2.empty());
			int node= stack2.top();
			stack2.pop();
			return node;
		}

	private:
		stack<int> stack1;
		stack<int> stack2;
};
