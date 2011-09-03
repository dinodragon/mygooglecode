#include <iostream>
#include <vector>

using namespace std;

int MaxSum(const vector<int> &data,int & start,int & end);

int main()
{
	int t = 0;
	cin>>t;
	for (int i = 1;i <= t;i++)
	{
		vector<int> data;
		int n = 0;
		cin>>n;
		data.reserve(n);
		for(int j=0;j < n;j++)
		{
			int tempData = 0;
			cin >> tempData;
			data.push_back(tempData);
		}
		int start = 0,end = 0,sum = 0;
		sum = MaxSum(data,start,end);
		cout<<"Case "<<i<<":"<<endl;
		cout<<sum<<" "<<start<<" "<<end<<endl;
		if (i < t)
		{
			cout<<endl;
		}
	}
}

int MaxSum(const vector<int> &data,int & start,int & end)
{
	unsigned int count = data.size();
	int maxSum = -10000;
	for(unsigned int i = 0;i<count;i++)
	{
		int s = -10000,p = i ,l = 0;
		int tempSum = 0;
		for (unsigned int j = i;j < count;j++)
		{
			tempSum += data[j];
			if (tempSum > s)
			{
				s = tempSum;
				p = i + 1;
				l = j + 1;
			}
		}
		if (s > maxSum)
		{
			maxSum = s;
			start = p;
			end = l;
		}
	}
	return maxSum;
}


//#include<stdio.h>
//#include<stdlib.h>
//int *a;
//int con=1;
//void DP_maxsum(int row_number)
//{   
//	int i;
//	int besti=1,bestj=1;
//	int besti_temp=1,bestj_temp=1;
//	int sum=0;
//	int b=0;
//
//	for(i=1;i<=row_number;i++)
//	{
//		bestj_temp=i;
//		if(b>=0)
//		{   
//			b+=a[i];
//		}
//		else 
//		{   
//			b=a[i];
//		}
//
//		if(b>sum)
//		{    
//			besti=besti_temp;  
//			sum=b;
//			bestj=bestj_temp;
//		}
//
//	}
//	if(sum==0)
//	{
//		sum=a[1];
//		for(i=2;i<=row_number;i++)
//			if(sum<a[i])
//			{
//				sum=a[i];
//				besti=bestj=i;
//			}
//
//	}
//	printf("Case %d:\n",con++);
//	printf("%d ",sum);
//	printf("%d %d",besti,bestj);
//	printf("\n");
//
//
//}
//int main()
//{
//
//
//	//程序定义部分。
//	int test;
//	int i;//循环变量
//	int row_number;//行的数量
//	scanf("%d",&test);
//	while(test--)
//	{    
//
//		scanf("%d",&row_number);
//		a=(int *)malloc((row_number+1) * sizeof(int));
//		for(i=1;i<=row_number;i++)
//			scanf("%d",&a[i]);
//		DP_maxsum(row_number);
//		if(test!=0)printf("\n");
//	}
//	return 0;
//}
