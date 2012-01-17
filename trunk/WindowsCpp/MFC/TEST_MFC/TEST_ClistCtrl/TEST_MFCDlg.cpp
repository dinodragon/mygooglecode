// TEST_MFCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TEST_MFC.h"
#include "TEST_MFCDlg.h"

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


// CTEST_MFCDlg �Ի���




CTEST_MFCDlg::CTEST_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTEST_MFCDlg::IDD, pParent)
	, index(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTEST_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, list);
}

BEGIN_MESSAGE_MAP(CTEST_MFCDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CTEST_MFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTEST_MFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTEST_MFCDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &CTEST_MFCDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &CTEST_MFCDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CTEST_MFCDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CTEST_MFCDlg ��Ϣ�������

BOOL CTEST_MFCDlg::OnInitDialog()
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

void CTEST_MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTEST_MFCDlg::OnPaint()
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
HCURSOR CTEST_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTEST_MFCDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	list.InsertColumn(0,TEXT("��һ��"),LVCFMT_LEFT,60);
	list.InsertColumn(4,TEXT("������"),LVCFMT_CENTER,60);
	list.InsertColumn(3,TEXT("������"),LVCFMT_CENTER,60);
	list.InsertColumn(9,TEXT("�ڶ���"),LVCFMT_CENTER,60);
	list.SetExtendedStyle(LVS_EX_GRIDLINES);
}

void CTEST_MFCDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR buf[20] = TEXT("���ݶ�");
	wsprintf(buf,L"����%d",index);
	//list.InsertItem(index++,buf,IDB_BITMAP1);
	LVITEM lvitem;
	memset(&lvitem,0,sizeof(lvitem));
	lvitem.mask = LVIF_TEXT;
	lvitem.pszText = buf;
	lvitem.iItem = index++;
	lvitem.iSubItem = 0;
	list.InsertItem(&lvitem);
}

void CTEST_MFCDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	list.SetView(LVS_REPORT);
}

void CTEST_MFCDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	list.SetView(LVS_ICON);
}

void CTEST_MFCDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	list.SetView(LVS_SMALLICON);
}

void CTEST_MFCDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	list.SetView(LVS_LIST);
}
