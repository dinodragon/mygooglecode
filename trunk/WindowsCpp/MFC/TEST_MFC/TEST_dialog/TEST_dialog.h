// TEST_dialog.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTEST_dialogApp:
// �йش����ʵ�֣������ TEST_dialog.cpp
//

class CTEST_dialogApp : public CWinApp
{
public:
	CTEST_dialogApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTEST_dialogApp theApp;

