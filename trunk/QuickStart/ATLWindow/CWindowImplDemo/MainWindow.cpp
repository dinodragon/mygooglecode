#include <atlbase.h>
#include <atlwin.h>

//一个基本的ATLCWindowImpl写的Windows程序。


class CMainWindow : public CWindowImpl<CMainWindow> 
{
	BEGIN_MSG_MAP(CMainWindow)
		MESSAGE_HANDLER( WM_PAINT, OnPaint )
		MESSAGE_HANDLER( WM_DESTROY, OnDestroy )
	END_MSG_MAP()

	LRESULT OnPaint( UINT, WPARAM, LPARAM, BOOL& )
	{
		PAINTSTRUCT ps;
		HDC         hdc = BeginPaint(&ps);
		RECT        rect; GetClientRect(&rect);
		DrawText(hdc, __T("Hello, Windows.This is CWindowImplDemo"), -1, &rect,
			DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		EndPaint(&ps);
		return 0;
	}

	LRESULT OnDestroy( UINT, WPARAM, LPARAM, BOOL& )
	{
		PostQuitMessage( 0 );
		return 0;
	}
};

// Entry point
int APIENTRY _tWinMain(HINSTANCE hinst,HINSTANCE /*hinstPrev*/,LPTSTR pszCmdLine,int nCmdShow) 
{
	CMainWindow wnd;
	wnd.Create(NULL, CMainWindow::rcDefault,__T("Windows Application"),  WS_OVERLAPPEDWINDOW|WS_VISIBLE);
	// Main message loop
	MSG msg;
	while( GetMessage(&msg, 0, 0, 0) ) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
