#include <iostream>
//��ͷ�ļ��л����һ��4244����
#include "WarningTest.h"
using namespace std;

#pragma warning(push)   //�Ǳ��浱ǰ�ı���������״̬��
#pragma warning(disable:4244)

void main()
{
	double x = 0.0;
	int y;
	y = x; //����ʱ������и����棬���������ˡ�ֻʣ����ͷ�ļ���ľ��棬warning C4244: '=' :conversion from 'double' to 'int', possible loss of data
	cout<<y<<endl;
}
#pragma warning(pop)   //�ǻָ�ԭ�ȵľ���״̬��   

