// TEST_dialogDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TEST_dialog.h"
#include "TEST_dialogDlg.h"

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


// CTEST_dialogDlg �Ի���




CTEST_dialogDlg::CTEST_dialogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTEST_dialogDlg::IDD, pParent)
	, value(0)
	, boolv(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTEST_dialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Value, value);
	DDV_MinMaxInt(pDX, value, 0, 100);
	DDX_Control(pDX, IDC_LIST1, list);
	DDX_Control(pDX, IDC_TREE1, tree);
	DDX_Check(pDX, IDC_CHECK1, boolv);
	DDX_Control(pDX, IDC_CHECK1, ccheck);
}

BEGIN_MESSAGE_MAP(CTEST_dialogDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDYES, &CTEST_dialogDlg::OnBnClickedYes)
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &CTEST_dialogDlg::OnNMClickTree1)
	ON_BN_CLICKED(IDC_BUTTON1, &CTEST_dialogDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTEST_dialogDlg ��Ϣ�������

BOOL CTEST_dialogDlg::OnInitDialog()
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

	ShowWindow(SW_SHOWDEFAULT);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTEST_dialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTEST_dialogDlg::OnPaint()
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
HCURSOR CTEST_dialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTEST_dialogDlg::OnBnClickedYes()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	list.InsertColumn(1, TEXT("�ļ��� "),LVCFMT_CENTER,140); 
	list.InsertColumn(2, TEXT("��С "),LVCFMT_CENTER,80); 
	list.InsertColumn(3, TEXT("���� "),LVCFMT_CENTER,80); 
	list.InsertColumn(4, TEXT("�޸�ʱ�� "),LVCFMT_CENTER,130); 
	list.ModifyStyle(NULL,LVS_REPORT);
	int   nitem; 
	nitem=list.InsertItem(1, L"aaa "); 
	list.SetItemText(nitem,1, L"cc "); 
	list.SetItemText(nitem,2, L"cc "); 
	list.SetItemText(nitem,3, L"cc "); 
	list.SetItemText(nitem,4, L"cc "); 

	tree.InsertItem(TEXT("aa"));
	UpdateData(false);

}

void CTEST_dialogDlg::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

void CTEST_dialogDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//::CreateThread(NULL,0,Proc1,this,0,NULL);
	//::CreateThread(NULL,0,Proc2,this,0,NULL);
	g_Mutex.Lock();
	g_Mutex.Lock();
	g_Mutex.Lock();
	g_Mutex.Lock();
	g_Mutex.Unlock();
	g_Mutex.Unlock();
	g_Mutex.Unlock();
	g_Mutex.Unlock();
}




DWORD WINAPI Proc1(PVOID pParam)
{
	CString temp;
	for(int i=0;i<10;i++)
	{
		g_Mutex.Lock();
		((CTEST_dialogDlg *)pParam)->GetDlgItemText(IDC_RICHEDIT21,temp);
		temp += TEXT("�߳�һ��\n");
		((CTEST_dialogDlg *)pParam)->SetDlgItemText(IDC_RICHEDIT21,temp);
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
		((CTEST_dialogDlg *)pParam)->GetDlgItemText(IDC_RICHEDIT21,temp);
		temp += TEXT("�̶߳���\n");
		((CTEST_dialogDlg *)pParam)->SetDlgItemText(IDC_RICHEDIT21,temp);
		g_Mutex.Unlock();
	}
	return 0;
}
