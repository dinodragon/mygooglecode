#include <iostream>
#include <vector>

using namespace std;

void main()
{
	vector<int> ivec;
	cout<<"vector<int>初始size："<<ivec.size()<<endl;
	cout<<"vector<int>初始capacity："<<ivec.capacity()<<endl;
	ivec.push_back(1);
	cout<<"vector<int>push_back(1)后size："<<ivec.size()<<endl;
	cout<<"vector<int>push_back(1)后capacity："<<ivec.capacity()<<endl;
	ivec.reserve(21);
	cout<<"vector<int>reserve(21)后size："<<ivec.size()<<endl;
	cout<<"vector<int>reserve(21)后capacity："<<ivec.capacity()<<endl;
	ivec.resize(20);
	cout<<"vector<int>resize(20)后size："<<ivec.size()<<endl;
	cout<<"vector<int>resize(20)后capacity："<<ivec.capacity()<<endl;
}