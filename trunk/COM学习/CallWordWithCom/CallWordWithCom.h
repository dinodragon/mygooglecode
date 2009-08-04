// CallWordWithCom.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#import   "C:\Program Files\Common Files\Microsoft Shared\OFFICE12\MSO.DLL"   
#import   "C:\Program Files\Common Files\Microsoft Shared\VBA\VBA6\VBE6EXT.OLB"   
#import   "C:\Program Files\Microsoft Office\Office12\msword.olb"  rename("FindText","_FindText"), rename("ExitWindows","_ExitWindows")   


// CCallWordWithComApp:
// 有关此类的实现，请参阅 CallWordWithCom.cpp
//

class CCallWordWithComApp : public CWinApp
{
public:
	CCallWordWithComApp();

// 重写
	public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CCallWordWithComApp theApp;