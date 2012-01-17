#include "stdafx.h"
#include "SelectFolder.h"



bool CSelectFolder::SelectFolder(const wchar_t * initPath,wchar_t * resultPath)
{
	LPARAM lparam = NULL;
	if (path != "")
	{
		lparam = (LPARAM)path.GetBuffer();
	}
	BROWSEINFO bi;
	TCHAR   Buffer[512]=L"";   
	TCHAR   FullPath[512]=L"";   
	bi.hwndOwner = m_hWnd; 
	bi.pidlRoot = NULL;   
	bi.pszDisplayName   =   Buffer; 
	bi.lpszTitle   =   L"Ñ¡Ôñ¼à¿ØÄ¿Â¼"; 
	bi.ulFlags   = BIF_RETURNONLYFSDIRS | BIF_VALIDATE | BIF_NEWDIALOGSTYLE |BIF_NONEWFOLDERBUTTON;
	bi.lpfn   =   BrowseCallbackProc;
	bi.lParam   =   lparam;   
	bi.iImage   =   0;   
	ITEMIDLIST* pidl = ::SHBrowseForFolder(&bi);

	return true;
}