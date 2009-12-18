// ReplayClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ReplayClient.h"
#include "ReplayClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CReplayClientDlg 对话框




CReplayClientDlg::CReplayClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReplayClientDlg::IDD, pParent)
	, m_port(9600)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReplayClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_port);
	DDV_MinMaxInt(pDX, m_port, 1, 65535);
}

BEGIN_MESSAGE_MAP(CReplayClientDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SEND, &CReplayClientDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_LISTENING, &CReplayClientDlg::OnBnClickedListening)
END_MESSAGE_MAP()


// CReplayClientDlg 消息处理程序

BOOL CReplayClientDlg::OnInitDialog()
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

void CReplayClientDlg::OnPaint()
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
HCURSOR CReplayClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CReplayClientDlg::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CString temp;
	TCHAR buf[200];
	GetDlgItemText(IDC_SENDEDIT,buf,200);
	m_mySocket.m_Socket.Send(buf,sizeof(buf));
}

void CReplayClientDlg::OnBnClickedListening()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_mySocket.Create(m_port);
	m_mySocket.Listen();
}
