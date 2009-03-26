// ReplayServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ReplayServer.h"
#include "ReplayServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CReplayServerDlg 对话框




CReplayServerDlg::CReplayServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReplayServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReplayServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CReplayServerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CRATE, &CReplayServerDlg::OnBnClickedCrate)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_STOP, &CReplayServerDlg::OnBnClickedStop)
END_MESSAGE_MAP()


// CReplayServerDlg 消息处理程序

BOOL CReplayServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	SetTimer(2,600000,NULL); //隔10分钟主动断掉连接,防止连接到错误端口不断开

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CReplayServerDlg::OnPaint()
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
HCURSOR CReplayServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CReplayServerDlg::OnBnClickedCrate()
{
	// TODO: 在此添加控件通知处理程序代码
	OnTimer(1);
	SetTimer(1,60000,NULL);
}

void CReplayServerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if(nIDEvent==1 && m_mySocket.m_bConnected == TRUE) return;
	if(nIDEvent==2)
	{
		m_mySocket.Close();
		Sleep(100);
		return;
	}
	CTime time; 
	time=::CTime::GetCurrentTime(); 
	CString str; 
	str=time.Format("%H:%M:%S"); 
	
	AddMessage(str + _T("发起连接..."));

	m_mySocket.Close();
	Sleep(100);
	m_mySocket.Create();
	m_mySocket.Connect(CString(_T("localhost")).GetBuffer(),9592);

	CDialog::OnTimer(nIDEvent);
}

void CReplayServerDlg::AddMessage(CString str)
{
	CString temp;
	GetDlgItemText(IDC_RICHEDIT21,temp);
	if( -1==str.Find(_T("\r")) && -1==str.Find(_T("\n")))
		str += _T("\n");
	temp += str;
	SetDlgItemText(IDC_RICHEDIT21,temp);

	CRichEditCtrl * m_RichEditCtrl = (CRichEditCtrl *)GetDlgItem(IDC_RICHEDIT21);
	m_RichEditCtrl->LineScroll(2,1);
}

void CReplayServerDlg::OnBnClickedStop()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
	AddMessage(_T("停止连接"));
}
