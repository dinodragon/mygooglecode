#include <iostream>

using namespace std;

namespace name1{
	void fun1()
	{
		cout<<"name1�µ�fun1"<<endl;
	}

	void fun2()
	{
		cout<<"name1�µ�fun2"<<endl;
	}
	void fun3()
	{
		cout<<"name1�µ�fun2"<<endl;
	}
}

namespace name2{
	void fun1()
	{
		cout<<"name2�µ�fun1"<<endl;
	}

	void fun2()
	{
		cout<<"name2�µ�fun2"<<endl;
	}
	void fun3()
	{
		cout<<"name2�µ�fun2"<<endl;
	}
}

using namespace name1;

int main()
{
	fun1();
	fun2();
	fun3();
}
