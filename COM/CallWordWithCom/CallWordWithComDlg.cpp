// CallWordWithComDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CallWordWithCom.h"
#include "CallWordWithComDlg.h"

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


// CCallWordWithComDlg 对话框

_ApplicationPtr CCallWordWithComDlg::m_app;

CCallWordWithComDlg::CCallWordWithComDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCallWordWithComDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//CoInitialize(NULL);
}

CCallWordWithComDlg::~CCallWordWithComDlg()
{
	//CoUninitialize();
}


void CCallWordWithComDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCallWordWithComDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CCallWordWithComDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCallWordWithComDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCallWordWithComDlg 消息处理程序

BOOL CCallWordWithComDlg::OnInitDialog()
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

void CCallWordWithComDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCallWordWithComDlg::OnPaint()
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
HCURSOR CCallWordWithComDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCallWordWithComDlg::OnBnClickedOk()
{

	::CreateThread(NULL,0,CCallWordWithComDlg::Proc1,this,0,NULL);
	// TODO: 在此添加控件通知处理程序代码

	//OnOK();
}

DWORD WINAPI CCallWordWithComDlg::Proc1(PVOID pParam)
{
	CoInitialize(NULL);
	HRESULT hr = m_app.CreateInstance("Word.Application");
	ASSERT(SUCCEEDED(hr));
	DocumentsPtr pDocumentsPtr = m_app->GetDocuments();
	_variant_t vtReadOnly = true;
	_variant_t vtWordFileName = TEXT("E:\\aa.docx");
	_DocumentPtr pDocPtr = pDocumentsPtr->Open(&vtWordFileName,&vtMissing,&vtReadOnly);
	//Sleep(10000);
	pDocPtr->Close();
	pDocPtr.Release();
	pDocumentsPtr.Release();
	_variant_t saveChange = wdDoNotSaveChanges;
	hr = m_app->Quit(&saveChange);
	ASSERT(SUCCEEDED(hr));
	m_app.Release();
	CoUninitialize();
	return TRUE;
}

void CCallWordWithComDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//CoInitialize(NULL);
	//_variant_t saveChange = wdDoNotSaveChanges;
	//HRESULT hr = m_app->Quit(&saveChange);
	//ASSERT(SUCCEEDED(hr));
	//CoUninitialize();
	OnCancel();
}
