#include "stdafx.h"
#include "factory.h"
#include "IComputer.h"

ULONG    g_LockNumber;
ULONG    g_ComputerNumber;

CComputerFactory::CComputerFactory()
{
	m_Ref = 0;
}

CComputerFactory::~CComputerFactory()
{
}

HRESULT  CComputerFactory::QueryInterface(const IID& iid, void **ppv)
{
	if ( iid == IID_IUnknown )
	{
		*ppv = (IUnknown *) this ;
		((IUnknown *)(*ppv))->AddRef() ;
	} else if ( iid == IID_IClassFactory) 
	{
		*ppv = (IClassFactory *) this ;
		((IClassFactory *)(*ppv))->AddRef() ;
	} 
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE ;
	}
	return S_OK;
}

ULONG	  CComputerFactory::AddRef()
{
	m_Ref ++;
	return  (ULONG) m_Ref;
}

ULONG	  CComputerFactory::Release()
{
	m_Ref --;
	if (m_Ref == 0 ) {
		delete this;
		return 0;
	}
	return  (ULONG) m_Ref;
}

HRESULT CComputerFactory::CreateInstance(IUnknown *pUnknownOuter, 
										   const IID& iid, void **ppv)
{
	CComputer * pObj;   
	HRESULT hr;

	*ppv=NULL;
	hr=E_OUTOFMEMORY;
	if (NULL != pUnknownOuter)
		return CLASS_E_NOAGGREGATION;

	//Create the object passing function to notify on destruction.
	pObj=new CComputer();
	if (NULL==pObj)
		return hr;   

	//Obtain the first interface pointer (which does an AddRef)
	hr=pObj->QueryInterface(iid, ppv);

	if (hr != S_OK) {
		//Kill the object if initial creation or FInit failed.
		g_ComputerNumber --; // Reference count g_cComputer be added in constructor
		delete pObj;
	}

	return hr;   
}

HRESULT CComputerFactory::LockServer(BOOL bLock)
{
	if (bLock)
		g_LockNumber ++;
	else
		g_LockNumber --;

	return NOERROR;
}