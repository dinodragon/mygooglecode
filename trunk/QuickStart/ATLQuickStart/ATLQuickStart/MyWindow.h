#pragma once
#include "stdafx.h"
#include "resource.h"
#include "PaintBkgnd.h"
#include "AboutDlg.h"

extern CComModule _Module;
//定义一个窗口的类型
typedef CWinTraits<WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,WS_EX_APPWINDOW> CMyWindowTraits;

class CMyWindow : public CWindowImpl<CMyWindow, CWindow, CMyWindowTraits>,public CPaintBkgnd<CMyWindow, RGB(0,0,255)>
{
public:
	//需要进行重命名，否则在宏展开后会因为逗号的原因被认为成两个类
	typedef CPaintBkgnd<CMyWindow, RGB(0,0,255)> CPaintBkgndBase;
	DECLARE_WND_CLASS(_T("My Window Class"))
	BEGIN_MSG_MAP(CMyWindow)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_CREATE,OnCreate)
		COMMAND_ID_HANDLER(IDC_ABOUT, OnAbout)
		//将CPaintBkgndBase类加入消息链，当消息被上面的处理器未处理时，会交给CPaintBkgndBase类
		CHAIN_MSG_MAP(CPaintBkgndBase)
	END_MSG_MAP()

	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DestroyWindow();
		return 0;
	}

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		PostQuitMessage(0);
		return 0;
	}

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		HMENU hmenu = LoadMenu ( _Module.GetResourceInstance(),	MAKEINTRESOURCE(IDR_MENU1));
		SetMenu ( hmenu );
		return 0;
	}

	LRESULT OnAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		CAboutDlg dlg;
		dlg.DoModal();
		return 0;
	}

};