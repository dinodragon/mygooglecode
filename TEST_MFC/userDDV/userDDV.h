// userDDV.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CuserDDVApp:
// �йش����ʵ�֣������ userDDV.cpp
//

class CuserDDVApp : public CWinApp
{
public:
	CuserDDVApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CuserDDVApp theApp;