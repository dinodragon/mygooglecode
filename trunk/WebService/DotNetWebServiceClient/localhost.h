//
// sproxy.exe generated file
// do not modify this file
//
// Created: 09/19/2009@10:43:58
//

#pragma once


#if !defined(_WIN32_WINDOWS) && !defined(_WIN32_WINNT) && !defined(_WIN32_WCE)
#pragma message("warning: defining _WIN32_WINDOWS = 0x0410")
#define _WIN32_WINDOWS 0x0410
#endif

#include <atlsoap.h>

namespace MyService
{

template <typename TClient = CSoapSocketClientT<> >
class CMyServiceT : 
	public TClient, 
	public CSoapRootHandler
{
protected:

	const _soapmap ** GetFunctionMap();
	const _soapmap ** GetHeaderMap();
	void * GetHeaderValue();
	const wchar_t * GetNamespaceUri();
	const char * GetServiceName();
	const char * GetNamespaceUriA();
	HRESULT CallFunction(
		void *pvParam, 
		const wchar_t *wszLocalName, int cchLocalName,
		size_t nItem);
	HRESULT GetClientReader(ISAXXMLReader **ppReader);

public:

	HRESULT __stdcall QueryInterface(REFIID riid, void **ppv)
	{
		if (ppv == NULL)
		{
			return E_POINTER;
		}

		*ppv = NULL;

		if (InlineIsEqualGUID(riid, IID_IUnknown) ||
			InlineIsEqualGUID(riid, IID_ISAXContentHandler))
		{
			*ppv = static_cast<ISAXContentHandler *>(this);
			return S_OK;
		}

		return E_NOINTERFACE;
	}

	ULONG __stdcall AddRef()
	{
		return 1;
	}

	ULONG __stdcall Release()
	{
		return 1;
	}

	CMyServiceT(ISAXXMLReader *pReader = NULL)
		:TClient(_T("http://localhost:3284/MyService.asmx"))
	{
		SetClient(true);
		SetReader(pReader);
	}
	
	~CMyServiceT()
	{
		Uninitialize();
	}
	
	void Uninitialize()
	{
		UninitializeSOAP();
	}	

	HRESULT Add(
		int x, 
		int y, 
		int* AddResult
	);

	HRESULT HelloWorld(
		BSTR* HelloWorldResult
	);
};

typedef CMyServiceT<> CMyService;

struct __CMyService_Add_struct
{
	int x;
	int y;
	int AddResult;
};

extern __declspec(selectany) const _soapmapentry __CMyService_Add_entries[] =
{

	{
		0x00000078, 
		"x", 
		L"x", 
		sizeof("x")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CMyService_Add_struct, x),
		NULL,
		NULL,
		-1,
	},
	{
		0x00000079, 
		"y", 
		L"y", 
		sizeof("y")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CMyService_Add_struct, y),
		NULL,
		NULL,
		-1,
	},
	{
		0xB5BB52A8, 
		"AddResult", 
		L"AddResult", 
		sizeof("AddResult")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CMyService_Add_struct, AddResult),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CMyService_Add_map =
{
	0x1181BCF8,
	"Add",
	L"AddResponse",
	sizeof("Add")-1,
	sizeof("AddResponse")-1,
	SOAPMAP_FUNC,
	__CMyService_Add_entries,
	sizeof(__CMyService_Add_struct),
	1,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0xC2E575C3,
	"http://tempuri.org/",
	L"http://tempuri.org/",
	sizeof("http://tempuri.org/")-1
};


struct __CMyService_HelloWorld_struct
{
	BSTR HelloWorldResult;
};

