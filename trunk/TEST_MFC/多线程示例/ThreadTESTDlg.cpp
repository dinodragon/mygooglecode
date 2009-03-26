// ���߳�ʾ��Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ThreadTEST.h"
#include "ThreadTESTDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef G_MUTEX
	#define G_MUTEX
	CMutex g_Mutex;
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


// C���߳�ʾ��Dlg �Ի���




CThreadTESTDlg::CThreadTESTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CThreadTESTDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CThreadTESTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CThreadTESTDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_START, &CThreadTESTDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_BUTTON2, &CThreadTESTDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// C���߳�ʾ��Dlg ��Ϣ�������

BOOL CThreadTESTDlg::OnInitDialog()
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

void CThreadTESTDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CThreadTESTDlg::OnPaint()
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
HCURSOR CThreadTESTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CThreadTESTDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_RICHEDIT21,TEXT(""));
}

void CThreadTESTDlg::OnBnClickedStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::CreateThread(NULL,0,Proc1,this,0,NULL);
	::CreateThread(NULL,0,Proc2,this,0,NULL);
}

DWORD WINAPI Proc1(PVOID pParam)
{
	CString temp;
	for(int i=0;i<10;i++)
	{
		g_Mutex.Lock();
		((CThreadTESTDlg *)pParam)->GetDlgItemText(IDC_RICHEDIT21,temp);
		add1(temp);
		((CThreadTESTDlg *)pParam)->SetDlgItemText(IDC_RICHEDIT21,temp);
		g_Mutex.Unlock();
	}
	return 0;
}

DWORD WINAPI Proc2(PVOID pParam)
{
	CString temp;
	for(int i=0;i<10;i++)
	{
		g_Mutex.Lock();
		((CThreadTESTDlg *)pParam)->GetDlgItemText(IDC_RICHEDIT21,temp);
		add2(temp);
		((CThreadTESTDlg *)pParam)->SetDlgItemText(IDC_RICHEDIT21,temp);
		g_Mutex.Unlock();
	}
	return 0;
}

VOID add1(CString &str)
{
	g_Mutex.Lock();
	str += TEXT("�߳�һ��\n");
	//g_Mutex.Unlock();
}

VOID add2(CString &str)
{
	str += TEXT("�ڶ����̣߳�\n");
}

