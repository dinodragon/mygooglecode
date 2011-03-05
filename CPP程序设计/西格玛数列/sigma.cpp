/**************************************************
������������һ���������У���ͨ���ʾΪ��
a(n) = 10^n,   n=0,1,2...

������1��10��100��1000��......�������������ͳ�������110100100010000������
���������֪���������ĵ�iλ������0����1��

���ݴ����string01.txt�У��ļ�һ�����ĵ�һ����ռһ�У�
��������N��N<65536������������N��������������N��������K(i)������1<=k(i)<=231��
����ڸ�0����1��ʱ��,��Ҫ��һ��,�Ա����֡�

                 ������ƣ����
				 http://yangfei.vicp.cc
***************************************************/

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

bool isOne(int n);

int main()
{
	int n,data;
	ifstream in("string01.txt");
	in>>n;
	for(int i=0;i<n;i++)
	{
		in>>data;
		cout<<isOne(data)<<" ";
	}
	cout<<endl;
}

bool isOne(int n)
{
	if(8*n-7<=0)
		return 0;
	else
	{
		int x = int( ( sqrt( double(8*n-7) )-1)/2 );
		if( x*(x+1)/2 + 1 == n )
			return 1;
		else
			return 0;
	}
}
