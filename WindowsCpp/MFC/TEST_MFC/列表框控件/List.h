// �б��ؼ�.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CListApp:
// �йش����ʵ�֣������ �б��ؼ�.cpp
//

class CListApp : public CWinApp
{
public:
	CListApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CListApp theApp;