// FtpDownLoader.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFtpDownLoaderApp:
// �йش����ʵ�֣������ FtpDownLoader.cpp
//

class CFtpDownLoaderApp : public CWinApp
{
public:
	CFtpDownLoaderApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFtpDownLoaderApp theApp;