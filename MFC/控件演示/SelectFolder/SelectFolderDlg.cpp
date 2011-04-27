// SelectFolderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SelectFolder.h"
#include "SelectFolderDlg.h"
#include "folder_dialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSelectFolderDlg 对话框

CSelectFolderDlg::CSelectFolderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectFolderDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSelectFolderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSelectFolderDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CSelectFolderDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSelectFolderDlg 消息处理程序

BOOL CSelectFolderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSelectFolderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CSelectFolderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData) 
{ 
	static HWND hWndEdit = NULL;
	switch(uMsg)
	{ 
	case BFFM_INITIALIZED:
		{
			HWND hChildWindow;
			hChildWindow = GetWindow(hwnd, GW_CHILD);
			while(hChildWindow)
			{
				TCHAR szClass[MAX_PATH];
				GetClassName(hChildWindow, szClass, MAX_PATH);
				if(0 == wcscmp(szClass, L"Edit"))
				{
					hWndEdit = hChildWindow;
					break;
				}
				hChildWindow = GetNextWindow(hChildWindow, GW_HWNDNEXT);
			}
			::SendMessage(hwnd,BFFM_SETSELECTION,TRUE,lpData); 
		}
		break;
	case BFFM_VALIDATEFAILED:
		{
			MessageBoxW(hwnd, _T("路径不合法，请重新输入！"), _T("自动监控"), MB_ICONWARNING|MB_OK);
			return 1;
		}
		break;
	case BFFM_SELCHANGED:
		{
			TCHAR buf[MAX_PATH];
			if (::SHGetPathFromIDList((LPITEMIDLIST) lParam ,buf)) 
			{
				if(hWndEdit != NULL)
					SetWindowText(hWndEdit, buf);
			}
			else
				::SendMessage(hwnd, BFFM_ENABLEOK, 0, 0);
		}
		break;
	}
	return 0; 
} 

void CSelectFolderDlg::OnBnClickedOk()
{
	CoInitialize(NULL);
	BROWSEINFO bi;
	TCHAR   Buffer[512]=L"";   
	TCHAR   FullPath[512]=L"";   
	bi.hwndOwner = m_hWnd; 
	bi.pidlRoot = NULL;   
	bi.pszDisplayName   =   Buffer; 
	bi.lpszTitle   =   L"选择监控目录"; 
	bi.ulFlags   =  BIF_EDITBOX|BIF_VALIDATE | BIF_NEWDIALOGSTYLE|BIF_NONEWFOLDERBUTTON  ;
	bi.lpfn   =   BrowseCallbackProc;
	TCHAR initPath[] = L"";
	bi.lParam   =  (LPARAM)initPath;   
	bi.iImage   =   0;   
	ITEMIDLIST* pidl = ::SHBrowseForFolder(&bi);
	if(::SHGetPathFromIDList(pidl,FullPath))
	{   
		AfxMessageBox(FullPath);
	}   
	CoUninitialize();
	//OnOK();
}

