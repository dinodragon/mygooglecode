#include <iostream>
#include <vector>

using namespace std;

void main()
{
	vector<int> ivec;
	cout<<"vector<int>��ʼsize��"<<ivec.size()<<endl;
	cout<<"vector<int>��ʼcapacity��"<<ivec.capacity()<<endl;
	ivec.push_back(1);
	cout<<"vector<int>push_back(1)��size��"<<ivec.size()<<endl;
	cout<<"vector<int>push_back(1)��capacity��"<<ivec.capacity()<<endl;
	ivec.reserve(21);
	cout<<"vector<int>reserve(21)��size��"<<ivec.size()<<endl;
	cout<<"vector<int>reserve(21)��capacity��"<<ivec.capacity()<<endl;
	ivec.resize(20);
	cout<<"vector<int>resize(20)��size��"<<ivec.size()<<endl;
	cout<<"vector<int>resize(20)��capacity��"<<ivec.capacity()<<endl;
}