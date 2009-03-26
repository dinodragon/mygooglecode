#include <iostream>
#include <time.h>
#include "header.h"

using namespace std;

void init(int value_array[N])  //��ʼ��
{
	for(int p=0;p<N;p++)
	{
		value_array[p] = -1;
	}
	value_array[0] = 1;
}

void double_array(int value_array[N])    //������ֵ��2
{
	int carry = 0;
	int p=0;

	for(p=0;value_array[p]>-1;p++)
	{
		int c = carry;
		carry = value_array[p]>4;
		value_array[p] = ( (value_array[p]<<1) + c ) % 10;
	}
	value_array[p] = carry>0?carry:-1;
}

void print_array(int value_array[N])  //�������ֵ
{
	int p=0;
	for(p=0;p<N && value_array[p]>-1;p++);
	for(--p;p>-1;p--) cout<<value_array[p];
	cout<<endl;
}

void time_calc(bool x)  //��ʱ����
{
	static int count = 1;
	static clock_t start=clock();
	if(x==0)
	{
		start = clock();
		count = 1;
	}
	if(x==1)
		cout<<"��ʱ:"<<clock()-start<<"����(��"<<count++<<"��ͳ��)"<<endl;
}