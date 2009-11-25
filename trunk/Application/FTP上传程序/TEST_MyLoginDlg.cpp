// TEST_MyLoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TEST_MyLogin.h"
#include "TEST_MyLoginDlg.h"
#include "upsock.h"
#include "updateAHost.h"

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


// CTEST_MyLoginDlg �Ի���




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


// CTEST_MyLoginDlg ��Ϣ�������

BOOL CTEST_MyLoginDlg::OnInitDialog()
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

	//��ʹ������ģʽ��ѡ��
	CButton *checkbox = (CButton *)GetDlgItem(IDC_PASV);
	checkbox->SetCheck(TRUE);
	//��ʹ���ϵ�������ѡ��
	checkbox = (CButton *)GetDlgItem(IDC_RESUME);
	checkbox->SetCheck(TRUE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTEST_MyLoginDlg::OnPaint()
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
HCURSOR CTEST_MyLoginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTEST_MyLoginDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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
		MessageBox(TEXT("û����д��������ַ������"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString cmd;
	GetDlgItemText(IDC_CMD,cmd);

	cmd += "\r\n";
	uphost.SendFTPCmd(cmd.GetBuffer());
	
}

void CTEST_MyLoginDlg::OnBnClickedUp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString filename;
	GetDlgItemText(IDC_FILENAME,filename);

	//ʶ��������ģʽ
	CButton *checkbox = (CButton *)GetDlgItem(IDC_PASV);
	uphost.bPasv = checkbox->GetCheck();
	//�����Ƿ�ʹ�öϵ�����
	checkbox = (CButton *)GetDlgItem(IDC_RESUME);
	uphost.bResume = checkbox->GetCheck();

	if(!filename.IsEmpty())
		uphost.UpdateAFileNow(filename.GetBuffer(),filename.GetBuffer(),5,"aa",NULL);
		//uphost.UpdateAFileNow(_T("c:\\1\\2\\2.txt"),_T("2.txt"),5,"aa",NULL);
	//����˵��
	//LPSTR filename,��·���ļ���
	//char * fname,�ļ���
	//DWORD nFileLength,�ļ���С
	//CString ltime,������ȷ���Ƿ�Ҫ���жϵ������Ի���ʱ,ȷ����ǰ�ļ����� ��ʱ����.
	//LPSTR szRealName,//�ϴ�����ļ�������
}

void CTEST_MyLoginDlg::OnBnClickedQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//uphost.~CUpdateAHost();
	uphost.DeleteCommandSocket();
	uphost.DeleteListenSocket();
	uphost.DeleteDataSocket();
}
