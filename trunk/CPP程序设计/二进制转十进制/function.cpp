#include <iostream>
#include <time.h>
#include "header.h"

using namespace std;

void init(int value_array[N])  //初始化
{
	for(int p=0;p<N;p++)
	{
		value_array[p] = -1;
	}
	value_array[0] = 1;
}

void double_array(int value_array[N])    //将数组值乘2
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

void print_array(int value_array[N])  //输出数组值
{
	int p=0;
	for(p=0;p<N && value_array[p]>-1;p++);
	for(--p;p>-1;p--) cout<<value_array[p];
	cout<<endl;
}

void time_calc(bool x)  //计时函数
{
	static int count = 1;
	static clock_t start=clock();
	if(x==0)
	{
		start = clock();
		count = 1;
	}
	if(x==1)
		cout<<"用时:"<<clock()-start<<"毫秒(第"<<count++<<"次统计)"<<endl;
}