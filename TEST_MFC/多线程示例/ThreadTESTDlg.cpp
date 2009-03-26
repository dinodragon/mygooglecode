// 多线程示例Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ThreadTEST.h"
#include "ThreadTESTDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef G_MUTEX
	#define G_MUTEX
	CMutex g_Mutex;
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


// C多线程示例Dlg 对话框




CThreadTESTDlg::CThreadTESTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CThreadTESTDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CThreadTESTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CThreadTESTDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_START, &CThreadTESTDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_BUTTON2, &CThreadTESTDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// C多线程示例Dlg 消息处理程序

BOOL CThreadTESTDlg::OnInitDialog()
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

void CThreadTESTDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CThreadTESTDlg::OnPaint()
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
HCURSOR CThreadTESTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CThreadTESTDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_RICHEDIT21,TEXT(""));
}

void CThreadTESTDlg::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码
	::CreateThread(NULL,0,Proc1,this,0,NULL);
	::CreateThread(NULL,0,Proc2,this,0,NULL);
}

DWORD WINAPI Proc1(PVOID pParam)
{
	CString temp;
	for(int i=0;i<10;i++)
	{
		g_Mutex.Lock();
		((CThreadTESTDlg *)pParam)->GetDlgItemText(IDC_RICHEDIT21,temp);
		add1(temp);
		((CThreadTESTDlg *)pParam)->SetDlgItemText(IDC_RICHEDIT21,temp);
		g_Mutex.Unlock();
	}
	return 0;
}

DWORD WINAPI Proc2(PVOID pParam)
{
	CString temp;
	for(int i=0;i<10;i++)
	{
		g_Mutex.Lock();
		((CThreadTESTDlg *)pParam)->GetDlgItemText(IDC_RICHEDIT21,temp);
		add2(temp);
		((CThreadTESTDlg *)pParam)->SetDlgItemText(IDC_RICHEDIT21,temp);
		g_Mutex.Unlock();
	}
	return 0;
}

VOID add1(CString &str)
{
	g_Mutex.Lock();
	str += TEXT("线程一！\n");
	//g_Mutex.Unlock();
}

VOID add2(CString &str)
{
	str += TEXT("第二个线程！\n");
}

