#include <iostream>

using namespace std;

#pragma pack(push) //�������״̬

//��ϸ���ݲο�http://www.cnblogs.com/bingxuefly/archive/2007/11/12/957056.html

//#pragma pack(4)//�趨Ϊ4�ֽڶ��룬Ĭ��ֵ
#pragma pack(1)//�趨Ϊ1�ֽڶ��룬���������ͻ���13

struct MyStruct
{
	double dda1; //8�ֽ�
	char dda; //1�ֽ�
	int type; //4�ֽ�
};

void main()
{
	cout<<"sizeof(MyStruct):"<<sizeof(MyStruct)<<endl; //���16
}

#pragma pack(pop)//�ָ�����״̬