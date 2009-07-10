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
	if (CoInitialize(NULL) != S_OK) {
		printf("Initialize COM library failed!\n");
		return FALSE;
	}

	HRESULT hResult;
	CLSID dictionaryCLSID;
	hResult = ::CLSIDFromProgID(L"Computer.Object", &dictionaryCLSID);
	if (hResult != S_OK) 
	{
		printf("Can't find the dictionary CLSID!\n");
		return FALSE;
	}

	hResult = CoCreateInstance(dictionaryCLSID, NULL, 
		CLSCTX_INPROC_SERVER, IID_IUnknown, ppv);
	if (hResult != S_OK) 
	{
		return FALSE;
	}
	return TRUE;
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