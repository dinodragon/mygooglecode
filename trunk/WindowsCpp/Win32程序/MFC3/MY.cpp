#include "my.h"

CMyWinApp theApp;  //全局对象

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

void PrintAllClasses()
{
	CRuntimeClass * pClass;
	for(pClass=CRuntimeClass::pFirstClass;pClass!=NULL;
		pClass=pClass->m_pNextClass)
	{
		cout<<pClass->m_lpszClassName<<endl;
		cout<<pClass->m_nObjectSize<<endl;
		cout<<pClass->m_wSchema<<endl;
	}
}


void main()
{
	CWinApp *pApp = AfxGetApp();

	pApp->InitApplication();
	pApp->InitInstance();
	pApp->Run();

	PrintAllClasses();
}