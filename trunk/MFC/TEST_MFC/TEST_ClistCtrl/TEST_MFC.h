// TEST_MFC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTEST_MFCApp:
// �йش����ʵ�֣������ TEST_MFC.cpp
//

class CTEST_MFCApp : public CWinApp
{
public:
	CTEST_MFCApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTEST_MFCApp theApp;