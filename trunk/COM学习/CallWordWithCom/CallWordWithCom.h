// CallWordWithCom.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#import   "C:\Program Files\Common Files\Microsoft Shared\OFFICE12\MSO.DLL"   
#import   "C:\Program Files\Common Files\Microsoft Shared\VBA\VBA6\VBE6EXT.OLB"   
#import   "C:\Program Files\Microsoft Office\Office12\msword.olb"  rename("FindText","_FindText"), rename("ExitWindows","_ExitWindows")   


// CCallWordWithComApp:
// �йش����ʵ�֣������ CallWordWithCom.cpp
//

class CCallWordWithComApp : public CWinApp
{
public:
	CCallWordWithComApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCallWordWithComApp theApp;