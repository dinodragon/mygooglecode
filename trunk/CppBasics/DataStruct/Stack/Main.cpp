#include <iostream>
#include "MyStack.h"
#include <deque>

using namespace std;

int main()
{
	cout<<"----------MyStack<int>---------------"<<endl;
	MyStack<int> mysatck;
	mysatck.push(1);
	mysatck.push(2);
	mysatck.push(3);
	cout<<mysatck.pop()<<endl;
	cout<<mysatck.pop()<<endl;
	cout<<mysatck.pop()<<endl;

	cout<<"----------deque<int>---------------"<<endl;
	deque<int> dequeint;
	dequeint.push_front(1);
	dequeint.push_front(2);
	dequeint.push_front(3);
	
	cout<<dequeint.front()<<endl;
	dequeint.pop_front();
	cout<<dequeint.front()<<endl;
	dequeint.pop_front();
	cout<<dequeint.front()<<endl;
	dequeint.pop_front();
	return 0;
}