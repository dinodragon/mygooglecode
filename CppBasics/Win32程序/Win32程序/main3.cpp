#include <iostream>

using namespace std;

class CObject
{
public:
	CObject(int a)
	{
		cout<<"CObject һ���������캯��ִ��"<<endl;
	}
	CObject()
	{
		cout<<"CObject �޲������캯��ִ��"<<endl;
	}
protected:
	~CObject()
	{
		cout<<"CObject ����"<<endl;
	}
};

class CCmdTarget:public CObject
{
public:
	CCmdTarget(int a)
	{
		cout<<"CCmdTarget һ�������������ִ��"<<endl;
	}
	~CCmdTarget()
	{
		cout<<"CCmdTarget ����"<<endl;
	}
};

CCmdTarget cc(1);

void main()
{
	cout<<"������ִ��!"<<endl;
}