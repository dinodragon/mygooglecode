/**************************************************
问题描述：有一个无穷数列，其通项表示为：
a(n) = 10^n,   n=0,1,2...

构成了1，10，100，1000，......把它连起来，就成了数串110100100010000。。。
问题是如何知道这数串的第i位到底是0还是1。

数据存放在string01.txt中，文件一上来的第一个数占一行，
是正整数N（N<65536，表明后面有N个正整数。后面N个正整数K(i)都符合1<=k(i)<=231）
输出第个0或者1的时候,都要空一格,以便区分。

                 程序设计：杨飞
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
