// ObjectInherit.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include "InheritTest.h"

using namespace std;

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
	return 0;
}

