// SelFolderDll.h : SelFolderDll DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CSelFolderDllApp
// 有关此类实现的信息，请参阅 SelFolderDll.cpp
//
extern "C" BOOL PASCAL EXPORT SelectFolder(const wchar_t * initPath,wchar_t * resultPath);

class CSelFolderDllApp : public CWinApp
{
public:
	CSelFolderDllApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
