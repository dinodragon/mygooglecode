// SelFolderDll.h : SelFolderDll DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSelFolderDllApp
// �йش���ʵ�ֵ���Ϣ������� SelFolderDll.cpp
//
extern "C" BOOL PASCAL EXPORT SelectFolder(const wchar_t * initPath,wchar_t * resultPath);

class CSelFolderDllApp : public CWinApp
{
public:
	CSelFolderDllApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
