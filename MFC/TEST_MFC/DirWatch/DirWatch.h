// DirWatch.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDirWatchApp:
// �йش����ʵ�֣������ DirWatch.cpp
//

class CDirWatchApp : public CWinApp
{
public:
	CDirWatchApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDirWatchApp theApp;