#ifndef __Computer_H__
#define __Computer_H__

#ifndef __ICale_H__
#include "ICale.h"
#endif

class CComputer : public ICale
{
	public :
		CComputer();
		~CComputer();
	public :
	// IUnknown member function
		virtual HRESULT __stdcall QueryInterface(const IID& iid, void **ppv) ;
		virtual ULONG	__stdcall AddRef() ; 
		virtual ULONG	__stdcall Release() ;

	// ICale member function
		virtual BOOL __stdcall Initialize();
		virtual BOOL __stdcall Add(int,int ,int *);
private :
	int		m_Ref ;
};

#endif // __DictComp_H__