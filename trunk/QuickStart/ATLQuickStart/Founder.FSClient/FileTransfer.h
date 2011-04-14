// FileTransfer.h : Declaration of the CFileTransfer

#pragma once
#include "resource.h"       // main symbols

#include "FounderFSClient_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CFileTransfer

class ATL_NO_VTABLE CFileTransfer :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFileTransfer, &CLSID_FileTransfer>,
	public IDispatchImpl<IFileTransfer, &IID_IFileTransfer, &LIBID_FounderFSClientLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CFileTransfer()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_FILETRANSFER)


BEGIN_COM_MAP(CFileTransfer)
	COM_INTERFACE_ENTRY(IFileTransfer)
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

	STDMETHOD(FtpUpload)(BSTR UserName, BSTR Password, BSTR RemotePath, BSTR LocalPath, BSTR* Result);
	STDMETHOD(Upload)(BSTR RemotePath, BSTR LocalPath, BSTR* Result);
	STDMETHOD(FtpDownload)(BSTR UserName, BSTR Password, BSTR RemotePath, BSTR LocalPath, BSTR* Result);
	STDMETHOD(Download)(BSTR RemotePath, BSTR LocalPath, BSTR* Result);
};

OBJECT_ENTRY_AUTO(__uuidof(FileTransfer), CFileTransfer)
