/***********************************
*�����*��ɵ�����ͼ��             *
***********************************/

#include <iostream>
#include <cmath>

#define N 8   //���δ�С
using namespace std;

void main()
{
	int r=0,c=0;
	for ( r = -N ; r<=N ;r++)
	{
		for( c=0 ;c < abs(r);c++ ) cout<<" ";
		for( c=1 ;c <= 2*N-2*abs(r)+1 ;c++ ) cout<<"*";
		cout<<endl;
	}
}
