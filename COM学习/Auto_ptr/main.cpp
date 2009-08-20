#include <iostream>
#include <memory>
#include <crtdbg.h>

using namespace std;

class A
{
public:
	int * p;

	A()
	{
		p = new int[80];
		cout<<"调用构造函数"<<endl;
	}

	~A()
	{
		delete[] p;
		cout<<"调用析构函数"<<endl;
	}

	void fun()
	{
		cout<<"对象方法被调用"<<endl;
	}
};

//智能指针
void fun()
{
	auto_ptr<A> p(new A());
	p->fun();
	//当p出了他的作用域之后即会释放掉A
	//即使发生了异常也会释放A
}

//不使用智能指针
void fun2()
{
	A *p = new A();
	p->fun();
	//如果此时发生了异常则A不会被释放
	//delete p;
}

void main()
{
	fun();
	cout<<"============================="<<endl;
	fun2();
	cout<<"sizeof(A):"<<sizeof(A)<<endl;
	cout<<"_CrtDumpMemoryLeaks:"<<_CrtDumpMemoryLeaks()<<endl;
	getchar();
}