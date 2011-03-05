/**************************************************
    打印素数表

                 程序设计：杨飞
				 http://yangfei.vicp.cc
***************************************************/

#include <iostream>
#include <bitset>
#include <fstream>
#include <time.h>
#define N 1000000

using namespace std;

int main()
{
	clock_t start=clock();
	bitset<N> * p = new bitset<N>;
	p->set();
	for(int i=2;i<=1000;++i)
		for(int j=i*i;j< p->size();j+=i)
			p->reset(j);
	ofstream out("prime.txt");
	for(int i=2;i<N;i++)
		if(p->test(i)) out<<i<<endl;
	cout<<"执行时间:"<<(clock()-start)*1.0/CLK_TCK<<"秒"<<endl;
}