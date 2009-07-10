// DictComp.cpp : Defines the entry point for the DLL application.
//
#include <comutil.h>
#include "IComputer.h"
#include "olectl.h"
#include "Registry.h"

HANDLE	 g_hModule;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	g_hModule = hModule;
    return TRUE;
}

// {54BF6567-1007-11D1-B0AA-444553540000}
extern "C" const GUID CLSID_Computer = 
		{ 0x54bf6567, 0x1007, 0x11d1,
		{ 0xb0, 0xaa, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00} } ;

BOOL __stdcall CreateObject(const CLSID& clsid, const IID& iid, void **ppv)
{
	if (clsid == CLSID_Computer ) {
		CComputer *pObject = new CComputer;
		HRESULT result = pObject->QueryInterface(iid, ppv);
		return (result == S_OK) ? TRUE : FALSE;
	}
	return FALSE;
}
// class CComputer implementation

CComputer::CComputer()
{
	m_Ref = 0;
}

CComputer::~CComputer()
{

}

HRESULT  CComputer::QueryInterface(const IID& iid, void **ppv)
{
	if ( iid == IID_IUnknown )
	{
		*ppv = (ICale *) this ;
				((ICale *)(*ppv))->AddRef() ;
	} else if ( iid == IID_Computer ) 
	{
		*ppv = (ICale *) this ;
				((ICale *)(*ppv))->AddRef() ;
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE ;
	}
	return S_OK;
}

ULONG CComputer::AddRef()
{
	m_Ref ++;
	return  (ULONG) m_Ref;
}

ULONG	  CComputer::Release()
{
	m_Ref --;
	if (m_Ref == 0 ) {
		delete this;
		return 0;
	}
	return  (ULONG) m_Ref;
}

BOOL CComputer::Initialize()
{

	return TRUE;
}

BOOL CComputer::Add(int x,int y,int *result)
{
	*result = x + y;
	return TRUE;
}

//
// Server registration
//
extern "C" HRESULT __stdcall DllRegisterServer()
{
	TCHAR szModule[1024];
	DWORD dwResult = ::GetModuleFileName((HMODULE)g_hModule, szModule, 1024);
	if (dwResult == 0)
		return SELFREG_E_CLASS;
	return RegisterServer(CLSID_Computer,
		szModule, 
		TEXT("Computer.Object"),
		TEXT("Computer Component"),
		NULL);
}


//
// Server unregistration
//
extern "C" HRESULT __stdcall DllUnregisterServer()
{
	return UnregisterServer(CLSID_Computer,
		TEXT("Computer.Object"),NULL);
}
