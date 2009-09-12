// FtpDownLoaderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FtpDownLoader.h"
#include "FtpDownLoaderDlg.h"
#include "afxinet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFtpDownLoaderDlg 对话框




CFtpDownLoaderDlg::CFtpDownLoaderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFtpDownLoaderDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFtpDownLoaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFtpDownLoaderDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CFtpDownLoaderDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CFtpDownLoaderDlg 消息处理程序

BOOL CFtpDownLoaderDlg::OnInitDialog()
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

void CFtpDownLoaderDlg::OnPaint()
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
HCURSOR CFtpDownLoaderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFtpDownLoaderDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CInternetSession * m_pInetSession = new CInternetSession;   
	CFtpConnection *  m_pFtpConnection = m_pInetSession->GetFtpConnection(TEXT("bookserver"),TEXT("aa"),TEXT("aa"),21,FALSE);   

	if(m_pFtpConnection->GetFile(TEXT("a\\trace.log"),TEXT("c:\\1.log"),FALSE,FILE_ATTRIBUTE_NORMAL,FTP_TRANSFER_TYPE_BINARY,1))
	{   
		AfxMessageBox(TEXT("下载成功！"));
	}
	CString str;
	m_pFtpConnection->GetCurrentDirectory(str);
	m_pInetSession->Close();
	m_pFtpConnection->Close();
	delete m_pFtpConnection;
	m_pFtpConnection = NULL;
 	delete m_pInetSession;
	m_pInetSession = NULL;
	
	//OnOK();
}
