/**************************************************
    ��������Ľ׳�

                 ������ƣ����
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
	cout<<"���������ڼ��� n! ������n:";
	cin >> n;
	if ( n<1 ) { cout<<"������������!"; exit(0); }
	for(unsigned i = 1;i <= n;i++)
	{
		s += log10(double(i));
	}
	cout<<n<<"!="<<setprecision(12)<<pow(10,s-int(s))<<"e+"<<int(s)<<endl;
}