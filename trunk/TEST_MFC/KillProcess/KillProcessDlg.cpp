// KillProcessDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KillProcess.h"
#include "KillProcessDlg.h"

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


// CKillProcessDlg �Ի���




CKillProcessDlg::CKillProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKillProcessDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKillProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKillProcessDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CKillProcessDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CKillProcessDlg ��Ϣ�������

BOOL CKillProcessDlg::OnInitDialog()
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

void CKillProcessDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CKillProcessDlg::OnPaint()
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
HCURSOR CKillProcessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CKillProcessDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DWORD dwCount;
	DWORD * m_pids;
	DWORD nalloc = 1024;
	m_pids = new DWORD[nalloc];
	if (EnumProcesses(m_pids, nalloc*sizeof(DWORD), &dwCount))
	{
		dwCount /= sizeof(DWORD);
	}
	for (DWORD i=1;i < dwCount;i++)
	{
		if (IsProcessContainModName(m_pids[i],TEXT("WinWord.exe")))
		{
			CloseProcess(m_pids[i]);
		}		
	}
	delete[] m_pids;
	OnOK();
}

BOOL CKillProcessDlg::CloseProcess(DWORD dwProcessId,BOOL bForce)
{
	HANDLE hp = OpenProcess(SYNCHRONIZE|PROCESS_TERMINATE,FALSE,dwProcessId);
	TerminateProcess(hp,0);
	return FALSE;
}

BOOL CKillProcessDlg::IsProcessContainModName(DWORD dwProcessId,LPCTSTR szModeName)
{
	CString NeedKillModName(szModeName);
	HMODULE * hModules = NULL;
	DWORD m_dwModCount = 0;
	DWORD nalloc = 1024;
	BOOL result = FALSE;
	TCHAR modName[_MAX_PATH];
	HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE,dwProcessId);
	if (handle) 
	{
		hModules = new HMODULE[nalloc];
		if (EnumProcessModules(handle, hModules,nalloc*sizeof(HMODULE), &m_dwModCount)) 
		{
			m_dwModCount /= sizeof(HMODULE);
		}
		for (DWORD j = 0 ;j<m_dwModCount ;j++)
		{
			GetModuleBaseName(handle,hModules[j],modName,_MAX_PATH);
			if (NeedKillModName.CompareNoCase(modName)==0)
			{
				result = TRUE;
				break;
			}
		}
		delete[] hModules;
	}
	CloseHandle(handle);
	return result;
}