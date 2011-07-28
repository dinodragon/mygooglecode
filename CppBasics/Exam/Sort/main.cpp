#include <iostream>
#include <random>
#include <time.h>
#include "Sort.h"

using namespace std;

void Init(int * a,int arrSize);
void Print(int *a,int arrSize);

int main()
{
	int a[200];
	int arrsize = sizeof(a)/sizeof(a[0]);
	Init(a,arrsize);
	cout<<"Ô­Ë³Ðò"<<endl;
	Print(a,arrsize);

	Sort2(a,arrsize);
	cout<<"Sort2ÅÅÐòºó"<<endl;
	Print(a,arrsize);
}



void Print(int *a,int arrSize)
{
	for(int i = 0;i<arrSize;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

void Init(int *a,int arrSize)
{
	srand((unsigned)time(NULL));
	for(int i = 0;i<arrSize;i++)
	{
		a[i] = rand();
	}
}