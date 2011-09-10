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
	Base(int data)
	{
		m_data = 0;
		std::cout<<"Base Construct"<<std::endl;
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
	//���øù��캯��ʱ����Ҫ�ȵ��û��๹�캯������δ��ʾ���� ���������Ĭ�Ϲ��캯����
	Child():Base(1)
	{
		m_data = 1;
		std::cout<<"Child Construct"<<std::endl;
	}

	Child(int data):Base(1)
	{
		m_data = data;
		std::cout<<"Child Construct Child(int data)"<<std::endl;
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

//���캯�����ԣ��޲ι��캯��������CTest b();��ʽ���壬Ӧʹ��CTest b
struct CTest
{
	CTest(int){};
	CTest(){};
	void fun(){};
};

//ֻ�о�̬�����������ݳ�Ա�ſ��������г�ʼ��,���·�ʽ�Ƿ�
//class CA
//{
//	const int size = 0;
//};
//��ʹ�����·�ʽ�������þ�̬�������Σ�
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