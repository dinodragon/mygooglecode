#include "my.h"//ԭ��Ƕ��mfc.h�ͺ�,��Ϊ��CMyWinApp�Ķ���,����...

extern CMyWinApp theApp;

BOOL CWnd::Create()
{
	cout<<"CWnd::Create"<<endl;
	return TRUE;
}

BOOL CWnd::CreateEx()
{
	cout<<"CWnd::CreateEx"<<endl;
	PreCreateWindow();
	return TRUE;
}

BOOL CWnd::PreCreateWindow()
{
	cout<<"CWnd::PreCreateWindow"<<endl;
	return TRUE;
}

BOOL CFrameWnd::Create()
{
	cout<<"CFrameWnd::Create"<<endl;
	CreateEx();
	return TRUE;
}

BOOL CFrameWnd::PreCreateWindow()
{
	cout<<"CFrameWnd::PreCreateWindow"<<endl;
	return TRUE;
}

CWinApp * AfxGetApp()
{
	return theApp.m_pCurrentWinApp;
}