// namepipeClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "namedPipeClient.h"
#include <Windows.h>
#include <iostream>

typedef struct _CmdStruct 
{
	char szName[MAX_PATH];
	char szParam[MAX_PATH];
	char authoid[32];
}CmdStruct,*PCmdStruct;


int main(int argc, char * argv)
{
	SECURITY_DESCRIPTOR sd;
	InitializeSecurityDescriptor(&sd,SECURITY_DESCRIPTOR_REVISION);
	SetSecurityDescriptorDacl(&sd,TRUE,NULL,FALSE);
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = &sd;

	CmdStruct info;
	const char * pPipeName = "\\\\.\\pipe\\RenRenServicePipe";
	strcpy(info.szName,"C:\\Users\\yangfei\\AppData\\Roaming\\renren.com\\RenRenUpdate.exe");
	strcpy(info.szParam,"\"C:\\Users\\yangfei\\AppData\\Roaming\\renren.com\\update\\xntalk\" \"4.57.1.6_full.mar\" 0 \"d:\\xntalk\\4.056\"  \"xntalk.exe\" off");
	CNamedPipeClient client(pPipeName);
	std::string r = client.Send(info);
	std::cout<<r.c_str()<<std::endl;
}

