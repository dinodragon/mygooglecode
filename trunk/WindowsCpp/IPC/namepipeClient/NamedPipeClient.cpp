#include "NamedPipeClient.h"
#include <iostream>

CNamedPipeClient::CNamedPipeClient(const char * szPipName):hPipe_(NULL),pipeName_(szPipName)
{
	hReadEvent_ = CreateEvent(NULL,FALSE,FALSE,NULL);
}

CNamedPipeClient::~CNamedPipeClient()
{
	if (hPipe_)
	{
		CloseHandle(hPipe_);
	}
	if (hReadEvent_)
	{
		CloseHandle(hReadEvent_);
	}
}

bool CNamedPipeClient::Create()
{
	if(!WaitNamedPipe(pipeName_.c_str(), NMPWAIT_NOWAIT))
	{
		std::cout<<"WaitNamedPipe failed!"<<std::endl;
		return false;
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
		return false;
	}
	return true;
}


