#include <iostream>

using namespace std;

//http://acm.hdu.edu.cn/showproblem.php?pid=1001

int main()
{
	int n = 0;
	while(cin>>n)
	{
		//���������㣬HDOJ���ж�Ϊ�����,��sumû��Խ��ʱ��n*(n+1)��Խ��
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


