// SdtMfcApp.h : SdtMfcApp Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CSdtMfcAppApp:
// �йش����ʵ�֣������ SdtMfcApp.cpp
//

class CSdtMfcAppApp : public CWinApp
{
public:
	CSdtMfcAppApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSdtMfcAppApp theApp;