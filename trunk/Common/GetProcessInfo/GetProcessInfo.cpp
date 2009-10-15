// GetProcessInfo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "Windows.h"
#include "psapi.h"
#include <string>
#pragma 
using namespace std;

BOOL IsProcessContainModName(DWORD dwProcessId,LPCTSTR szModeName);
BOOL GetProcessMemInfo(LPCTSTR,PROCESS_MEMORY_COUNTERS *);

int _tmain(int argc, _TCHAR* argv[])
{
	PROCESS_MEMORY_COUNTERS pmc;
	BOOL b = GetProcessMemInfo(_T("QQ.exe"),&pmc);
	if (!b)
	{
		return 0;
	}

	const int nBufSize = 512;
	TCHAR chBuf[nBufSize];
	ZeroMemory(chBuf,nBufSize);
	wsprintf(chBuf,_T("缺页中断次数: %d"), pmc.PageFaultCount/1024 );
	wcout<<chBuf<<endl;

	wsprintf(chBuf,_T("内存使用高峰: %d"), pmc.PeakWorkingSetSize/1024);
	wcout<<chBuf<<endl;

	wsprintf(chBuf,_T("内存使用: %d"), pmc.WorkingSetSize/1024 );
	wcout<<chBuf<<endl;

	wsprintf(chBuf,_T("使用页面缓存池高峰: %d"),pmc.QuotaPeakPagedPoolUsage/1024);
	wcout<<chBuf<<endl;

	wsprintf(chBuf,_T("使用页面缓存池: %d"),pmc.QuotaPagedPoolUsage/1024);
	wcout<<chBuf<<endl;

	wsprintf(chBuf,_T("使用非分页缓存池高峰: %d"),pmc.QuotaPeakNonPagedPoolUsage/1024);
	wcout<<chBuf<<endl;

	wsprintf(chBuf,_T("使用非分页缓存池: %d"),pmc.QuotaNonPagedPoolUsage/1024);
	wcout<<chBuf<<endl;

	wsprintf(chBuf,_T("使用分页文件: %d"), pmc.PagefileUsage/1024); 
	wcout<<chBuf<<endl;

	wsprintf(chBuf,_T("使用分页文件的高峰: %d"), pmc.PeakPagefileUsage/1024);
	wcout<<chBuf<<endl;

	wsprintf(chBuf,_T("使用分页文件的高峰: %d"), pmc.PeakPagefileUsage );

	return 0;
}

BOOL GetProcessMemInfo(LPCTSTR szModeName ,PROCESS_MEMORY_COUNTERS * ppmc)
{
	DWORD dwCount;
	DWORD * m_pids;
	DWORD nalloc = 1024;
	m_pids = new DWORD[nalloc];
	BOOL bflag = FALSE;
	if (EnumProcesses(m_pids, nalloc*sizeof(DWORD), &dwCount))
	{
		dwCount /= sizeof(DWORD);
	}
	for (DWORD i = 1;i < dwCount;i++)
	{
		if (IsProcessContainModName(m_pids[i],szModeName))
		{
			HANDLE hp = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,m_pids[i]);
			(*ppmc).cb = sizeof(PROCESS_MEMORY_COUNTERS);
			if (GetProcessMemoryInfo(hp,ppmc,sizeof(*ppmc)))
			{
				bflag = TRUE;
				break;
			}
		}		
	}
	delete[] m_pids;
	return bflag;
}

BOOL IsProcessContainModName(DWORD dwProcessId,LPCTSTR szModeName)
{
	string NeedFindModName(szModeName);
	HMODULE * hModules = NULL;
	DWORD m_dwModCount = 0;
	DWORD nalloc = 1024;
	BOOL result = FALSE;
	TCHAR modName[_MAX_PATH];
	HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE,dwProcessId);
	if (handle) 
	{
		hModules = new HMODULE[nalloc];
		if (EnumProcessModules(handle, hModules,nalloc*sizeof(HMODULE), &m_dwModCount)) 
		{
			m_dwModCount /= sizeof(HMODULE);
		}
		for (DWORD j = 0 ;j<m_dwModCount ;j++)
		{
			GetModuleBaseName(handle,hModules[j],modName,_MAX_PATH);
			if (NeedFindModName.compare(modName)==0)
			{
				result = TRUE;
				break;
			}
		}
		delete[] hModules;
	}
	CloseHandle(handle);
	return result;
}

