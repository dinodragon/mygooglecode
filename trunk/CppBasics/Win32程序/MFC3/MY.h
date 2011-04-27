#include <iostream>
#include "mfc.h"

using namespace std;

class CMyWinApp:public CWinApp
{
public:
	CMyWinApp()
	{
		cout<<"CMyWinApp Constructor\n"<<endl;
	}
	~CMyWinApp()
	{
		cout<<"CMyWinApp Destructor"<<endl;
	}
	virtual BOOL InitInstance();
};

class CMyFrameWnd:public CFrameWnd
{
public:
	CMyFrameWnd();
	~CMyFrameWnd()
	{
		cout<<"CMyFrameWnd Destructor"<<endl;
	}
};

class CMyDoc:public CDocument
{
public:
	CMyDoc::CMyDoc(){}
	CMyDoc::~CMyDoc(){}
};

class CMyView:public CView
{
public:
	CMyView::CMyView(){}
	~CMyView(){}
};

void PrintAllClasses();