// notepad.h : notepad Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CnotepadApp:
// �йش����ʵ�֣������ notepad.cpp
//

class CnotepadApp : public CWinApp
{
public:
	CnotepadApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CnotepadApp theApp;