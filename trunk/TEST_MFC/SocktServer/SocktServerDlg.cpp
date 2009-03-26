// SocktServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SocktServer.h"
#include "SocktServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CSocktServerDlg �Ի���




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


// CSocktServerDlg ��Ϣ�������

BOOL CSocktServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSocktServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CSocktServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSocktServerDlg::OnBnClickedCreatserver()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UINT err = 0;;

	if(UpdateData()==false || m_Socket.m_hSocket !=INVALID_SOCKET) return;
	
	BOOL bFlag=m_Socket.Create(m_port,SOCK_STREAM); 
	if(!bFlag)
	{
		TCHAR buf[256];
		err = m_Socket.GetLastError();
		wsprintf(buf,TEXT("Socket ����! �����룺%d\r\n"),err);
		MessageBox(buf);
		return;
	}
	else
	{
		m_Socket.Listen(1);
		TCHAR buf[256];
		err = m_Socket.GetLastError();
		wsprintf(buf,TEXT("Socket��ʼ���������ڶ˿ڣ�%d ����,Return Code %d\n"),m_port,err);
		m_RichText += buf;
		UpdateData(FALSE);
	}
	UpdateData(false);
}

void CSocktServerDlg::OnBnClickedStoplisten()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Socket.Close();
	CString temp;
	GetDlgItemText(IDC_RICHEDIT21,temp);
	temp += TEXT("ֹͣ����\n");
	SetDlgItemText(IDC_RICHEDIT21,temp);
}


void CSocktServerDlg::OnBnClickedConnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR buf[2048];
	int err = 0;
	GetDlgItemText(IDC_SERVERIP,m_serverIP);
	if(UpdateData()==false || m_Socket.m_hSocket !=INVALID_SOCKET) return;

	BOOL bFlag=m_Socket.Create(0,SOCK_STREAM,FD_CONNECT);
	if(!bFlag)
	{
		TCHAR buf[256];
		err = m_Socket.GetLastError();
		wsprintf(buf,TEXT("Socket ����! �����룺%d"),err);
		MessageBox(buf);
		return;
	}
	//���Ӵ���
	bFlag=m_Socket.Connect(m_serverIP,m_ServerPort);
	//bFlag=m_Socket.Connect(TEXT("192.168.75.1"),808);
	
	err = m_Socket.GetLastError();
	if(bFlag && err!=10035)
	{
		TCHAR buf[256];
		wsprintf(buf,TEXT("����ʧ��! Error Code %d"),err);
		MessageBox(buf);
		return;
	}
}

void CSocktServerDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_RichText += TEXT("�µ�һ��\r\n");
	UpdateData(false);
	//OnOK();
}

void CSocktServerDlg::OnBnClickedButtonSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_Socket.m_bConnected == TRUE)
	{
		TCHAR buf[256];
		GetDlgItemText(IDC_EDIT_SEND,buf,256);
		SetDlgItemText(IDC_EDIT_SEND,TEXT(""));
		
		//ʹ�ô���
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
		MessageBox(TEXT("��δ��������!"));
		wsprintf(buf,L"%s%s:%d%s",L"CONNECT   ",L"localhost",21,L"   HTTP/1.1   User-Agent:   MyApp/0.1   ");     
		//ClientSock.Send(buff,strlen(buff)); 
		SetDlgItemText(IDC_EDIT_SEND,buf);
	}
}

int CSocktServerDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}

