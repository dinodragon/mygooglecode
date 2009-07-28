// DirWatchDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DirWatch.h"
#include "DirWatchDlg.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDirWatchDlg �Ի���


BOOL isEmptyDir(const wchar_t * dirPath);

CDirWatchDlg::CDirWatchDlg(CWnd* pParent /*=NULL*/)
: CDialog(CDirWatchDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDirWatchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}

BEGIN_MESSAGE_MAP(CDirWatchDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CDirWatchDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDirWatchDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDirWatchDlg ��Ϣ�������

BOOL CDirWatchDlg::OnInitDialog()
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

void CDirWatchDlg::OnPaint()
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
HCURSOR CDirWatchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD WINAPI Proc1(PVOID pParam);

void CDirWatchDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OnOK();
	::CreateThread(NULL,0,Proc1,this,0,NULL);

}
BOOL IsAllCanAccess(LPCTSTR pFolder);
DWORD WINAPI Proc1(PVOID pParam)
{
	//WaitCopyFinish(L"F:\\aa",5000);
	DWORD dwMilliseconds = 1000;
	std::wstring filePath = L"F:\\aa";
	while (isEmptyDir(filePath.c_str()))
	{
		Sleep(100);
		((CDirWatchDlg *)pParam)->SetDlgItemText(IDC_EDIT1,L"�ļ���Ϊ�գ�");
	}
	((CDirWatchDlg *)pParam)->SetDlgItemText(IDC_EDIT1,L"��ʼ������");
	HANDLE dwChangeHandle = FindFirstChangeNotification(filePath.c_str(),TRUE,FILE_NOTIFY_CHANGE_LAST_WRITE);
	if(dwChangeHandle == INVALID_HANDLE_VALUE)
		return FALSE;
	DWORD   dwWaitStatus;  
	while (TRUE)
	{
		FindNextChangeNotification(dwChangeHandle);
		dwWaitStatus=WaitForSingleObject(dwChangeHandle,dwMilliseconds); 
		if (dwWaitStatus == WAIT_OBJECT_0)
		{
			continue;
		}
		else if (dwWaitStatus == WAIT_TIMEOUT)
		{
			//��������Ϊ�˴������ڼ���ļ��Ƿ�ɷ���ʱ�����ļ����롣
			FindNextChangeNotification(dwChangeHandle);
			if (IsAllCanAccess(filePath.c_str()))
			{
				dwWaitStatus=WaitForSingleObject(dwChangeHandle,dwMilliseconds); 
				if (dwWaitStatus == WAIT_TIMEOUT)
				{
					((CDirWatchDlg *)pParam)->SetDlgItemText(IDC_EDIT1,L"�ļ��������");
					FindCloseChangeNotification(dwChangeHandle);  
					break;
				}
			}
		}
	}
	return TRUE;
}

int CDirWatchDlg::WaitCopyFinish(const wchar_t * filePath,const DWORD dwMilliseconds)
{
	while (isEmptyDir(filePath))
	{
		Sleep(100);
		m_edit.SetWindowText(L"�ļ���Ϊ�գ�");
	}
	m_edit.SetWindowText(L"��ʼ������");
	HANDLE dwChangeHandle = FindFirstChangeNotification(filePath,TRUE,FILE_NOTIFY_CHANGE_LAST_ACCESS);
	if(dwChangeHandle == INVALID_HANDLE_VALUE)
		return FALSE;
	DWORD   dwWaitStatus;  
	while (TRUE)
	{
		FindNextChangeNotification(dwChangeHandle);
		dwWaitStatus=WaitForSingleObject(dwChangeHandle,dwMilliseconds); 
		if (dwWaitStatus == WAIT_OBJECT_0)
		{
			continue;
		}
		else if (dwWaitStatus == WAIT_TIMEOUT)
		{
			m_edit.SetWindowText(L"�ļ��������");
			FindCloseChangeNotification(dwChangeHandle);  
			break;
		}
	}
	return TRUE;
}

BOOL isEmptyDir(const wchar_t * dirPath)
{
	BOOL bIsEmpty = TRUE;   
	CFileFind finder;
	std::wstring file;
	file += dirPath;
	file += L"\\*.*";
	BOOL bFind = finder.FindFile(file.c_str());   
	while(bFind)   
	{   
		bFind = finder.FindNextFile();   
		if(!finder.IsDots())   
		{   
			bIsEmpty = FALSE;   
			break;   
		}   
	}
	return bIsEmpty;
}

void CDirWatchDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

BOOL IsAllCanAccess(LPCTSTR pFolder)//�õ��ļ����ܴ�С   
{   
	TCHAR   szFullPathFileName[MAX_PATH];   
	TCHAR   szFilename[MAX_PATH];   
	WIN32_FIND_DATA   FileData   =   {0};   
	BOOL   bFinished   =   FALSE;     
	DWORD   dwSize   =   0;   
	CFile file;

	swprintf_s(szFullPathFileName, TEXT("%s\\*.*"), pFolder);   
	HANDLE hSearch = FindFirstFile(szFullPathFileName,&FileData);     
	if(hSearch == INVALID_HANDLE_VALUE)     
		return FALSE;   
	while(!bFinished)   
	{   
		swprintf_s(szFilename, TEXT("%s\\%s"),pFolder,FileData.cFileName);   
		if(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)   
		{   
			if(_tcscmp(FileData.cFileName,TEXT(".")) && _tcscmp(FileData.cFileName,TEXT("..")))   
			{
				if(!IsAllCanAccess(szFilename))
				{
					return FALSE;
				}
			}
		}   
		else
		{
			if(file.Open(szFilename, CFile::modeRead))
			{
				file.Close();
			}
			else
			{
				FindClose(hSearch);
				return FALSE;
			}
		}
		if(!FindNextFile(hSearch, &FileData))     
		{   
			if(GetLastError() == ERROR_NO_MORE_FILES)     
				bFinished   =   TRUE;   
		}     
	}
	FindClose(hSearch);   
	return TRUE;   
}   

