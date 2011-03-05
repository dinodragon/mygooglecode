/**************************************************
    测试程序性能，计算Fibonacci数列

                 程序设计：杨飞
				 http://yangfei.vicp.cc
***************************************************/

#include <iostream>
#include <time.h>
#include <vector>
#define N 45
#define M 100000

using namespace std;

int fibo1(const int n);
int fibo2(const int n);
int fibo3(const int n);

int main()
{
	clock_t start;
	int result;

	start = clock();
	for(int i=1;i<5;i++)
	cout<<"Fibo1("<<N<<")执行"<<M<<"次时间:"<<(clock()-start)*1.0/CLK_TCK<<"秒"<<endl;

	start = clock();
	for(int i=1;i<M;i++)
		result = fibo2(N);
	cout<<"Fibo2("<<N<<")执行"<<M<<"次时间:"<<(clock()-start)*1.0/CLK_TCK<<"秒"<<endl;

	start = clock();
	for(int i=1;i<M;i++)
		result = fibo3(N);
	cout<<"Fibo3("<<N<<")执行"<<M<<"次时间:"<<(clock()-start)*1.0/CLK_TCK<<"秒"<<endl;

}

int fibo1(const int n)
{
	if(n==0) return 0;
	if(n==1) return 1;
	return fibo1(n-1)+fibo1(n-2);
}

int fibo2(const int n)
{
	int a=0,c;
	for(int b=1,i=2; i<=n; ++i)
		c=a+b, a=b, b=c;
	return c;
}

int fibo3(const int n)
{
	vector<int> v( n+1, 0 );
	v[1] = 1;
	for(int i=2;i<=n;++i)
		v[i] = v[i-1] + v[i-2];
	return v[n];
}