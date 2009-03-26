#include <iostream>
#include <fstream>

using namespace std;

void main()
{
	unsigned int i=0,j=0;//输入的数据.
	unsigned int imin=0,imax=~0;//当前的重叠区域
	ifstream in("input.txt");
	while (in>>i>>j)
	{
		if (i>j)
		{
			swap(i,j);
		}
		imin = max(imin,i);
		imax = min(imax,j);
		if (imin>imax)
		{
			break;
		}
	}
	if (imax>=imin)
	{
		cout<<imax-imin+1<<endl;
	}
	else
	{
		cout<<0<<endl;
	}
}