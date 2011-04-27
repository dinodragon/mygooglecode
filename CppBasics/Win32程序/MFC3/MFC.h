#include <iostream>
#define BOOL int
#define TRUE 1
#define FALSE 0
#define LPCSTR LPSTR
typedef char *LPSTR;
#define UINT int
#define PASCAL _stdcall

using namespace std;
class CObject;

struct CRuntimeClass
{
	LPCSTR m_lpszClassName;
	int m_nObjectSize;
	UINT m_wSchema;
	void (PASCAL * m_pfnConstruct)(void *p);//NULL =>abstract class
	CRuntimeClass * m_pBaseClass;

	static CRuntimeClass * pFirstClass;
	CRuntimeClass * m_pNextClass;
};

struct AFX_CLASSINIT
{
	AFX_CLASSINIT(CRuntimeClass * pNewClass);
};

#define RUNTIME_CLASS(class_name) (&class_name::class##class_name)

#define DECLARE_DYNAMIC(class_name)\
public:\
	static CRuntimeClass class##class_name;\
	virtual CRuntimeClass *GetRuntimeClass() const;

#define _IMPLEMENT_RUNTIMECLASS(class_name,base_class_name,wSchema,pfnNew)\
	static char _lpsz##class_name[] = #class_name;\
	CRuntimeClass class_name::class##class_name={\
	_lpsz##class_name,sizeof(class_name),wSchema,pfnNew,\
	RUNTIME_CLASS(base_class_name),NULL};\
	static AFX_CLASSINIT _init_##class_name(&class_name::class##class_name);\
	CRuntimeClass * class_name::GetRuntimeClass() const\
	{return &class_name::class##class_name;}

#define IMPLEMENT_DYNAMIC(class_name,base_class_name)\
	_IMPLEMENT_RUNTIMECLASS(class_name,base_class_name,0xFFFF,NULL)



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
	virtual CRuntimeClass * GetRuntimeClass() const;
	static CRuntimeClass classCObject;
};

class CCmdTarget:public CObject
{
	DECLARE_DYNAMIC(CCmdTarget);
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
	DECLARE_DYNAMIC(CWinThread);
public:
	CWinThread()
	{
		cout<<"CWinThread Constructor"<<endl;
	}
	~CWinThread()
	{
		cout<<"CWinThread Destructor"<<endl;
	}
	virtual BOOL InitInstance()
	{
		return TRUE;
	}
	virtual int Run()
	{
		return 1;
	}
};

class CWnd;
class CWinApp:public CWinThread
{
	DECLARE_DYNAMIC(CWinApp);
public:
	CWinApp *m_pCurrentWinApp;
	CWnd * m_pMainWnd;

	CWinApp()
	{
		cout<<"CWinApp Constructor"<<endl;
		m_pCurrentWinApp=this;
	}
	~CWinApp()
	{
		cout<<"CWinApp Destructor"<<endl;
	}
	virtual BOOL InitApplication()
	{
		return TRUE;
	}
	virtual BOOL InitInstance(){return TRUE;}
	virtual int Run(){return CWinThread::Run();}
};

class CDocument:public CCmdTarget
{
	DECLARE_DYNAMIC(CDocument);
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
	DECLARE_DYNAMIC(CWnd);
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
	DECLARE_DYNAMIC(CFrameWnd)
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
	DECLARE_DYNAMIC(CView);
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