#include "my.h"//原该嵌入mfc.h就好,但为了CMyWinApp的定义,所以...

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