extern __declspec(selectany) const _soapmapentry __CMyService_HelloWorld_entries[] =
{

	{
		0x0588E51B, 
		"HelloWorldResult", 
		L"HelloWorldResult", 
		sizeof("HelloWorldResult")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CMyService_HelloWorld_struct, HelloWorldResult),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CMyService_HelloWorld_map =
{
	0x8AFDB82B,
	"HelloWorld",
	L"HelloWorldResponse",
	sizeof("HelloWorld")-1,
	sizeof("HelloWorldResponse")-1,
	SOAPMAP_FUNC,
	__CMyService_HelloWorld_entries,
	sizeof(__CMyService_HelloWorld_struct),
	1,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0xC2E575C3,
	"http://tempuri.org/",
	L"http://tempuri.org/",
	sizeof("http://tempuri.org/")-1
};

extern __declspec(selectany) const _soapmap * __CMyService_funcs[] =
{
	&__CMyService_Add_map,
	&__CMyService_HelloWorld_map,
	NULL
};

template <typename TClient>
inline HRESULT CMyServiceT<TClient>::Add(
		int x, 
		int y, 
		int* AddResult
	)
{
    if ( AddResult == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CMyService_Add_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.x = x;
	__params.y = y;

	__atlsoap_hr = SetClientStruct(&__params, 0);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_OUTOFMEMORY);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = GenerateResponse(GetWriteStream());
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_GENERATE_ERROR);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"http://tempuri.org/Add\"\r\n"));
	if (FAILED(__atlsoap_hr))
	{
		goto __skip_cleanup;
	}
	__atlsoap_hr = GetReadStream(&__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_READ_ERROR);
		goto __skip_cleanup;
	}
	
	// cleanup any in/out-params and out-headers from previous calls
	Cleanup();
	__atlsoap_hr = BeginParse(__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_PARSE_ERROR);
		goto __cleanup;
	}

	*AddResult = __params.AddResult;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CMyServiceT<TClient>::HelloWorld(
		BSTR* HelloWorldResult
	)
{
    if ( HelloWorldResult == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CMyService_HelloWorld_struct __params;
	memset(&__params, 0x00, sizeof(__params));

	__atlsoap_hr = SetClientStruct(&__params, 1);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_OUTOFMEMORY);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = GenerateResponse(GetWriteStream());
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_GENERATE_ERROR);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"http://tempuri.org/HelloWorld\"\r\n"));
	if (FAILED(__atlsoap_hr))
	{
		goto __skip_cleanup;
	}
	__atlsoap_hr = GetReadStream(&__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_READ_ERROR);
		goto __skip_cleanup;
	}
	
	// cleanup any in/out-params and out-headers from previous calls
	Cleanup();
	__atlsoap_hr = BeginParse(__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_PARSE_ERROR);
		goto __cleanup;
	}

	*HelloWorldResult = __params.HelloWorldResult;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
ATL_NOINLINE inline const _soapmap ** CMyServiceT<TClient>::GetFunctionMap()
{
	return __CMyService_funcs;
}

template <typename TClient>
ATL_NOINLINE inline const _soapmap ** CMyServiceT<TClient>::GetHeaderMap()
{
	static const _soapmapentry __CMyService_Add_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CMyService_Add_atlsoapheader_map = 
	{
		0x1181BCF8,
		"Add",
		L"AddResponse",
		sizeof("Add")-1,
		sizeof("AddResponse")-1,
		SOAPMAP_HEADER,
		__CMyService_Add_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0xC2E575C3,
		"http://tempuri.org/",
		L"http://tempuri.org/",
		sizeof("http://tempuri.org/")-1
	};

	static const _soapmapentry __CMyService_HelloWorld_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CMyService_HelloWorld_atlsoapheader_map = 
	{
		0x8AFDB82B,
		"HelloWorld",
		L"HelloWorldResponse",
		sizeof("HelloWorld")-1,
		sizeof("HelloWorldResponse")-1,
		SOAPMAP_HEADER,
		__CMyService_HelloWorld_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0xC2E575C3,
		"http://tempuri.org/",
		L"http://tempuri.org/",
		sizeof("http://tempuri.org/")-1
	};


	static const _soapmap * __CMyService_headers[] =
	{
		&__CMyService_Add_atlsoapheader_map,
		&__CMyService_HelloWorld_atlsoapheader_map,
		NULL
	};
	
	return __CMyService_headers;
}

template <typename TClient>
ATL_NOINLINE inline void * CMyServiceT<TClient>::GetHeaderValue()
{
	return this;
}

template <typename TClient>
ATL_NOINLINE inline const wchar_t * CMyServiceT<TClient>::GetNamespaceUri()
{
	return L"http://tempuri.org/";
}

template <typename TClient>
ATL_NOINLINE inline const char * CMyServiceT<TClient>::GetServiceName()
{
	return NULL;
}

template <typename TClient>
ATL_NOINLINE inline const char * CMyServiceT<TClient>::GetNamespaceUriA()
{
	return "http://tempuri.org/";
}

template <typename TClient>
ATL_NOINLINE inline HRESULT CMyServiceT<TClient>::CallFunction(
	void *, 
	const wchar_t *, int,
	size_t)
{
	return E_NOTIMPL;
}

template <typename TClient>
ATL_NOINLINE inline HRESULT CMyServiceT<TClient>::GetClientReader(ISAXXMLReader **ppReader)
{
	if (ppReader == NULL)
	{
		return E_INVALIDARG;
	}
	
	CComPtr<ISAXXMLReader> spReader = GetReader();
	if (spReader.p != NULL)
	{
		*ppReader = spReader.Detach();
		return S_OK;
	}
	return TClient::GetClientReader(ppReader);
}

} // namespace MyService
