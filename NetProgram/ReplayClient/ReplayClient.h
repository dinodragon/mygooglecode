// ReplayClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CReplayClientApp:
// �йش����ʵ�֣������ ReplayClient.cpp
//

class CReplayClientApp : public CWinApp
{
public:
	CReplayClientApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CReplayClientApp theApp;