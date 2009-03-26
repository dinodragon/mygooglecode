// TEST_MyLoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TEST_MyLogin.h"
#include "TEST_MyLoginDlg.h"
#include "upsock.h"
#include "updateAHost.h"

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


// CTEST_MyLoginDlg 对话框




CTEST_MyLoginDlg::CTEST_MyLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTEST_MyLoginDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTEST_MyLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTEST_MyLoginDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CTEST_MyLoginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_SEND, &CTEST_MyLoginDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_UP, &CTEST_MyLoginDlg::OnBnClickedUp)
	ON_BN_CLICKED(IDC_QUIT, &CTEST_MyLoginDlg::OnBnClickedQuit)
END_MESSAGE_MAP()


// CTEST_MyLoginDlg 消息处理程序

BOOL CTEST_MyLoginDlg::OnInitDialog()
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

	//初使化被动模式复选框
	CButton *checkbox = (CButton *)GetDlgItem(IDC_PASV);
	checkbox->SetCheck(TRUE);
	//初使化断点续传复选框
	checkbox = (CButton *)GetDlgItem(IDC_RESUME);
	checkbox->SetCheck(TRUE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTEST_MyLoginDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTEST_MyLoginDlg::OnPaint()
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
HCURSOR CTEST_MyLoginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTEST_MyLoginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//CUpdateAHost uphost;
	CString sProxyHost,server,user,pass;
	UINT uProxyPort,port;
	BOOL bProxyEnable;

	CButton *checkbox = (CButton *)GetDlgItem(IDC_PROXY);
	bProxyEnable = checkbox->GetCheck();
	GetDlgItemText(IDC_PROXYIP,sProxyHost);
	uProxyPort = GetDlgItemInt(IDC_PROXYPORT);

	port = GetDlgItemInt(IDC_PORT);
	GetDlgItemText(IDC_SERVER,server);
	GetDlgItemText(IDC_USER,user);
	GetDlgItemText(IDC_PASS,pass);

	if(server == "") 
	{
		MessageBox(TEXT("没有填写服务器地址完整！"));
		return;
	}

	if(bProxyEnable)
	{
		user = user + "@" + sProxyHost;
		uphost.SetProxy(sProxyHost,uProxyPort);
		if( 0 == uphost.ConnectFTPControlSocket(sProxyHost,uProxyPort,0))
			uphost.FTPLogIn(user,pass);
	}
	else
	{
		if( 0 == uphost.ConnectFTPControlSocket(server,port,0))
			uphost.FTPLogIn(user.GetBuffer(),pass.GetBuffer());
	}
}

void CTEST_MyLoginDlg::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CString cmd;
	GetDlgItemText(IDC_CMD,cmd);

	cmd += "\r\n";
	uphost.SendFTPCmd(cmd.GetBuffer());
	
}

void CTEST_MyLoginDlg::OnBnClickedUp()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filename;
	GetDlgItemText(IDC_FILENAME,filename);

	//识别主被动模式
	CButton *checkbox = (CButton *)GetDlgItem(IDC_PASV);
	uphost.bPasv = checkbox->GetCheck();
	//设置是否使用断点续传
	checkbox = (CButton *)GetDlgItem(IDC_RESUME);
	uphost.bResume = checkbox->GetCheck();

	if(!filename.IsEmpty())
		uphost.UpdateAFileNow(filename.GetBuffer(),filename.GetBuffer(),5,"aa",NULL);
		//uphost.UpdateAFileNow(_T("c:\\1\\2\\2.txt"),_T("2.txt"),5,"aa",NULL);
	//参数说明
	//LPSTR filename,带路径文件名
	//char * fname,文件名
	//DWORD nFileLength,文件大小
	//CString ltime,当弹出确认是否要进行断点续传对话框时,确定当前文件日期 暂时不用.
	//LPSTR szRealName,//上传后对文件重命名
}

void CTEST_MyLoginDlg::OnBnClickedQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	//uphost.~CUpdateAHost();
	uphost.DeleteCommandSocket();
	uphost.DeleteListenSocket();
	uphost.DeleteDataSocket();
}
