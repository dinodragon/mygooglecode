//this file is part of eMule
//Copyright (C)2004 Merkur ( merkur-@users.sourceforge.net / http://www.emule-project.net )
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "stdafx.h"
#include "LinkCreator.h"
#include "LinkCreatorDlg.h"
#include "functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLinkCreatorApp

BEGIN_MESSAGE_MAP(CLinkCreatorApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CLinkCreatorApp-Erstellung

CLinkCreatorApp::CLinkCreatorApp()
{
	bCancelHashing = false;
	m_lid = 0;
}


CLinkCreatorApp theApp;


BOOL CLinkCreatorApp::InitInstance()
{
	InitCommonControls();

	CWinApp::InitInstance();

	bool bHashFile = false;
	CString strFileToHash,strArgs;

	for (int i=1; i<__argc; i++)
	{
		LPCTSTR pszParam = __targv[i];
		if (pszParam[0] == _T('-') || pszParam[0] == _T('/'))
			pszParam++;
		if (!stricmp(pszParam,_T("lang")))
		{
			i++;
			ASSERT( i<__argc );
			LPCTSTR pszLangID = __targv[i];
			SetLang( (LANGID)atoi(pszLangID) );
		}
		if (!stricmp(pszParam,_T("hashfile")))
		{
			i++;
			ASSERT( i<__argc );
			strFileToHash = __targv[i];
			strFileToHash.Trim(_T('\"'));
			int pos = strFileToHash.ReverseFind(_T('\\'));
			if (pos<0)
				pos = strFileToHash.ReverseFind(_T('/'));
			bHashFile = (pos>=0 && strFileToHash.Mid(pos+1)!=_T("") && PathFileExists(strFileToHash));
		}
	}

	CLinkCreatorDlg dlg;
	m_pMainWnd = &dlg;
	m_pLinkCreatorDlg = &dlg;
	if (bHashFile && strFileToHash.GetLength())
		dlg.SetFilePath(strFileToHash);
	INT_PTR nResponse = dlg.DoModal();

	m_pLinkCreatorDlg = NULL;

	return FALSE;
}

void CLinkCreatorApp::SetLang(LANGID lid)
{
	if (IsLangSupported(lid))
		m_lid = lid;
	else
		m_lid = MAKELANGID(LANG_ENGLISH,SUBLANG_DEFAULT);
	SetThreadLocale(m_lid);
}

