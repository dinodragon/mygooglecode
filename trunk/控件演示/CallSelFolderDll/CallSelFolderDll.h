// CallSelFolderDll.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCallSelFolderDllApp:
// �йش����ʵ�֣������ CallSelFolderDll.cpp
//

class CCallSelFolderDllApp : public CWinApp
{
public:
	CCallSelFolderDllApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCallSelFolderDllApp theApp;