// namepipeClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "namedPipeClient.h"
#include <Windows.h>
#include <iostream>

typedef struct _CmdInfo
{
	char cmd[10];
	char path[20];
} CmdInfo;


int main(int argc, char * argv)
{
	CmdInfo info;
	const char * pPipeName    = "\\\\.\\pipe\\ZacharyPipe";
	char data[] = "sdfasfasdjkkjhkfaskfjjs!";
	CNamedPipeClient client(pPipeName);
	std::string r = client.Send(data);
	std::cout<<r.c_str()<<std::endl;
}

