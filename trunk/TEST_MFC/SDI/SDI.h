// SDI.h : SDI Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CSDIApp:
// �йش����ʵ�֣������ SDI.cpp
//

class CSDIApp : public CWinApp
{
public:
	CSDIApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	DECLARE_MESSAGE_MAP()
};

extern CSDIApp theApp;