// GetProcessInfo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
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
	BOOL b = GetProcessMemInfo(L"QQ.exe",&pmc);
	if (!b)
	{
		return 0;
	}

	const int nBufSize = 512;
	TCHAR chBuf[nBufSize];
	ZeroMemory(chBuf,nBufSize);

	wsprintf(chBuf,_T("\tȱҳ�жϴ���: %d\n"), pmc.PageFaultCount/1024 );
	OutputDebugString(chBuf);

	wsprintf(chBuf,_T("\t�ڴ�ʹ�ø߷�: %d\n"), pmc.PeakWorkingSetSize/1024);
	OutputDebugString(chBuf);

	wsprintf(chBuf,_T("\t�ڴ�ʹ��: %d\n"), pmc.WorkingSetSize/1024 );
	OutputDebugString(chBuf);

	wsprintf(chBuf,_T("\tʹ��ҳ�滺��ظ߷�: %d\n"),pmc.QuotaPeakPagedPoolUsage/1024);
	OutputDebugString(chBuf);

	wsprintf(chBuf,_T("\tʹ��ҳ�滺���: %d\n"),pmc.QuotaPagedPoolUsage/1024);
	OutputDebugString(chBuf);

	wsprintf(chBuf,_T("\tʹ�÷Ƿ�ҳ����ظ߷�: %d\n"),pmc.QuotaPeakNonPagedPoolUsage/1024);
	OutputDebugString(chBuf);

	wsprintf(chBuf,_T("\tʹ�÷Ƿ�ҳ�����: %d\n"),pmc.QuotaNonPagedPoolUsage/1024);
	OutputDebugString(chBuf);

	wsprintf(chBuf,_T("\tʹ�÷�ҳ�ļ�: %d\n"), pmc.PagefileUsage/1024); 
	OutputDebugString(chBuf);

	wsprintf(chBuf,_T("\tʹ�÷�ҳ�ļ��ĸ߷�: %d\n"), pmc.PeakPagefileUsage/1024);
	OutputDebugString(chBuf);

	wsprintf(chBuf,_T("\tʹ�÷�ҳ�ļ��ĸ߷�: %d\n"), pmc.PeakPagefileUsage );

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
	wstring NeedFindModName(szModeName);
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

