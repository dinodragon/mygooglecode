// ObjectInherit.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "InheritTest.h"

using namespace std;
void Fun(Base);
void Fun2(Base *);

int _tmain(int argc, _TCHAR* argv[])
{
	C c(10);
	cout<<c.GetData()<<endl;
	cout<<c.A::GetData()<<endl;
	cout<<c.B::GetData()<<endl;
	cout<<c.C::GetData()<<endl;
	cout<<c.doGetData()<<endl;
	cout<<c.A::doGetData()<<endl;
	cout<<c.B::doGetData()<<endl;
	cout<<c.C::doGetData()<<endl;

	Base b;
	Child child;
	Fun(b);
	Fun(child);
	child.m_data = 10;
	Base cc = child;//相当于用子类对象的值，构造了一个基类的对象，这是两个独的对象。
	cout<<"------Fun2------"<<endl;
	Fun2(&b);
	Fun2(&child);

	CTest ta(1);
	ta.fun();
	CTest tb; //CTest tb();不需要传参时，不用带括号，否则下在一句会报错。
	tb.fun();

	CA ca;
	ca.ShowSize();
	return 0;
}

void Fun(Base o)
{
	o.fun();
	o.vfun();
}

void Fun2(Base * o)
{
	o->fun();
	o->vfun();
}
