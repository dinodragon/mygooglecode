// flipTest.h : flipTest Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CflipTestApp:
// �йش����ʵ�֣������ flipTest.cpp
//

class CflipTestApp : public CWinApp
{
public:
	CflipTestApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CflipTestApp theApp;