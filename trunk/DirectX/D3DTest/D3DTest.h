// D3DTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CD3DTestApp:
// �йش����ʵ�֣������ D3DTest.cpp
//

class CD3DTestApp : public CWinApp
{
public:
	CD3DTestApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CD3DTestApp theApp;