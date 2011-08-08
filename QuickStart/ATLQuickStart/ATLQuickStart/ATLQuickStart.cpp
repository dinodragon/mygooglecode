// ATLQuickStart.cpp : WinMain µÄÊµÏÖ


#include "stdafx.h"
#include "resource.h"
#include "ATLQuickStart_i.h"
#include "dlldatax.h"
#include "MyWindow.h"

//class CATLQuickStartModule : public CAtlExeModuleT< CATLQuickStartModule >
//{
//public :
//	DECLARE_LIBID(LIBID_ATLQuickStartLib)
//	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLQUICKSTART, "{1D0C7C17-AA41-4206-98BF-095AE7624C7B}")
//};
//
//
//CATLQuickStartModule _AtlModule;
CComModule _Module;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
                                LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	_Module.Init(NULL, NULL);
	CMyWindow myWindow;
	MSG msg;

	// Create & show our main window
	if ( NULL == myWindow.Create ( NULL, CWindow::rcDefault, _T("My First ATL Window") ))
	{
		// Bad news, window creation failed
		return 1;
	}

	myWindow.ShowWindow(nShowCmd);
	myWindow.UpdateWindow();

	// Run the message loop
	while ( GetMessage(&msg, NULL, 0, 0) > 0 )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	_Module.Term();
	return (int)msg.wParam;;
}

