// GetProcessInfo.cpp : �������̨Ӧ�ó������ڵ㡣
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
	wsprintf(chBuf,_T("ȱҳ�жϴ���: %d"), pmc.PageFaultCount/1024 );
	wcout<<chBuf<<endl;

	wsprintf(chBuf,_T("�ڴ�ʹ�ø߷�: %d"), pmc.PeakWorkingSetSize/1024);
	wcout<<chBuf<<endl;

	wsprintf(chBuf,_T("�ڴ�ʹ��: %d"), pmc.WorkingSetSize/1024 );
	wcout<<chBuf<<endl;

	wsprintf(chBuf,_T("ʹ��ҳ�滺��ظ߷�: %d"),pmc.QuotaPeakPagedPoolUsage/1024);
	wcout<<chBuf<<endl;

	wsprintf(chBuf,_T("ʹ��ҳ�滺���: %d"),pmc.QuotaPagedPoolUsage/1024);
	wcout<<chBuf<<endl;

	wsprintf(chBuf,_T("ʹ�÷Ƿ�ҳ����ظ߷�: %d"),pmc.QuotaPeakNonPagedPoolUsage/1024);
	wcout<<chBuf<<endl;

	wsprintf(chBuf,_T("ʹ�÷Ƿ�ҳ�����: %d"),pmc.QuotaNonPagedPoolUsage/1024);
	wcout<<chBuf<<endl;

	wsprintf(chBuf,_T("ʹ�÷�ҳ�ļ�: %d"), pmc.PagefileUsage/1024); 
	wcout<<chBuf<<endl;

	wsprintf(chBuf,_T("ʹ�÷�ҳ�ļ��ĸ߷�: %d"), pmc.PeakPagefileUsage/1024);
	wcout<<chBuf<<endl;

	wsprintf(chBuf,_T("ʹ�÷�ҳ�ļ��ĸ߷�: %d"), pmc.PeakPagefileUsage );

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

