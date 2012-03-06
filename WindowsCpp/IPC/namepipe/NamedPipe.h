#pragma once

#include <stdio.h>
#include <string>
#include <windows.h>

const DWORD BUFSIZE = 1024;  
const DWORD PIPE_TIMEOUT = 5000;  

class CNamedPipe
{
private:  
	HANDLE hPipe_;
public:
	CNamedPipe();
	~CNamedPipe(void);
	bool Create(char* szPipName);
	bool Listen();
	virtual std::string Process(const char * cmd);
	bool Stop();
	bool Close();
};
