
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
	//	std::cout<<"�����Ͷ���תΪ�����Ͷ���ʵ���ǵ����˻����͵Ĺ��캯����"<<std::endl;
	//	//�����������Ĭ�ϵ���������캯����
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