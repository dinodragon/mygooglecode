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
	bool Create();
public:
	CNamedPipeClient(const char * szPipName);
	~CNamedPipeClient(void);
	template<typename T> std::string Send(T &cmd)
	{
		Create();
		DWORD dwWrite;
		//向命名管道中写入数据
		if(!WriteFile(hPipe_,(void *)&cmd,sizeof(cmd), &dwWrite, NULL))
		{
			std::cout<<"WriteFile failed!"<<std::endl;
			return "";
		}
		DWORD dwRead;
		char * pReadBuf = new char[BUFSIZE + 1];
		memset(pReadBuf, 0,BUFSIZE + 1);
		//从命名管道中读取数据
		if(!ReadFile(hPipe_, pReadBuf,BUFSIZE, &dwRead, NULL))
		{
			delete []pReadBuf;
			std::cout<<"ReadFile failed!"<<std::endl;
			return "";
		}
		std::string result = std::string(pReadBuf,dwRead);
		delete []pReadBuf;
		return result;
	}
};
