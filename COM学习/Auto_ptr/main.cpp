#include <iostream>
#include <memory>

using namespace std;

class A
{
public:
	int *p;

	A()
	{
		p = new int[80];
		cout<<"���ù��캯��"<<endl;
	}

	~A()
	{
		delete[] p;
		cout<<"������������"<<endl;
	}

	void fun()
	{
		cout<<"���󷽷�������"<<endl;
	}
};

//����ָ��
void fun()
{
	auto_ptr<A> p(new A());
	p->fun();
	//��p��������������֮�󼴻��ͷŵ�A
	//��ʹ�������쳣Ҳ���ͷ�A
}

//��ʹ������ָ��
void fun2()
{
	A *p = new A();
	p->fun();
	//�����ʱ�������쳣��A���ᱻ�ͷ�
	delete p;
}

void main()
{
	fun();
	cout<<"============================="<<endl;
	fun2();
}