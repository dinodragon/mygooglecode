// D3DIndexTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CD3DIndexTestApp:
// �йش����ʵ�֣������ D3DIndexTest.cpp
//

class CD3DIndexTestApp : public CWinApp
{
public:
	CD3DIndexTestApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CD3DIndexTestApp theApp;