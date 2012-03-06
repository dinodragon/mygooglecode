#pragma once

#include <stdio.h>
#include <string>
#include <windows.h>

const DWORD BUFSIZE = 1024;  
const DWORD PIPE_TIMEOUT = 5000;  

class CNamedPipeServer
{
private:  
	HANDLE hPipe_;
	HANDLE hEvent_;
	std::string pipeName_;
	bool _stop;
public:
	CNamedPipeServer();
	~CNamedPipeServer(void);
	bool Create(const  char * szPipName);
	bool Listen();
	virtual std::string Process(const char * cmd);
	bool Stop(){_stop = true;};
	//bool Close();
};
