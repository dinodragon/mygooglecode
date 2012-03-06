// namepipeClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "namedPipeClient.h"
#include <Windows.h>
#include <iostream>

int main(int argc, char * argv)
{
	const char * pPipeName    = "\\\\.\\pipe\\ZacharyPipe";
	CNamedPipeClient client;
	client.Create(pPipeName);
	std::string r = client.Send("aaaaa!");
	std::cout<<r.c_str()<<std::endl;
}

