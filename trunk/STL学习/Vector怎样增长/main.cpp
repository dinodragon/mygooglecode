#include <iostream>
#include <vector>

using namespace std;

void main()
{
	vector<int> ivec;
	cout<<"vector<int>初始容量："<<ivec.size()<<endl;
	ivec.push_back(1);
	cout<<"vector<int>push_back(1)后容量："<<ivec.size()<<endl;
	ivec.reserve(21);
	cout<<"vector<int>reserve(21)后容量："<<ivec.size()<<endl;
	ivec.resize(20);
	cout<<"vector<int>resize(20)后容量："<<ivec.size()<<endl;
}