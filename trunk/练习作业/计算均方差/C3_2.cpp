/**************************************************
使用向量计算均方差

                 程序设计：杨飞
				 http://yangfei.vicp.cc
***************************************************/

#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

int main()
{
	int a[]={6,3,7,1,4,8,2,9,11,5};
	int size = sizeof(a)/sizeof(*a);
	vector<int> va(a,a+size);
	int s = 0;
	unsigned int i = 0;
	double avg , sum = 0;
	for(i = 0; i < va.size() ; i++) s += va[i];
	avg = s/(double)va.size();
	for(i = 0 ; i < va.size() ; i++)
		sum += (va[i] - avg) * (va[i] - avg);
	cout << "s=" << sqrt(sum / va.size())<<endl;
}
