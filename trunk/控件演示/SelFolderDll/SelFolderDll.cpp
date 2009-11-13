// SelFolderDll.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "SelFolderDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//


// CSelFolderDllApp

BEGIN_MESSAGE_MAP(CSelFolderDllApp, CWinApp)
END_MESSAGE_MAP()


// CSelFolderDllApp ����

CSelFolderDllApp::CSelFolderDllApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CSelFolderDllApp ����

CSelFolderDllApp theApp;


// CSelFolderDllApp ��ʼ��

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
	bi.lpszTitle   =   L"ѡ����Ŀ¼"; 
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
