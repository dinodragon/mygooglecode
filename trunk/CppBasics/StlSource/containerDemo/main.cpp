#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <stack>

using namespace std;

int main()
{
  stack<int,list<int>> a;
  a.push(1);
  a.push(7);
  a.push(4);
  cout<<a.top()<<endl;
}