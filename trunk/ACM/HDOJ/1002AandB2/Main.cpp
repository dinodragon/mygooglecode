#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//http://acm.hdu.edu.cn/showproblem.php?pid=1002

string Sum(string x,string y);
int main()
{
	int t = 0;
	cin>>t;
	for (int i = 1 ;i <= t ;i++)
	{
		string x,y;
		cin>>x>>y;
		string result = Sum(x,y);
		cout<<"Case "<<i<<":"<<endl;
		cout<<x<<" + "<<y <<" = "<<result<<endl;
		//注意题目是要求在两个Case之间有空行
		if (i<t)
		{
			cout<<endl;
		}
	}
}

string Sum(string x,string y)
{
	string result;
	int carry = 0;
	for (unsigned int i = 0 ;i<x.length() || i<y.length() ; i++)
	{
		int a = i < x.length() ? x[x.length() - 1 - i] - '0' : 0;
		int b = i < y.length() ? y[y.length() - 1 - i] - '0' : 0;

		result.append(1,((a + b + carry) % 10) + '0');
		carry = (a + b + carry) /10;
	}
	if (carry > 0)
	{
		result.append(1,carry + '0');
	}
	reverse(result.begin(),result.end());
	return result;
}