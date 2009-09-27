// SelectFolderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SelectFolder.h"
#include "SelectFolderDlg.h"
#include "folder_dialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSelectFolderDlg �Ի���

CSelectFolderDlg::CSelectFolderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectFolderDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSelectFolderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSelectFolderDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CSelectFolderDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSelectFolderDlg ��Ϣ�������

BOOL CSelectFolderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSelectFolderDlg::OnPaint()
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
HCURSOR CSelectFolderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData) 
{ 
	static HWND hWndEdit = NULL;
	switch(uMsg)
	{ 
	case BFFM_INITIALIZED:
		{
			HWND hChildWindow;
			hChildWindow = GetWindow(hwnd, GW_CHILD);
			while(hChildWindow)
			{
				TCHAR szClass[MAX_PATH];
				GetClassName(hChildWindow, szClass, MAX_PATH);
				if(0 == wcscmp(szClass, L"Edit"))
				{
					hWndEdit = hChildWindow;
					break;
				}
				hChildWindow = GetNextWindow(hChildWindow, GW_HWNDNEXT);
			}
			::SendMessage(hwnd,BFFM_SETSELECTION,TRUE,lpData); 
		}
		break;
	case BFFM_VALIDATEFAILED:
		{
			MessageBoxW(hwnd, _T("·�����Ϸ������������룡"), _T("�Զ����"), MB_ICONWARNING|MB_OK);
			return 1;
		}
		break;
	case BFFM_SELCHANGED:
		{
			TCHAR buf[MAX_PATH];
			if (::SHGetPathFromIDList((LPITEMIDLIST) lParam ,buf)) 
			{
				if(hWndEdit != NULL)
					SetWindowText(hWndEdit, buf);
			}
			else
				::SendMessage(hwnd, BFFM_ENABLEOK, 0, 0);
		}
		break;
	}
	return 0; 
} 

void CSelectFolderDlg::OnBnClickedOk()
{
	CoInitialize(NULL);
	BROWSEINFO bi;
	TCHAR   Buffer[512]=L"";   
	TCHAR   FullPath[512]=L"";   
	bi.hwndOwner = m_hWnd; 
	bi.pidlRoot = NULL;   
	bi.pszDisplayName   =   Buffer; 
	bi.lpszTitle   =   L"ѡ����Ŀ¼"; 
	bi.ulFlags   =  BIF_EDITBOX|BIF_VALIDATE | BIF_NEWDIALOGSTYLE|BIF_NONEWFOLDERBUTTON  ;
	bi.lpfn   =   BrowseCallbackProc;
	TCHAR initPath[] = L"";
	bi.lParam   =  (LPARAM)initPath;   
	bi.iImage   =   0;   
	ITEMIDLIST* pidl = ::SHBrowseForFolder(&bi);
	if(::SHGetPathFromIDList(pidl,FullPath))
	{   
		AfxMessageBox(FullPath);
	}   
	CoUninitialize();
	//OnOK();
}

