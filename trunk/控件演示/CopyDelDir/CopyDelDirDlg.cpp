// CopyDelDirDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CopyDelDir.h"
#include "CopyDelDirDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCopyDelDirDlg �Ի���




CCopyDelDirDlg::CCopyDelDirDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCopyDelDirDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCopyDelDirDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCopyDelDirDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CCopyDelDirDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CCopyDelDirDlg ��Ϣ�������

BOOL CCopyDelDirDlg::OnInitDialog()
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

void CCopyDelDirDlg::OnPaint()
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
HCURSOR CCopyDelDirDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCopyDelDirDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}



BOOL CopyDirectory(LPCTSTR strSrcPath, LPCTSTR strDestPath)   
{   
	HANDLE HResult;   
	WIN32_FIND_DATA FindFileData;
	TCHAR strSrcFileName[MAX_PATH],strDestFileName[MAX_PATH];   
	BOOL blResult;   
	HResult = FindFirstFile(strSrcPath,&FindFileData);   

	if(HResult == INVALID_HANDLE_VALUE)   
	{   
		return FALSE   ;   
	}   

	_tcscpy_s(strSrcFileName,strSrcPath);
	_tcscpy_s(strDestFileName,strDestPath);

	if(strSrcFileName[_tcslen(strSrcPath) - 1] == '\\')   
		strSrcFileName[_tcslen(strSrcPath) - 1] =   '\0';   

	if(strDestFileName[_tcslen(strDestPath) - 1]   ==   '\\')   
		strDestFileName[_tcslen(strDestPath) - 1]   =   '\0';   

	HResult   =     FindFirstFile(strDestPath,   &FindFileData);   

	if(HResult   ==   INVALID_HANDLE_VALUE)   
	{   
		CreateDirectory(strDestPath   ,NULL);   
	}   

	_tcscat_s(strSrcFileName,_T("\\*"));   
	HResult = FindFirstFile(strSrcFileName,&FindFileData);   
	if(HResult   ==   INVALID_HANDLE_VALUE)   
	{   
		return   FALSE;   
	}   
	if(_tcscmp(FindFileData.cFileName,_T(".")) &&   _tcscmp(FindFileData.cFileName   ,_T(".."))   )   
	{   
		_tcscpy_s(strSrcFileName,strSrcPath);   
		_tcscat_s(strSrcFileName,_T("\\"));   
		_tcscat_s(strSrcFileName,FindFileData.cFileName);   
		_tcscpy_s(strDestFileName,strDestPath);   
		_tcscat_s(strDestFileName,_T("\\"));   
		_tcscat_s(strDestFileName,FindFileData.cFileName);   

		if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)   
		{   
			CopyDirectory(strSrcFileName,strDestFileName);   
		}   
		else   
		{   
			CopyFile(strSrcFileName,strDestFileName,FALSE);   
		}   
	}   
	while(1)   
	{   
		blResult   =   FindNextFile(HResult,&FindFileData);   
		if(!blResult)   
			break;   
		if(_tcscmp(FindFileData.cFileName   ,   _T("."))     &&   _tcscmp(FindFileData.cFileName   ,_T(".."))   )   
		{   
			_tcscpy_s(strSrcFileName,strSrcPath);   
			_tcscat_s(strSrcFileName,_T("\\"));
			_tcscat_s(strSrcFileName,FindFileData.cFileName);   
			_tcscpy_s(strDestFileName,strDestPath);   
			_tcscat_s(strDestFileName,_T("\\"));   
			_tcscat_s(strDestFileName,FindFileData.cFileName);   

			if((FindFileData.dwFileAttributes   &   FILE_ATTRIBUTE_DIRECTORY)   ==   FILE_ATTRIBUTE_DIRECTORY)   
			{   
				CopyDirectory(strSrcFileName,strDestFileName);   
			}   
			else   
			{   
				CopyFile(strSrcFileName,strDestFileName,FALSE);   
			}   
		}   
	}   
	return   TRUE;    
}

BOOL DeleteDirectory(LPCTSTR sDirName) 
{ 
	CFileFind tempFind; 
	TCHAR sTempFileFind[MAX_PATH] ;

	swprintf_s(sTempFileFind, TEXT("%s\\*.*"), sDirName);  
	BOOL IsFinded = tempFind.FindFile(sTempFileFind); 
	while (IsFinded) 
	{ 
		IsFinded = tempFind.FindNextFile(); 

		if (!tempFind.IsDots()) 
		{ 
			TCHAR sFoundFileName[MAX_PATH]; 
			lstrcpy(sFoundFileName,tempFind.GetFileName().GetBuffer(MAX_PATH)); 

			if (tempFind.IsDirectory()) 
			{ 
				TCHAR sTempDir[MAX_PATH]; 
				swprintf_s(sTempDir,L"%s\\%s",sDirName,sFoundFileName); 
				DeleteDirectory(sTempDir); 
			} 
			else 
			{ 
				TCHAR sTempFileName[MAX_PATH]; 
				swprintf_s(sTempFileName,L"%s\\%s",sDirName,sFoundFileName); 
				DeleteFile(sTempFileName); 
			} 
		} 
	} 
	tempFind.Close(); 
	if(!RemoveDirectory(sDirName)) 
	{ 
		return FALSE; 
	} 
	return TRUE; 
} 