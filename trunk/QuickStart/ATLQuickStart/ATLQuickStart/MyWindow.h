#pragma once
#include "stdafx.h"
#include "resource.h"
#include "PaintBkgnd.h"
#include "AboutDlg.h"

extern CComModule _Module;
//����һ�����ڵ�����
typedef CWinTraits<WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,WS_EX_APPWINDOW> CMyWindowTraits;

class CMyWindow : public CWindowImpl<CMyWindow, CWindow, CMyWindowTraits>,public CPaintBkgnd<CMyWindow, RGB(0,0,255)>
{
public:
	//��Ҫ�����������������ں�չ�������Ϊ���ŵ�ԭ����Ϊ��������
	typedef CPaintBkgnd<CMyWindow, RGB(0,0,255)> CPaintBkgndBase;
	DECLARE_WND_CLASS(_T("My Window Class"))
	BEGIN_MSG_MAP(CMyWindow)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_CREATE,OnCreate)
		COMMAND_ID_HANDLER(IDC_ABOUT, OnAbout)
		//��CPaintBkgndBase�������Ϣ��������Ϣ������Ĵ�����δ����ʱ���ύ��CPaintBkgndBase��
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