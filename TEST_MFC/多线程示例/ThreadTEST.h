// ThreadTEST.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C���߳�ʾ��App:
// �йش����ʵ�֣������ ThreadTEST.cpp
//

class CThreadTESTApp : public CWinApp
{
public:
	CThreadTESTApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CThreadTESTApp theApp;