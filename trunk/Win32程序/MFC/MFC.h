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
	~CWinThread()
	{
		cout<<"CWinThread Destructor"<<endl;
	}
};

class CWinApp:public CWinThread
{
public:
	CWinApp *m_pCurrentWinApp;
	CWinApp()
	{
		cout<<"CWinApp Constructor"<<endl;
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