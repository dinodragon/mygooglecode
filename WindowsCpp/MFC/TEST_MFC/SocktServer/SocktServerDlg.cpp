// SocktServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SocktServer.h"
#include "SocktServerDlg.h"

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


// CSocktServerDlg 对话框




CSocktServerDlg::CSocktServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSocktServerDlg::IDD, pParent)
	, m_port(2561)
	, m_RichText(_T(""))
	, m_ServerPort(21)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CSocktServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PORT, m_port);
	DDV_MinMaxInt(pDX, m_port, 1, 65535);
	DDX_Text(pDX, IDC_RICHEDIT21, m_RichText);
	DDX_Control(pDX, IDC_RICHEDIT21, m_RichEditCtrl);
	DDX_Text(pDX, IDC_SERVERPORT, m_ServerPort);
	DDV_MinMaxInt(pDX, m_ServerPort, 0, 65535);
}

BEGIN_MESSAGE_MAP(CSocktServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CREATSERVER, &CSocktServerDlg::OnBnClickedCreatserver)
	ON_BN_CLICKED(IDC_CONNECT, &CSocktServerDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDOK, &CSocktServerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CSocktServerDlg::OnBnClickedButtonSend)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_STOPLISTEN, &CSocktServerDlg::OnBnClickedStoplisten)
END_MESSAGE_MAP()


// CSocktServerDlg 消息处理程序

BOOL CSocktServerDlg::OnInitDialog()
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

void CSocktServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSocktServerDlg::OnPaint()
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
HCURSOR CSocktServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSocktServerDlg::OnBnClickedCreatserver()
{
	// TODO: 在此添加控件通知处理程序代码
	UINT err = 0;;

	if(UpdateData()==false || m_Socket.m_hSocket !=INVALID_SOCKET) return;
	
	BOOL bFlag=m_Socket.Create(m_port,SOCK_STREAM); 
	if(!bFlag)
	{
		TCHAR buf[256];
		err = m_Socket.GetLastError();
		wsprintf(buf,TEXT("Socket 错误! 错误码：%d\r\n"),err);
		MessageBox(buf);
		return;
	}
	else
	{
		m_Socket.Listen(1);
		TCHAR buf[256];
		err = m_Socket.GetLastError();
		wsprintf(buf,TEXT("Socket初始化正常，在端口：%d 监听,Return Code %d\n"),m_port,err);
		m_RichText += buf;
		UpdateData(FALSE);
	}
	UpdateData(false);
}

void CSocktServerDlg::OnBnClickedStoplisten()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Socket.Close();
	CString temp;
	GetDlgItemText(IDC_RICHEDIT21,temp);
	temp += TEXT("停止监听\n");
	SetDlgItemText(IDC_RICHEDIT21,temp);
}


void CSocktServerDlg::OnBnClickedConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR buf[2048];
	int err = 0;
	GetDlgItemText(IDC_SERVERIP,m_serverIP);
	if(UpdateData()==false || m_Socket.m_hSocket !=INVALID_SOCKET) return;

	BOOL bFlag=m_Socket.Create(0,SOCK_STREAM,FD_CONNECT);
	if(!bFlag)
	{
		TCHAR buf[256];
		err = m_Socket.GetLastError();
		wsprintf(buf,TEXT("Socket 错误! 错误码：%d"),err);
		MessageBox(buf);
		return;
	}
	//连接代理
	bFlag=m_Socket.Connect(m_serverIP,m_ServerPort);
	//bFlag=m_Socket.Connect(TEXT("192.168.75.1"),808);
	
	err = m_Socket.GetLastError();
	if(bFlag && err!=10035)
	{
		TCHAR buf[256];
		wsprintf(buf,TEXT("连接失败! Error Code %d"),err);
		MessageBox(buf);
		return;
	}
}

void CSocktServerDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RichText += TEXT("新的一行\r\n");
	UpdateData(false);
	//OnOK();
}

void CSocktServerDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_Socket.m_bConnected == TRUE)
	{
		TCHAR buf[256];
		GetDlgItemText(IDC_EDIT_SEND,buf,256);
		SetDlgItemText(IDC_EDIT_SEND,TEXT(""));
		
		//使用代理
		//wsprintf(buf,L"%s%s:%d%s",L"CONNECT   ",L"localhost",21,L"   HTTP/1.1   User-Agent:   MyApp/0.1   ");     
		//ClientSock.Send(buff,strlen(buff)); 
		//SetDlgItemText(IDC_EDIT_SEND,TEXT(""));


		wcscat(buf,TEXT("\r\n"));
		m_Socket.Send(buf,wcslen(buf)+1,0);
		char buf2[256];
		wcstombs(buf2,buf,256);
		m_Socket.Send(buf2,strlen(buf2)+1,0);
		int nLineCount = m_RichEditCtrl.GetLineCount();   
		m_RichEditCtrl.LineScroll(1,0);
	}
	else
	{
		TCHAR buf[2048];
		MessageBox(TEXT("尚未建立连接!"));
		wsprintf(buf,L"%s%s:%d%s",L"CONNECT   ",L"localhost",21,L"   HTTP/1.1   User-Agent:   MyApp/0.1   ");     
		//ClientSock.Send(buff,strlen(buff)); 
		SetDlgItemText(IDC_EDIT_SEND,buf);
	}
}

int CSocktServerDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}

