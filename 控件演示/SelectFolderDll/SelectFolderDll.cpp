// SelectFolderDll.cpp : ���� DLL Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "SelectFolder.h"


#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

__declspec(dllexport) bool SelectFolder(const wchar_t * initPath,wchar_t * resultPath)
{
	CSelectFolder selctFolder;
	return selctFolder.SelectFolder(initPath,resultPath);
}