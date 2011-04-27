// DirWatchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DirWatch.h"
#include "DirWatchDlg.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDirWatchDlg 对话框


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


// CDirWatchDlg 消息处理程序

BOOL CDirWatchDlg::OnInitDialog()
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

void CDirWatchDlg::OnPaint()
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
HCURSOR CDirWatchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD WINAPI Proc1(PVOID pParam);

void CDirWatchDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
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
		((CDirWatchDlg *)pParam)->SetDlgItemText(IDC_EDIT1,L"文件夹为空！");
	}
	((CDirWatchDlg *)pParam)->SetDlgItemText(IDC_EDIT1,L"开始拷贝！");
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
			//这样做是为了处理当正在检查文件是否可访问时有新文件拷入。
			FindNextChangeNotification(dwChangeHandle);
			if (IsAllCanAccess(filePath.c_str()))
			{
				dwWaitStatus=WaitForSingleObject(dwChangeHandle,dwMilliseconds); 
				if (dwWaitStatus == WAIT_TIMEOUT)
				{
					((CDirWatchDlg *)pParam)->SetDlgItemText(IDC_EDIT1,L"文件拷贝完成");
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
		m_edit.SetWindowText(L"文件夹为空！");
	}
	m_edit.SetWindowText(L"开始拷贝！");
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
			m_edit.SetWindowText(L"文件拷贝完成");
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
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

BOOL IsAllCanAccess(LPCTSTR pFolder)//得到文件夹总大小   
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

