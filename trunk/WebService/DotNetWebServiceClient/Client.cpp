#include "stdafx.h"
#include "WebService.h"

using namespace std;
using namespace MyService;

void main()
{
	CoInitialize(NULL);
	CMyService *p = new CMyService;
	int result = 0;
	HRESULT hr = p->Add(234,4,&result);
	cout<<result<<endl;
	assert(SUCCEEDED(hr));
	_CrtDumpMemoryLeaks();
	CoUninitialize();
}