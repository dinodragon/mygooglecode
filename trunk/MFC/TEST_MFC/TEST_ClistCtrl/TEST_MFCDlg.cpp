// TEST_MFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TEST_MFC.h"
#include "TEST_MFCDlg.h"

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


// CTEST_MFCDlg 对话框




CTEST_MFCDlg::CTEST_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTEST_MFCDlg::IDD, pParent)
	, index(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTEST_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, list);
}

BEGIN_MESSAGE_MAP(CTEST_MFCDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CTEST_MFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTEST_MFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTEST_MFCDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &CTEST_MFCDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &CTEST_MFCDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CTEST_MFCDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CTEST_MFCDlg 消息处理程序

BOOL CTEST_MFCDlg::OnInitDialog()
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

void CTEST_MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTEST_MFCDlg::OnPaint()
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
HCURSOR CTEST_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTEST_MFCDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	list.InsertColumn(0,TEXT("第一列"),LVCFMT_LEFT,60);
	list.InsertColumn(4,TEXT("第四列"),LVCFMT_CENTER,60);
	list.InsertColumn(3,TEXT("第三列"),LVCFMT_CENTER,60);
	list.InsertColumn(9,TEXT("第二列"),LVCFMT_CENTER,60);
	list.SetExtendedStyle(LVS_EX_GRIDLINES);
}

void CTEST_MFCDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR buf[20] = TEXT("内容二");
	wsprintf(buf,L"内容%d",index);
	//list.InsertItem(index++,buf,IDB_BITMAP1);
	LVITEM lvitem;
	memset(&lvitem,0,sizeof(lvitem));
	lvitem.mask = LVIF_TEXT;
	lvitem.pszText = buf;
	lvitem.iItem = index++;
	lvitem.iSubItem = 0;
	list.InsertItem(&lvitem);
}

void CTEST_MFCDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	list.SetView(LVS_REPORT);
}

void CTEST_MFCDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	list.SetView(LVS_ICON);
}

void CTEST_MFCDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	list.SetView(LVS_SMALLICON);
}

void CTEST_MFCDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	list.SetView(LVS_LIST);
}
