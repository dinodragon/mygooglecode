/**************************************************
    �æ�/4=1 - 1/3 + 1/5 - 1/7 + ...�����ֵ

                 ������ƣ����
				 http://yangfei.vicp.cc

 �޷���ý�Ϊ��ȷ��ֵ
***************************************************/

#include <iostream>
#include <iomanip>
 using namespace std;

 void main()
 {
	double s = 0;
	long i = 1;
	for( i = 1 ; i <= 1e8 ;i=i+4)
		s += 2.0/(i*(i+2));
	cout<<"pi="<<setprecision(15)<<s*4<<endl;

 }