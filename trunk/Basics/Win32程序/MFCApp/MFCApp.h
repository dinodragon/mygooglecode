// MFCApp.h : MFCApp Ӧ�ó������ͷ�ļ�
//
#pragma once
#include "stdafx.h"
#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMFCAppApp:
// �йش����ʵ�֣������ MFCApp.cpp
//

class CMFCAppApp : public CWinApp
{
public:
	CMFCAppApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCAppApp theApp;