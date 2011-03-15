// MyCalc.h : CMyCalc ������

#pragma once
#include "resource.h"       // ������

#include "ATLDemo_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CMyCalc

class ATL_NO_VTABLE CMyCalc :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMyCalc, &CLSID_MyCalc>,
	public IDispatchImpl<IMyCalc, &IID_IMyCalc, &LIBID_ATLDemoLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CMyCalc()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MYCALC)


BEGIN_COM_MAP(CMyCalc)
	COM_INTERFACE_ENTRY(IMyCalc)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	STDMETHOD(Add)(LONG a, LONG b, LONG* rusult);
	STDMETHOD(Msg)();
	STDMETHOD(Msg2)(void);
};

OBJECT_ENTRY_AUTO(__uuidof(MyCalc), CMyCalc)
