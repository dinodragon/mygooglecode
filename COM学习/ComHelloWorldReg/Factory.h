#ifndef __Computer_FACTORY__
#define __Computer_FACTORY__

#include "Unknwn.h"

class CComputerFactory : public IClassFactory
{
protected:
	ULONG           m_Ref;

public:
	CComputerFactory ();
	~CComputerFactory ();

	//IUnknown members
	HRESULT __stdcall QueryInterface(const IID& iid, void **ppv);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	//IClassFactory members
	HRESULT __stdcall CreateInstance(IUnknown *, const IID& iid, void **ppv);
	HRESULT __stdcall LockServer(BOOL);
};

#endif //