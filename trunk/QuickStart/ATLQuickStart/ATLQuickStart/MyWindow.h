#pragma once
#include "stdafx.h"
#include "resource.h"
#include "PaintBkgnd.h"

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
};