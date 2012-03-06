// namepipeClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>

using namespace std;

HANDLE            hNamedPipe;
const char * pStr        = "Zachary";
const char * pPipeName    = "\\\\.\\pipe\\ZacharyPipe";

//打开命名管道
void OpenNamedPipeInClient();
//客户端从命名管道中读取数据
void NamedPipeReadInClient();
//客户端往命名管道中写入数据
void NamedPipeWriteInClient();

int main(int argc, char * argv)
{
	OpenNamedPipeInClient();
	//接收服务端发来的数据
	NamedPipeReadInClient();
	//往命名管道中写入数据
	NamedPipeWriteInClient();
	system("pause");
}

void OpenNamedPipeInClient()
{
	//等待连接命名管道
	if(!WaitNamedPipe(pPipeName, NMPWAIT_WAIT_FOREVER))
	{
		cout<<"命名管道实例不存在 ..."<<endl<<endl;
		return;
	}
	//打开命名管道
	hNamedPipe = CreateFile(pPipeName, GENERIC_READ | GENERIC_WRITE, 
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(INVALID_HANDLE_VALUE == hNamedPipe)
	{
		cout<<"打开命名管道失败 ..."<<endl<<endl;
		return;
	}
}
 
 
void NamedPipeReadInClient()
{
	char *                pReadBuf;
	DWORD                dwRead;
	 
	pReadBuf = new char[strlen(pStr) + 1];
	memset(pReadBuf, 0, strlen(pStr) + 1);
	 
	//从命名管道中读取数据
	if(!ReadFile(hNamedPipe, pReadBuf, strlen(pStr), &dwRead, NULL))
	{
		delete []pReadBuf;
		 
		cout<<"读取数据失败 ..."<<endl<<endl;
		return;
	}
	cout<<"读取数据成功：    "<<pReadBuf<<endl<<endl;
}
 
 
void NamedPipeWriteInClient()
{
	DWORD                dwWrite;
	 
	//向命名管道中写入数据
	if(!WriteFile(hNamedPipe, pStr, strlen(pStr), &dwWrite, NULL))
	{
		cout<<"写入数据失败 ..."<<endl<<endl;
		return;
	}
	cout<<"写入数据成功：    "<<pStr<<endl<<endl;
}

