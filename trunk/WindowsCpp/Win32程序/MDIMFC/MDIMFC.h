// MDIMFC.h : MDIMFC Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMDIMFCApp:
// �йش����ʵ�֣������ MDIMFC.cpp
//

class CMDIMFCApp : public CWinApp
{
public:
	CMDIMFCApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMDIMFCApp theApp;