// SelectFolder.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSelectFolderApp:
// �йش����ʵ�֣������ SelectFolder.cpp
//

class CSelectFolderApp : public CWinApp
{
public:
	CSelectFolderApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSelectFolderApp theApp;