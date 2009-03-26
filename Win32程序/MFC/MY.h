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
};

class CMyFrameWnd:public CFrameWnd
{
public:
	CMyFrameWnd()
	{
		cout<<"CMyFrameWnd Constructor"<<endl;
	}
	~CMyFrameWnd()
	{
		cout<<"CMyFrameWnd Destructor"<<endl;
	}
};