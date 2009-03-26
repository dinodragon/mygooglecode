// TEST_dialogDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TEST_dialog.h"
#include "TEST_dialogDlg.h"

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


// CTEST_dialogDlg 对话框




CTEST_dialogDlg::CTEST_dialogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTEST_dialogDlg::IDD, pParent)
	, value(0)
	, boolv(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTEST_dialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Value, value);
	DDV_MinMaxInt(pDX, value, 0, 100);
	DDX_Control(pDX, IDC_LIST1, list);
	DDX_Control(pDX, IDC_TREE1, tree);
	DDX_Check(pDX, IDC_CHECK1, boolv);
	DDX_Control(pDX, IDC_CHECK1, ccheck);
}

BEGIN_MESSAGE_MAP(CTEST_dialogDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDYES, &CTEST_dialogDlg::OnBnClickedYes)
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &CTEST_dialogDlg::OnNMClickTree1)
	ON_BN_CLICKED(IDC_BUTTON1, &CTEST_dialogDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTEST_dialogDlg 消息处理程序

BOOL CTEST_dialogDlg::OnInitDialog()
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

	ShowWindow(SW_SHOWDEFAULT);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTEST_dialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTEST_dialogDlg::OnPaint()
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
HCURSOR CTEST_dialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTEST_dialogDlg::OnBnClickedYes()
{
	// TODO: 在此添加控件通知处理程序代码
	list.InsertColumn(1, TEXT("文件名 "),LVCFMT_CENTER,140); 
	list.InsertColumn(2, TEXT("大小 "),LVCFMT_CENTER,80); 
	list.InsertColumn(3, TEXT("类型 "),LVCFMT_CENTER,80); 
	list.InsertColumn(4, TEXT("修改时间 "),LVCFMT_CENTER,130); 
	list.ModifyStyle(NULL,LVS_REPORT);
	int   nitem; 
	nitem=list.InsertItem(1, L"aaa "); 
	list.SetItemText(nitem,1, L"cc "); 
	list.SetItemText(nitem,2, L"cc "); 
	list.SetItemText(nitem,3, L"cc "); 
	list.SetItemText(nitem,4, L"cc "); 

	tree.InsertItem(TEXT("aa"));
	UpdateData(false);

}

void CTEST_dialogDlg::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CTEST_dialogDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//::CreateThread(NULL,0,Proc1,this,0,NULL);
	//::CreateThread(NULL,0,Proc2,this,0,NULL);
	g_Mutex.Lock();
	g_Mutex.Lock();
	g_Mutex.Lock();
	g_Mutex.Lock();
	g_Mutex.Unlock();
	g_Mutex.Unlock();
	g_Mutex.Unlock();
	g_Mutex.Unlock();
}




DWORD WINAPI Proc1(PVOID pParam)
{
	CString temp;
	for(int i=0;i<10;i++)
	{
		g_Mutex.Lock();
		((CTEST_dialogDlg *)pParam)->GetDlgItemText(IDC_RICHEDIT21,temp);
		temp += TEXT("线程一！\n");
		((CTEST_dialogDlg *)pParam)->SetDlgItemText(IDC_RICHEDIT21,temp);
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
		((CTEST_dialogDlg *)pParam)->GetDlgItemText(IDC_RICHEDIT21,temp);
		temp += TEXT("线程二！\n");
		((CTEST_dialogDlg *)pParam)->SetDlgItemText(IDC_RICHEDIT21,temp);
		g_Mutex.Unlock();
	}
	return 0;
}
