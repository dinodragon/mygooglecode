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
		cout<<"���캯��"<<endl;
	}

	~A()
	{
		delete[] p;
		cout<<"��������"<<endl;
	}

	void fun()
	{
		cout<<"���󱻵���"<<endl;
	}
};

void fun()
{
	//std::auto_ptr<A> p;
	A * p = new A();
	p->fun();
	delete p;
}
//����ָ��
void main()
{
	fun();
}