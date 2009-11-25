// FindFileDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

extern "C" _declspec(dllexport) int FindByExtFix(const wstring pwszPath,const wstring pwszPostfix,wstring arrFileName[]);

int FindByPostfix(const wchar_t* pwszPath,const wchar_t* pwszPostfix,std::vector<std::wstring>& arrFileName) 
{

	wchar_t pszFind[MAX_PATH]; 
	lstrcpy(pszFind, pwszPath);
	lstrcat(pszFind, L"*.*"); 
	WIN32_FIND_DATA wfd; 
	HANDLE hFind = FindFirstFile(pszFind, &wfd); 
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		return 0; 
	}
	do 
	{ 
		if (wfd.cFileName[0] == '.') 
		{
			continue; 
		}
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
		{ 
			wchar_t wszFileName[MAX_PATH]; 
			wsprintf(wszFileName, L"%s%s\\", pwszPath, wfd.cFileName); 
			FindByPostfix(wszFileName,pwszPostfix,arrFileName); 
		} 
		else 
		{ 
			wchar_t wszFileName[MAX_PATH]; 
			wsprintf(wszFileName, L"%s%s", pwszPath, wfd.cFileName); 
			std::wstring strFileName = wszFileName;
			if(strFileName.substr(strFileName.length() - 4,4).compare(pwszPostfix) == 0)
			{
				arrFileName.push_back(wszFileName);
			}
		} 
	} while (FindNextFile(hFind, &wfd)); 
	FindClose(hFind);
	return 0;
}

int FindByExtFix(const wstring pwszPath,const wstring pwszPostfix,wstring arrFileName[])
{
	const wchar_t * wPath = pwszPath.c_str();
	const wchar_t * wPost = pwszPostfix.c_str();
	std::vector<std::wstring> arrfile;
	FindByPostfix(wPath,wPost,arrfile);
	for(size_t i = 0;i<arrfile.size();i++)
	{
		arrFileName[i] = arrfile[i];
	}
	return 0;
}