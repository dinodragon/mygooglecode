#include "my.h"

CMyWinApp theApp;  //ȫ�ֶ���

BOOL CMyWinApp::InitInstance()
{
	cout<<"CMyWinApp::InitInstance"<<endl;
	m_pMainWnd = new CMyFrameWnd;
	return TRUE;
}

CMyFrameWnd::CMyFrameWnd()
{
	cout<<"CMyFrameWnd Constructor"<<endl;
	cout<<"CMyFrameWnd::CMyFrameWnd"<<endl;
	Create();
}

void main()
{
	CWinApp *pApp = AfxGetApp();
	pApp->InitApplication();
	pApp->InitInstance();
	pApp->Run();
}