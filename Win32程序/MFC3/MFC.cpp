#include "my.h"//原该嵌入mfc.h就好,但为了CMyWinApp的定义,所以...

extern CMyWinApp theApp;

static char szCObject[] = "CObjct";
struct CRuntimeClass CObject::classCObject = 
{szCObject,sizeof(CObject),0xffff,NULL,NULL};

static AFX_CLASSINIT _init_CObject(&CObject::classCObject);

CRuntimeClass * CRuntimeClass::pFirstClass = NULL;

AFX_CLASSINIT::AFX_CLASSINIT(CRuntimeClass *pNewClass)
{
	pNewClass->m_pNextClass = CRuntimeClass::pFirstClass;
	CRuntimeClass::pFirstClass=pNewClass;
}

CRuntimeClass * CObject::GetRuntimeClass() const
{
	return &CObject::classCObject;
}

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

IMPLEMENT_DYNAMIC(CCmdTarget,CObject)
IMPLEMENT_DYNAMIC(CWinThread,CCmdTarget)
IMPLEMENT_DYNAMIC(CWinApp,CWinThread)
IMPLEMENT_DYNAMIC(CWnd,CCmdTarget)
IMPLEMENT_DYNAMIC(CFrameWnd,CWnd)
IMPLEMENT_DYNAMIC(CDocument,CCmdTarget)
IMPLEMENT_DYNAMIC(CView,CWnd)

CWinApp *AfxGetApp()
{
	return theApp.m_pCurrentWinApp;
}