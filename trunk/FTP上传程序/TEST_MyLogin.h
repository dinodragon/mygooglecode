// TEST_MyLogin.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTEST_MyLoginApp:
// �йش����ʵ�֣������ TEST_MyLogin.cpp
//

class CTEST_MyLoginApp : public CWinApp
{
public:
	CTEST_MyLoginApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTEST_MyLoginApp theApp;