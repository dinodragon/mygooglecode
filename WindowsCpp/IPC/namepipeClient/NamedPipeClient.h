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
	HANDLE hReadEvent_;
	std::string pipeName_;
	bool Create();
public:
	CNamedPipeClient(const char * szPipName);
	~CNamedPipeClient(void);
	template<typename T> std::string Send(T &cmd)
	{
		if (!Create())
		{
			return "-1";
		}
		DWORD dwWrite;
		if(!WriteFile(hPipe_,(void *)&cmd,sizeof(cmd), &dwWrite, NULL))
		{
			std::cout<<"WriteFile failed!"<<std::endl;
			return "-1";
		}
		OVERLAPPED ovlpd;
		memset(&ovlpd, 0, sizeof(OVERLAPPED));
		//ovlpd.hEvent = hReadEvent_;

		DWORD dwRead;
		char * pReadBuf = new char[BUFSIZE + 1];
		memset(pReadBuf, 0,BUFSIZE + 1);
		//从命名管道中读取数据
		if(!ReadFile(hPipe_, pReadBuf,BUFSIZE, &dwRead, &ovlpd))
		{
			std::cout<<"ReadFile failed!"<<std::endl;
			return "-1";
		}
		std::string result = std::string(pReadBuf,dwRead);
		delete []pReadBuf;
		return result;
	}
};
