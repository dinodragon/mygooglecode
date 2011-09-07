#include "Math.h"

CMath::CMath(void)
{
	cout<<"CMath Constructor"<<endl;
}

CMath::~CMath(void)
{
	cout<<"CMath Destructor"<<endl;
}

int CMath::Add(int a, int b)
{
	return a + b;
}
