// KillProcess.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CKillProcessApp:
// �йش����ʵ�֣������ KillProcess.cpp
//

class CKillProcessApp : public CWinApp
{
public:
	CKillProcessApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CKillProcessApp theApp;