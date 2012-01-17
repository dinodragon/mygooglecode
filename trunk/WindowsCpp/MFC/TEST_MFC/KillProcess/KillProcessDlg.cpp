// KillProcessDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "KillProcess.h"
#include "KillProcessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CKillProcessDlg 对话框




CKillProcessDlg::CKillProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKillProcessDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKillProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKillProcessDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CKillProcessDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CKillProcessDlg 消息处理程序

BOOL CKillProcessDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CKillProcessDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CKillProcessDlg::OnPaint()
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
//
HCURSOR CKillProcessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CKillProcessDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD dwCount;
	DWORD * m_pids;
	DWORD nalloc = 1024;
	m_pids = new DWORD[nalloc];
	if (EnumProcesses(m_pids, nalloc*sizeof(DWORD), &dwCount))
	{
		dwCount /= sizeof(DWORD);
	}
	for (DWORD i=1;i < dwCount;i++)
	{
		if (IsProcessContainModName(m_pids[i],TEXT("WinWord.exe")))
		{
			CloseProcess(m_pids[i]);
		}		
	}
	delete[] m_pids;
	OnOK();
}

BOOL CKillProcessDlg::CloseProcess(DWORD dwProcessId,BOOL bForce)
{
	HANDLE hp = OpenProcess(SYNCHRONIZE|PROCESS_TERMINATE,FALSE,dwProcessId);
	TerminateProcess(hp,0);
	return FALSE;
}

BOOL CKillProcessDlg::IsProcessContainModName(DWORD dwProcessId,LPCTSTR szModeName)
{
	CString NeedKillModName(szModeName);
	HMODULE * hModules = NULL;
	DWORD m_dwModCount = 0;
	DWORD nalloc = 1024;
	BOOL result = FALSE;
	TCHAR modName[_MAX_PATH];
	HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE,dwProcessId);
	if (handle) 
	{
		hModules = new HMODULE[nalloc];
		if (EnumProcessModules(handle, hModules,nalloc*sizeof(HMODULE), &m_dwModCount)) 
		{
			m_dwModCount /= sizeof(HMODULE);
		}
		for (DWORD j = 0 ;j<m_dwModCount ;j++)
		{
			GetModuleBaseName(handle,hModules[j],modName,_MAX_PATH);
			if (NeedKillModName.CompareNoCase(modName)==0)
			{
				result = TRUE;
				break;
			}
		}
		delete[] hModules;
	}
	CloseHandle(handle);
	return result;
}