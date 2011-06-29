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

#pragma once
#include <afxmt.h>

#define	MAX_EMULE_FILE_SIZE		0x4000000000ui64 // = 2^38 = 256GB


#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

class CLinkCreatorDlg;

class CLinkCreatorApp : public CWinApp
{
public:
	CLinkCreatorApp();

	virtual BOOL InitInstance();
	CLinkCreatorDlg* m_pLinkCreatorDlg;

	CMutex			hashing_mut;
	volatile bool	bCancelHashing;
	volatile bool	bFolderJob;
	CStringArray	m_saHashList;

	void SetLang(LANGID lid);
	LANGID GetLang() { return m_lid; }
	const CString GetVersion() { return CString(_T("0.7")); }

protected:
	DECLARE_MESSAGE_MAP()

	LANGID m_lid;
};

extern CLinkCreatorApp theApp;
