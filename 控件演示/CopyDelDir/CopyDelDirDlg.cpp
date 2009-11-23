// CopyDelDirDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CopyDelDir.h"
#include "CopyDelDirDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCopyDelDirDlg 对话框




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


// CCopyDelDirDlg 消息处理程序

BOOL CCopyDelDirDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCopyDelDirDlg::OnPaint()
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
HCURSOR CCopyDelDirDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCopyDelDirDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
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