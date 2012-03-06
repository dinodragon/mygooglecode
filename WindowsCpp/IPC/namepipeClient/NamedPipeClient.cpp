#include "NamedPipeClient.h"
#include <iostream>

CNamedPipeClient::CNamedPipeClient():hPipe_(NULL)
{
}

CNamedPipeClient::~CNamedPipeClient(void)
{
	if (hPipe_)
	{
		CloseHandle(hPipe_);
	}
}

bool CNamedPipeClient::Create(const char * szPipName)
{
	pipeName_ = szPipName;
	return true;
}

std::string CNamedPipeClient::Send(std::string cmd)
{
	std::string result = "";
	if(!WaitNamedPipe(pipeName_.c_str(), NMPWAIT_WAIT_FOREVER))
	{
		std::cout<<"WaitNamedPipe failed!"<<std::endl;
		return result;
	}
	hPipe_ = CreateFile(
		pipeName_.c_str(),
		GENERIC_READ | GENERIC_WRITE, 
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);
	if(INVALID_HANDLE_VALUE == hPipe_)
	{
		std::cout<<"CreateFile failed!"<<std::endl;
		return result;
	}
	DWORD                dwWrite;
	//向命名管道中写入数据
	if(!WriteFile(hPipe_, cmd.c_str(),cmd.length(), &dwWrite, NULL))
	{
		std::cout<<"WriteFile failed!"<<std::endl;
		return result;
	}

	DWORD dwRead;
	char * pReadBuf = new char[BUFSIZE + 1];
	memset(pReadBuf, 0,BUFSIZE + 1);
	//从命名管道中读取数据
	if(!ReadFile(hPipe_, pReadBuf,BUFSIZE, &dwRead, NULL))
	{
		delete []pReadBuf;
		std::cout<<"ReadFile failed!"<<std::endl;
		return result;
	}
	result = std::string(pReadBuf);
	delete []pReadBuf;
	return result;
}


bool CNamedPipeClient::Stop()
{
	return false;
}

bool CNamedPipeClient::Close()
{
	return false;
}