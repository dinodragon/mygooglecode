#include "NamedPipeServer.h"
#include <iostream>

CNamedPipeServer::CNamedPipeServer():_stop(false)
{
	hEvent_ = CreateEvent(NULL, FALSE, FALSE, NULL);
	if(!hEvent_)
	{
		std::cout<<"Create event failed!"<<std::endl;
	}
}

CNamedPipeServer::~CNamedPipeServer(void)
{
	if (hPipe_)
	{
		CloseHandle(hPipe_);
	}
	if (hEvent_)
	{
		CloseHandle(hEvent_);
	}
}

bool CNamedPipeServer::Create(const char * szPipName)
{
	pipeName_ = szPipName;
	return true;
}

bool CNamedPipeServer::Listen()
{
	OVERLAPPED ovlpd;
	while (true && !_stop)
	{
		hPipe_ = CreateNamedPipe(
			pipeName_.c_str(), 
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
		memset(&ovlpd, 0, sizeof(OVERLAPPED));
		ovlpd.hEvent = hEvent_;
		if(!ConnectNamedPipe(hPipe_, &ovlpd))
		{
			if(ERROR_IO_PENDING != GetLastError())
			{
				std::cout<<"ConnectNamedPipe failed!"<<std::endl;
				return false;
			}
		}
		if(WAIT_FAILED == WaitForSingleObject(hEvent_, INFINITE))
		{
			std::cout<<"WaitForSingleObject failed!"<<std::endl;
			return false;
		}
		DWORD dwRead;
		char * pReadBuf = new char[BUFSIZE + 1];
		memset(pReadBuf, 0,BUFSIZE + 1);
		if(!ReadFile(hPipe_, pReadBuf,BUFSIZE, &dwRead, NULL))
		{
			delete[] pReadBuf;
			std::cout<<"ReadFile failed!"<<std::endl;
			return false;
		}
		std::string cmd(pReadBuf,dwRead);
		delete []pReadBuf;
		std::string result = Process(cmd.c_str());
		DWORD dwWrite;
		if(!WriteFile(hPipe_, result.c_str(), result.length(), &dwWrite, NULL))
		{
			std::cout<<"WriteFile failed!"<<std::endl;
			return false;
		}
		CloseHandle(hPipe_);
		hPipe_ = NULL;
	}
	return true;
}

std::string CNamedPipeServer::Process(const char * cmd)
{
	std::string result = std::string(cmd) + ":OK";
	std::cout<<"receive:"<<cmd<<std::endl;
	std::cout<<"return:"<<result.c_str()<<std::endl;
	return result;
}
