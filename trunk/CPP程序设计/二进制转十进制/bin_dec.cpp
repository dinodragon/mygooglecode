/****************************************
问题描述:
文件in.txt中每行存一个二进制数,一般情况比较长.最多不超过5000位.
程序处理后把该二进制数对应的十进制数输出到out.txt每行一个十进制数.
*****************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "header.h"

using namespace std;

int main()
{
	time_calc(0);  //设计计时器起点
	int value_array[N];
	const int counter = 10;

	for(int c=0;c<counter;c++)
	{
		init(value_array);
		//time_calc(0);
		for(int p=1;p<3000;p++)
		{
			double_array(value_array);
		}
		time_calc();  //输出计时
	}
	print_array(value_array);
}