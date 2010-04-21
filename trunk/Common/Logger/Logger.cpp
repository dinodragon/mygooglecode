#include "StdAfx.h"
#include "Logger.h"
#include <string>
#include <time.h>


HANDLE CLogger::m_hFile = NULL;

CLogger::CLogger()
{
	if (m_hFile != NULL)
	{
		return;
	}
	std::wstring wstrLogFilePath = L"C:\\PluginLog.txt";
	m_hFile = ::CreateFile(wstrLogFilePath.c_str(), GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, 0);
	if(m_hFile == INVALID_HANDLE_VALUE)
	{
		m_hFile = ::CreateFile(wstrLogFilePath.c_str(), GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, 0);
		WORD wFileHead = 0xFEFF;
		DWORD dwWriteSize = 0L;
		::WriteFile(m_hFile, &wFileHead, sizeof(WORD), &dwWriteSize, NULL);
	}
}

CLogger::~CLogger()
{
	::CloseHandle(m_hFile);
}

bool CLogger::WriteLog(const wchar_t* wszLogText)
{
	if(m_hFile == INVALID_HANDLE_VALUE)
		return false;
	SetFilePointer(m_hFile,0,NULL,FILE_END);
	__time64_t timecount;
	_time64(&timecount);
	tm tmdata;
	_localtime64_s(&tmdata, &timecount);
	wchar_t timestr[MAX_PATH] = {0};
	wcsftime(timestr, MAX_PATH, L"-- %Y-%m-%d %H:%M:%S --\r\n", &tmdata);
	std::wstring strLogText = timestr;
	strLogText += wszLogText;
	strLogText += L"\r\n";
	strLogText += L"---\r\n\r\n";

	DWORD dwWriteSize = 0L;
	::WriteFile(m_hFile, strLogText.c_str(),(DWORD)strLogText.length()*sizeof(wchar_t), &dwWriteSize, NULL);
	return true;
}