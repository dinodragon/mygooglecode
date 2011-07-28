#include <iostream>
#include <random>
#include <time.h>

using namespace std;

void Init(int * a,int arrSize);
void Sort(int *a,int arrSize);
void Print(int *a,int arrSize);

int main()
{
	int a[200];
	int arrsize = sizeof(a)/sizeof(a[0]);
	Init(a,arrsize);
	cout<<"Ô­Ë³Ðò"<<endl;
	Print(a,arrsize);
	Sort(a,arrsize);
	cout<<"ÅÅÐòºó"<<endl;
	Print(a,arrsize);
}


void Sort(int *a,int arrSize)
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