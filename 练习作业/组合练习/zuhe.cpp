#include <iostream>

using namespace std;

int main()
{
int i=0,j=0,k=0,count=0;
for(i=1;i<=10;i++)
	for(j=i+1;j<=10;j++)
		for(k=j+1;k<=10;k++)
			cout<<i<<","<<j<<","<<k<<"\t";
}