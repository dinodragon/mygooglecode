// ReplayServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CReplayServerApp:
// �йش����ʵ�֣������ ReplayServer.cpp
//

class CReplayServerApp : public CWinApp
{
public:
	CReplayServerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CReplayServerApp theApp;