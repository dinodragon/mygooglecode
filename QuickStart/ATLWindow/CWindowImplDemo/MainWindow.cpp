#include <atlbase.h>
#include <atlwin.h>

//一个基本的ATLCWindowImpl写的Windows程序。
//并关联了一个编辑子窗口。

/////////////////////////////////////////////////////////////////////////////
// CEditQuote
class CEditQuote : public CWindowImpl<CEditQuote>
{
public:
	DECLARE_WND_SUPERCLASS(TEXT("EDITQUOTE"), TEXT("EDIT"))
	BEGIN_MSG_MAP(CEditQuote)
		//COMMAND_CODE_HANDLER(EN_SETFOCUS, OnSetFocus)
	END_MSG_MAP()
	CEditQuote(){};
	virtual ~CEditQuote(){};
};



class CMainWindow : public CWindowImpl<CMainWindow> 
{
	BEGIN_MSG_MAP(CMainWindow)
		CHAIN_MSG_MAP_MEMBER(m_EditWnd)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
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

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// create our EditQuote window and set the font.
		RECT rect = {0,0,200,30};
		m_EditWnd.Create(m_hWnd, rect, NULL, WS_CHILD|WS_VISIBLE, WS_EX_CLIENTEDGE);
		m_EditWnd.SetFont(static_cast<HFONT>(GetStockObject(DEFAULT_GUI_FONT)));
		return 0;
	}
	CEditQuote m_EditWnd;
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
