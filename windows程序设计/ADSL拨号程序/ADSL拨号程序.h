// ADSL���ų���.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CadslApp:
// �йش����ʵ�֣������ ADSL���ų���.cpp
//

class CadslApp : public CWinApp
{
public:
	CadslApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CadslApp theApp;