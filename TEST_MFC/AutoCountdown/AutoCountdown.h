// AutoCountdown.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAutoCountdownApp:
// �йش����ʵ�֣������ AutoCountdown.cpp
//

class CAutoCountdownApp : public CWinApp
{
public:
	CAutoCountdownApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAutoCountdownApp theApp;