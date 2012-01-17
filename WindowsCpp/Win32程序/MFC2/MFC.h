#define BOOL int
#define TRUE 1
#define FALSE 0

#include <iostream>

using namespace std;

class CObject
{
public:
	CObject::CObject()
	{
		cout<<"CObject Constructor"<<endl;
	}
	CObject::~CObject()
	{
		cout<<"CObject Destructor"<<endl;
	}
};

class CCmdTarget:public CObject
{
public:
	CCmdTarget::CCmdTarget()
	{
		cout<<"CCmdTarget Constructor"<<endl;
	}
	CCmdTarget::~CCmdTarget()
	{
		cout<<"CCmdTarget Destructor"<<endl;
	}
};

class CWinThread:public CCmdTarget
{
public:
	CWinThread()
	{
		cout<<"CWinThread Constructor"<<endl;
	}
	virtual BOOL InitInstance()
	{
		cout<<"CWinThread::InitInstance"<<endl;
		return TRUE;
	}
	virtual int Run()
	{
		cout<<"CWinThread::Run"<<endl;
		return 1;
	}
	~CWinThread()
	{
		cout<<"CWinThread Destructor"<<endl;
	}
};

class CWnd;

class CWinApp:public CWinThread
{
public:
	CWinApp *m_pCurrentWinApp;
	CWnd *m_pMainWnd;
	CWinApp()
	{
		m_pCurrentWinApp = this;
		cout<<"CWinApp Constructor"<<endl;
	}
	virtual BOOL InitApplication()
	{
		cout<<"CWinAPP::InitApplication"<<endl;
		return TRUE;
	}
	virtual BOOL InitInstance()
	{
		cout<<"CWinApp::InitInstance"<<endl;
		return TRUE;
	}
	virtual int Run()
	{
		cout<<"CWinApp::Run"<<endl;
		return CWinThread::Run();
	}
	~CWinApp()
	{
		cout<<"CWinApp Destructor"<<endl;
	}
};

class CDocument:public CCmdTarget
{
public:
	CDocument()
	{
		cout<<"CDocument Constructor"<<endl;
	}
	~CDocument()
	{
		cout<<"CDocument Destrucotr"<<endl;
	}
};

class CWnd:public CCmdTarget
{
public:
	CWnd()
	{
		cout<<"CWnd Constructor"<<endl;
	}
	~CWnd()
	{
		cout<<"CWnd Destructor"<<endl;
	}
	virtual BOOL Create();
	BOOL CreateEx();
	virtual BOOL PreCreateWindow();
};

class CFrameWnd:public CWnd
{
public:
	CFrameWnd()
	{
		cout<<"CFrameWnd Constructor"<<endl;
	}
	~CFrameWnd()
	{
		cout<<"CFrameWnd Destructor"<<endl;
	}
	BOOL Create();
	virtual BOOL PreCreateWindow();
};

class CView:public CWnd
{
	CView()
	{
		cout<<"CView Constructor"<<endl;
	}
	~CView()
	{
		cout<<"CView Destructor"<<endl;
	}
};

//È«¾Öº¯Êý

CWinApp * AfxGetApp();