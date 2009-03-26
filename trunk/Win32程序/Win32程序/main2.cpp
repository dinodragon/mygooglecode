#include <iostream>

using namespace std;

class ClassA
{
public:
	static int x;
	virtual void fun()
	{
		cout<<"ClassA:"<<x<<endl;
		x = 5;
	}
};

class ClassB:public ClassA
{
public:
	virtual void fun()
	{
		cout<<"ClassB:"<<x<<endl;
	}
};

int ClassA::x = 10;

template<class T>
T function(T x)
{
	cout<<x<<endl;
	return x;
}


void main()
{
	ClassA a;
	ClassB b;
	a.fun();
	b.fun();
	if(typeid((ClassA)b)==typeid(ClassB))
		cout<<"OK!"<<endl;
	int x;
	typedef int A;
	if(typeid(x)==typeid(A))
		cout<<"intok"<<endl;
	//cout<<typeid(int)<<endl;
	function("aa");
	
	
}