#include <atlbase.h>
#include <atlwin.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

CComModule _module;

#define MAX_LOADSTRING 100
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= NULL;
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);

}


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd )
{
	_module.Init(0,hInstance);
	StrCpy(szWindowClass,_T("YangfeiCWin"));
	MyRegisterClass(hInstance);
	CWindow wnd;
	wnd.Create(szWindowClass,
		NULL,
		CWindow::rcDefault,
		_T("ÎÒµÄ³ÌÐò"),
		WS_OVERLAPPEDWINDOW
		);
	if(!wnd)
		return -1;
	wnd.CenterWindow();
	wnd.ShowWindow(nShowCmd);
	wnd.UpdateWindow();
	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	_module.Term();
	return (int) msg.wParam;

}

LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message)
	{
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			CWindow wnd(hWnd);
			HDC hdc = wnd.BeginPaint(&ps);
			RECT rect;
			wnd.GetClientRect(&rect);
			DrawText(hdc, __T("Hello, Windows.This is CWindowDemo"), -1, &rect,
				DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			wnd.EndPaint(&ps);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage (0) ;
		return 0 ;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);

	}
	return 0;
}
