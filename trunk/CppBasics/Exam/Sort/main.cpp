#include <iostream>
#include <random>
#include <time.h>

using namespace std;

void Init(int * a,int arrSize);

int main()
{
	int a[20];
	Init(a,sizeof(a)/sizeof(a[0]));
	
}


void Sort(int *a,int arrSize)
{

}

void Print(int *a,int arrSize)
{

}

void Init(int *a,int arrSize)
{
	srand((unsigned)time(NULL));
	for(int i = 0;i<arrSize;i++)
	{
		a[i] = rand();
	}
}