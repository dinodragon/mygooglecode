/****************************************
��������:
�ļ�in.txt��ÿ�д�һ����������,һ������Ƚϳ�.��಻����5000λ.
�������Ѹö���������Ӧ��ʮ�����������out.txtÿ��һ��ʮ������.
*****************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "header.h"

using namespace std;

int main()
{
	time_calc(0);  //��Ƽ�ʱ�����
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
		time_calc();  //�����ʱ
	}
	print_array(value_array);
}