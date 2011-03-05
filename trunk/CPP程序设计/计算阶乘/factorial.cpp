/**************************************************
    计算大数的阶乘

                 程序设计：杨飞
				 http://yangfei.vicp.cc
***************************************************/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

void main()
{
	unsigned int n=0;
	double s=0;
	cout<<"本程序用于计算 n! 请输入n:";
	cin >> n;
	if ( n<1 ) { cout<<"输入数据有误!"; exit(0); }
	for(unsigned i = 1;i <= n;i++)
	{
		s += log10(double(i));
	}
	cout<<n<<"!="<<setprecision(12)<<pow(10,s-int(s))<<"e+"<<int(s)<<endl;
}