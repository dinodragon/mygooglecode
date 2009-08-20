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
		cout<<"构造函数"<<endl;
	}

	~A()
	{
		delete[] p;
		cout<<"析构函数"<<endl;
	}

	void fun()
	{
		cout<<"对象被调用"<<endl;
	}
};

void fun()
{
	//std::auto_ptr<A> p;
	A * p = new A();
	p->fun();
	delete p;
}
//智能指针
void main()
{
	fun();
}