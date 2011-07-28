#include "Sort.h"


//交换法：
void Sort1(int *a,int arrSize)
{
	for(int i = 0;i<arrSize - 1;i++)
	{
		for(int j = i;j < arrSize;j++)
		{
			if(a[i] > a[j])
			{
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
			
		}
	}
}
//选择法
void Sort2(int *a ,int arrSize)
{
	int pMin = 0;
	for(int i = 0;i < arrSize -1;i++)
	{
		pMin = i;
		for(int j = i+1;j<arrSize;j++)
		{
			if(a[pMin] > a[j])
				pMin = j;
		}
		int temp = a[i];
		a[i] = a[pMin];
		a[pMin] = temp;
	}
}