// ShowCompileTime.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CShowCompileTimeApp:
// �йش����ʵ�֣������ ShowCompileTime.cpp
//

class CShowCompileTimeApp : public CWinApp
{
public:
	CShowCompileTimeApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CShowCompileTimeApp theApp;