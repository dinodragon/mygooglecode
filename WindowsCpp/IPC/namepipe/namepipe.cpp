// namepipe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "NamedPipeServer.h"
//////////////////////////////////////////////////////////////////////////
//Server
//////////////////////////////////////////////////////////////////////////

int main(int argc, char * argv)
{
	const char* pPipeName = "\\\\.\\pipe\\ZacharyPipe";
	CNamedPipeServer cnp;
	cnp.Create(pPipeName);
	cnp.Listen();
}
 
 
