/**************************************************
����������,����Ƚϲ�ͬ���Ƚ��

                 ������ƣ����
				 http://yangfei.vicp.cc
***************************************************/

#include <iostream>
#include <iomanip>

using namespace std;

void main()
{
	double s=0,t=0;
	cout<<"�����뱻�����ͳ���:";
	cin>>s>>t;
	if( t==0 ){ cout<<"��������Ϊ0"; exit(0); }
	for(int i=1 ; i<12 ; i++)
		cout<<i<<"λС������:"<<setprecision(i)<<s/t<<endl;
}