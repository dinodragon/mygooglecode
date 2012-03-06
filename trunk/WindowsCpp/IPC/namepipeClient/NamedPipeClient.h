#pragma once

#include <stdio.h>
#include <string>
#include <windows.h>

const DWORD BUFSIZE = 1024;  
const DWORD PIPE_TIMEOUT = 5000;  

class CNamedPipeClient
{
private:  
	HANDLE hPipe_;
	std::string pipeName_;
public:
	CNamedPipeClient();
	~CNamedPipeClient(void);
	bool Create(const char * szPipName);
	std::string Send(std::string cmd);
	bool Stop();
	bool Close();
};
