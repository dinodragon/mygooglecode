#pragma once
#include <Windows.h>

class CLogger
{
public:
	CLogger(void);
	~CLogger(void);
	bool WriteLog(const wchar_t* wszLogText);

private:
	static HANDLE m_hFile;
};
