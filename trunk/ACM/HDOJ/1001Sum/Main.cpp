#include <iostream>

using namespace std;

//http://acm.hdu.edu.cn/showproblem.php?pid=1001

int main()
{
	int n = 0;
	while(cin>>n)
	{
		//不能这样算，HDOJ会判定为错误的,当sum没有越界时，n*(n+1)会越界
		//int sum = n*(n+1)/2;
		int sum = 0;
		if( n % 2 == 0)
		{
			sum = (n/2)*(n+1);
		}
		else
		{
			sum = (n+1)/2 * n;
		}
		cout<<sum<<endl<<endl;
	}
	return 0;
}


