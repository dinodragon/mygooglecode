// CopyDelDir.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCopyDelDirApp:
// �йش����ʵ�֣������ CopyDelDir.cpp
//

class CCopyDelDirApp : public CWinApp
{
public:
	CCopyDelDirApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCopyDelDirApp theApp;