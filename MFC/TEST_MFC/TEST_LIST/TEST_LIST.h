// TEST_LIST.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTEST_LISTApp:
// �йش����ʵ�֣������ TEST_LIST.cpp
//

class CTEST_LISTApp : public CWinApp
{
public:
	CTEST_LISTApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTEST_LISTApp theApp;