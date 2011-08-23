using namespace std;

class A
{
protected:
	int m_data;

public:
	A(int data = 0)
	{
		m_data = data;
	}
	int GetData()
	{
		return doGetData();
	}

	virtual int doGetData()
	{
		return m_data;
	}
};

class B : public A
{
protected:
	int m_data;

public:
	B(int data = 1)
	{
		m_data = data;
	}

	int doGetData()
	{
		return m_data;
	}
};

class C : public B
{
protected:
	int m_data;
public:
	C(int data = 2)
	{
		m_data = data;
	}
};

class Child;
class Base
{
public:
	int m_data;
	Base()
	{
		m_data = 0;
	};
	//Base(const Child& c)
	//{
	//	
	//	std::cout<<"子类型对象转为基类型对象，实际是调用了基类型的构造函数！"<<std::endl;
	//	//正常情况下有默认的子类对象构造函数。
	//}
	void fun()
	{
		std::cout<<"Base Fun"<<std::endl;
	}
	virtual	void vfun()
	{
		std::cout<<"Base Vfun"<<std::endl;
	}
};

class Child :public Base
{
public:
	int m_data;
	Child()
	{
		m_data = 1;
	}
	void fun()
	{
		std::cout<<"Child Fun"<<std::endl;
	}
	virtual	void vfun()
	{
		std::cout<<"Child Vfun"<<std::endl;
	}
};

//构造函数测试，无参构造函数不能用CTest b();格式定义，应使用CTest b
struct CTest
{
	CTest(int){};
	CTest(){};
	void fun(){};
};

//只有静态常量整型数据成员才可以在类中初始化,以下方式非法
//class CA
//{
//	const int size = 0;
//};
//可使用以下方式，或者用静态常量整形；
class CA
{
public:
	static const int size2 = 2;
	const int size;
	CA():size(0)
	{
	}

	void ShowSize()
	{
		cout<<"size:"<<size<<endl;
		cout<<"size2:"<<size2<<endl;
	}
};