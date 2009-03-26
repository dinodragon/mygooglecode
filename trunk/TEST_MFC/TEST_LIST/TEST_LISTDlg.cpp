// TEST_LISTDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TEST_LIST.h"
#include "TEST_LISTDlg.h"

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


// CTEST_LISTDlg 对话框




CTEST_LISTDlg::CTEST_LISTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTEST_LISTDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CTEST_LISTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CTEST_LISTDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CTEST_LISTDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTEST_LISTDlg 消息处理程序

BOOL CTEST_LISTDlg::OnInitDialog()
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

void CTEST_LISTDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTEST_LISTDlg::OnPaint()
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
HCURSOR CTEST_LISTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTEST_LISTDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int aa = m_listCtrl.InsertColumn(1, TEXT("文件名 "),LVCFMT_CENTER,140); 
	aa = m_listCtrl.InsertColumn(2, TEXT("大小 "),LVCFMT_CENTER,80); 
	aa = m_listCtrl.InsertColumn(3, TEXT("类型 "),LVCFMT_CENTER,80); 
	aa = m_listCtrl.InsertColumn(4, TEXT("修改时间 "),LVCFMT_CENTER,130);
	
	m_listCtrl.ModifyStyle(NULL,LVS_REPORT);
	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	

	memset(&item,0,sizeof(item));
	item.mask = LVIF_TEXT;
	item.pszText=_T("faint");   
	item.iItem=1;
	int nitem =0; 
	//nitem=m_listCtrl.InsertItem(1, L"aaa ");
	//nitem=m_listCtrl.InsertItem(1, L"aaa ");
	//nitem=m_listCtrl.InsertItem(1, L"aaa ");
	//nitem=m_listCtrl.InsertItem(1, L"aaa ");
	//nitem=m_listCtrl.InsertItem(1, L"aaa ");
	nitem=m_listCtrl.InsertItem(&item);

	m_listCtrl.SetItemText(nitem,1, L"1 "); 
	m_listCtrl.SetItemText(nitem,2, L"2 "); 
	m_listCtrl.SetItemText(nitem,3, L"3 "); 

}
