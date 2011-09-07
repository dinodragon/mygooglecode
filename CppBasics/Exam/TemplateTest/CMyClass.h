#include <iostream>

using namespace std;

template <typename T1> class myvector
{
	T1 a[80];
public:
	myvector()
	{
		cout<<"myvector"<<endl;
	}
	void Fun(void);
};


template <typename T1> void myvector<T1>::Fun()
{
	cout<<"Fun"<<endl;
}