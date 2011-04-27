#include "stdafx.h"
#include "hello.h"
#include "resource.h"


CMyWinApp theApp;

BOOL CMyWinApp::InitInstance()
{
	m_pMainWnd = new CMyFrameWnd();

	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

CMyFrameWnd::CMyFrameWnd()
{

	Create(NULL,"MyMFC",WS_OVERLAPPEDWINDOW,rectDefault,NULL,"MainMenu");

}

BEGIN_MESSAGE_MAP(CMyFrameWnd,CFrameWnd)
	ON_COMMAND(IDM_ABOUT,OnAbout)
	ON_WM_PAINT()
	ON_COMMAND(ID_HELP_OPEN,OnOpen)
END_MESSAGE_MAP()

void CMyFrameWnd::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;

	GetClientRect(rect);
	dc.SetTextAlign(TA_BOTTOM|TA_CENTER);
	static TCHAR szText[] = "Hello,MFC";
	dc.TextOut(rect.right/2,rect.bottom/2,szText,sizeof(szText)-1);
}

void CMyFrameWnd::OnAbout()
{
	CDialog about("About_Box",this);
	about.DoModal();
}
void CMyFrameWnd::OnOpen(void)
{
	//char szFileters[] = "文本文件(*.txt)|*.txt|图片(*.jpg)|*.jpg";
	char szFileters[] = "Chart Files (*.xlc)|*.xlc|Worksheet Files (*.xls)|*.xls|Data Files (*.xlc;*.xls)|*.xlc;*.xls|All Files (*.*)|*.*||";
	
	CString name;
	CFileDialog opendlg(true,"txt","*.txt",OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,szFileters,this);
	if(opendlg.DoModal()==IDOK)
	{
		name = opendlg.GetPathName();
	}

}
