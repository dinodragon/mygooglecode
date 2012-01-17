// SelFolderDll.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "SelFolderDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//


// CSelFolderDllApp

BEGIN_MESSAGE_MAP(CSelFolderDllApp, CWinApp)
END_MESSAGE_MAP()


// CSelFolderDllApp 构造

CSelFolderDllApp::CSelFolderDllApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CSelFolderDllApp 对象

CSelFolderDllApp theApp;


// CSelFolderDllApp 初始化

BOOL CSelFolderDllApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData) 
{ 
	static HWND hWndEdit = NULL;
	switch(uMsg)
	{ 
	case BFFM_INITIALIZED:
		{
			::SendMessage(hwnd,BFFM_SETSELECTION,TRUE,lpData); 
		}
		break; 
	}
	return 0; 
} 

extern "C" BOOL PASCAL EXPORT SelectFolder(const wchar_t * initPath,wchar_t * resultPath)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	LPARAM lparam = NULL;
	lparam = (LPARAM)initPath;
	BROWSEINFO bi;
	TCHAR   Buffer[512]=L"";   
	TCHAR   FullPath[512]=L"";
	bi.hwndOwner = NULL; 
	bi.pidlRoot = NULL;   
	bi.pszDisplayName   =   Buffer; 
	bi.lpszTitle   =   L"选择监控目录"; 
	bi.ulFlags   = BIF_RETURNONLYFSDIRS | BIF_VALIDATE | BIF_NEWDIALOGSTYLE |BIF_NONEWFOLDERBUTTON;
	bi.lpfn   =   BrowseCallbackProc;
	bi.lParam   =   lparam;   
	bi.iImage   =   0;   
	ITEMIDLIST* pidl = ::SHBrowseForFolder(&bi);
	if(::SHGetPathFromIDList(pidl,resultPath))
	{   
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}
