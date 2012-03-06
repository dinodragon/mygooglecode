#include "NamedPipe.h"
#include <iostream>

CNamedPipe::CNamedPipe()
{
}

CNamedPipe::~CNamedPipe(void)
{
	CloseHandle(hPipe_);
}

bool CNamedPipe::Create(char* szPipName)
{
	hPipe_ = CreateNamedPipe(
		szPipName, 
		PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
		0,
		1,
		1024,
		1024,
		0,
		NULL
		);
	if(INVALID_HANDLE_VALUE == hPipe_)
	{
		std::cout<<"Create namedPipe failed!"<<std::endl;
		hPipe_ = NULL;
		return false;
	}
	return true;
}

bool CNamedPipe::Listen()
{
	OVERLAPPED ovlpd;
	HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if(!hEvent)
	{
		std::cout<<"Create event failed!"<<std::endl;
		return false;
	}
	memset(&ovlpd, 0, sizeof(OVERLAPPED));
	ovlpd.hEvent = hEvent;
	if(!ConnectNamedPipe(hPipe_, &ovlpd))
	{
		if(ERROR_IO_PENDING != GetLastError())
		{
			std::cout<<"ConnectNamedPipe failed!"<<std::endl;
			CloseHandle(hEvent);
			return false;
		}
	}
	if(WAIT_FAILED == WaitForSingleObject(hEvent, INFINITE))
	{
		std::cout<<"WaitForSingleObject failed!"<<std::endl;
		CloseHandle(hEvent);
		return false;
	}
	CloseHandle(hEvent);

	DWORD dwRead;
	char * pReadBuf = new char[BUFSIZE];
	memset(pReadBuf, 0,BUFSIZE + 1);

	//从命名管道中读取数据
	if(!ReadFile(hPipe_, pReadBuf,BUFSIZE, &dwRead, NULL))
	{
		delete []pReadBuf;
		std::cout<<"ReadFile failed!"<<std::endl;
		return false;
	}
	std::string cmd(pReadBuf);
	delete []pReadBuf;
	std::string result = Process(cmd.c_str());
	DWORD dwWrite;
	if(!WriteFile(hPipe_, result.c_str(), result.length(), &dwWrite, NULL))
	{
		std::cout<<"WriteFile failed!"<<std::endl;
		return false;
	}
	std::cout<<"WriteFile Succeed："<<result.c_str()<<std::endl;
}

std::string CNamedPipe::Process(const char * cmd)
{
	std::cout<<"ReadFile Succeed:"<<cmd<<std::endl;
	return "OK!";
}

bool CNamedPipe::Stop()
{
	return false;
}

bool CNamedPipe::Close()
{
	return false;
}