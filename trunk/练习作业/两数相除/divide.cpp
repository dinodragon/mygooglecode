/**************************************************
输入两个数,相除比较不同精度结果

                 程序设计：杨飞
				 http://yangfei.vicp.cc
***************************************************/

#include <iostream>
#include <iomanip>

using namespace std;

void main()
{
	double s=0,t=0;
	cout<<"请输入被除数和除数:";
	cin>>s>>t;
	if( t==0 ){ cout<<"除数不能为0"; exit(0); }
	for(int i=1 ; i<12 ; i++)
		cout<<i<<"位小数精度:"<<setprecision(i)<<s/t<<endl;
}