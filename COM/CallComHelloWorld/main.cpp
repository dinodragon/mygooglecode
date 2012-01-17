#include <iostream>
#include <comutil.h>

#include "IMyUnknown.h"
#include "ICale.h"
using namespace std;

// {54BF6567-1007-11D1-B0AA-444553540000}
extern "C" const GUID CLSID_Dictionary = 
{ 0x54bf6567, 0x1007, 0x11d1,
{ 0xb0, 0xaa, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00} } ;
HMODULE hModual;

BOOL CreateObject(const CLSID& clsid, const IID& iid, void **ppv)
{

	hModual = LoadLibrary(TEXT("ComHelloWorld.dll"));
	if (hModual == NULL) return 0;

	typedef BOOL  (__stdcall*  MyFunctionType)(const CLSID& clsid, const IID& iid, void **ppv);
	MyFunctionType fnCreateObject;

	fnCreateObject = (MyFunctionType)GetProcAddress(hModual, "CreateObject");
	if (fnCreateObject == NULL) {
		FreeLibrary(hModual);
		return FALSE;
	}

	return fnCreateObject(clsid, iid, ppv);
}




int main()
{
	hModual = NULL;
	IMyUnknown *pMyUnknown;
	ICale *pCale;
	
	BOOL bResult;
	HRESULT hResult;

	bResult = CreateObject(CLSID_Dictionary, IID_IUnknown, (void **)&pMyUnknown);
	if (bResult == FALSE) 
	{
		printf("Create object failed!\n");
		return -1;
	}

	hResult = pMyUnknown->QueryInterface(IID_Computer, (void **)&pCale);
	if (hResult != S_OK) {
		pMyUnknown->Release();
		printf("QueryInterface IComputer failed!\n");
		return -2;
	}

	int x = 1,y=2, result = 0;
	bResult = pCale->Add(x,y,&result);
	if (hResult == S_OK) {
		cout<<x<<"+"<<y<<"="<<result<<endl;
	}

	pCale->Release();
	pMyUnknown->Release();
}