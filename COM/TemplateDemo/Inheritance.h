using namespace std;

class CBase
{
public:
	CBase(){}
	~CBase(){}

	void BaseMethod()
	{
		cout<<"Call CBase Method"<<endl;
	}
};

class CMath: public CBase
{
public:
	CMath(){}
	~CMath(){}
	void BaseMethod()
	{
		cout<<"Call CMath Method"<<endl;
	}
};

template<typename T>
class CComObject:public T
{
public:
	CComObject(){}
	~CComObject(){}
	void CallBaseMethod()
	{
		T * pT = static_cast<T *>(this);
		pT->BaseMethod();
	}
};