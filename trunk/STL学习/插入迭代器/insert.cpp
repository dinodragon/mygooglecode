//������������ڽ�ֵ���뵽�����С�����Ҳ��������������Ϊ���ǽ����������ת��Ϊһ����������
//������copy()�������㷨�С����磬һ����������һ�������һ��ʸ������:
//
//list<double> dList;
//vector<double> dVector;
//ͨ��ʹ��front_inserter���������󣬿���ֻ�õ���copy()���
//����ɽ�ʸ���еĶ�����뵽����ǰ�˵Ĳ�����
//
//copy(dVector.begin(), dVector.end(), front_inserter(dList));
//���ֲ�����������£�
//
//��        ��ͨ������ ��������뵽�����κζ����ǰ�档
//
//��        Front inserters ��������뵽���ݼ���ǰ�桪�����磬�����ͷ��
//
//��        Back inserters ��������뵽���ϵ�β���������磬ʸ����β��������ʸ��������չ��
//
//ʹ�ò�����������ܵ��������е����������ƶ�λ�ã����ʹ���ִ�ĵ������Ƿ���
//���磬��һ��������뵽ʸ����������������ֵ�ƶ�λ�����ڳ��ռ䡣һ����˵��
//���뵽�����������Ľṹ�и�Ϊ��Ч����Ϊ���ǲ��ᵼ�����������ƶ���

#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

int iArray[5] = { 1, 2, 3, 4, 5 };

void Display(list<int>& v, const char* s);

int main()
{
	list<int> iList;

	// Copy iArray backwards into iList
	copy(iArray, iArray + 5, front_inserter(iList));
	Display(iList, "Before find and copy");

	// Locate value 3 in iList
	list<int>::iterator p =
		find(iList.begin(), iList.end(), 3);

	// Copy first two iArray values to iList ahead of p
	copy(iArray, iArray + 2, inserter(iList, p));
	Display(iList, "After find and copy");

	return 0;
}

void Display(list<int>& a, const char* s)
{
	cout << s << endl;
	copy(a.begin(), a.end(),
		ostream_iterator<int>(cout, " "));
	cout << endl;
}
