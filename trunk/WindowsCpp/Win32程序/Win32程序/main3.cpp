#include <iostream>

using namespace std;

class CObject
{
public:
	CObject(int a)
	{
		cout<<"CObject 一个参数构造函数执行"<<endl;
	}
	CObject()
	{
		cout<<"CObject 无参数构造函数执行"<<endl;
	}
protected:
	~CObject()
	{
		cout<<"CObject 析构"<<endl;
	}
};

class CCmdTarget:public CObject
{
public:
	CCmdTarget(int a)
	{
		cout<<"CCmdTarget 一个参数构造参数执行"<<endl;
	}
	~CCmdTarget()
	{
		cout<<"CCmdTarget 析构"<<endl;
	}
};

CCmdTarget cc(1);

void main()
{
	cout<<"主函数执行!"<<endl;
}