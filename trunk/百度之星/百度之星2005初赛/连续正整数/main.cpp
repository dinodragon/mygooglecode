/*
百度之星2005初赛第一题
*/
#include <iostream>

using namespace std;

int main()
{
	int n=9999,flag = 0;
	for(int i=n/2;i>0;i--)
		if ((n-i*(i+1)/2) % (i+1) == 0)
		{
			int from = (n-i*(i-1)/2)/(i+1);
			if (from < 1)
			{
				continue;
			}
			int k;
			k = 0;
			flag = 1;
			while (k<=i)
			{
				cout<<from + (k++)<<" ";
			}
			cout<<endl;
		}
	if (flag == 0)
	{
		cout<<"NONE"<<endl;
	}
	return 0;
}