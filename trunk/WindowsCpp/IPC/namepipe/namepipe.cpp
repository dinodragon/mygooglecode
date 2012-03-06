// namepipe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;

//////////////////////////////////////////////////////////////////////////
//Server
//////////////////////////////////////////////////////////////////////////

void CreateNamedPipeInServer();
void NamedPipeWriteInServer();
void NamedPipeReadInServer();

HANDLE            hNamedPipe;
const char *    pStr        = "Zachary";
const char *    pPipeName    = "\\\\.\\pipe\\ZacharyPipe"; 

int main(int argc, char * argv)
{
	CreateNamedPipeInServer();
	//�ڷ�������ܵ���д������
	NamedPipeWriteInServer();
	//���տͻ��˷���������
	NamedPipeReadInServer();
	system("pause");
}
 
 
void CreateNamedPipeInServer()
{
	HANDLE                    hEvent;
	OVERLAPPED                ovlpd;
	 
	//������Ҫ���������ܵ�
	//���ﴴ������˫��ģʽ��ʹ���ص�ģʽ�������ܵ�
	hNamedPipe = CreateNamedPipe(pPipeName, 
		PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED, 
		0, 1, 1024, 1024, 0, NULL);
	 
	if(INVALID_HANDLE_VALUE == hNamedPipe)
	{
		hNamedPipe = NULL;
		std::cout<<"���������ܵ�ʧ��..."<<std::endl;
		return;
	}
	std::cout<<"�����ܵ��ɹ�!"<<endl;
	//����¼��Եȴ��ͻ������������ܵ�
	//���¼�Ϊ�ֶ������¼����ҳ�ʼ��״̬Ϊ���ź�״̬
	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if(!hEvent)
	{
		std::cout<<"�����¼�ʧ�� ..."<<std::endl;
		return;
	}
	memset(&ovlpd, 0, sizeof(OVERLAPPED));
	//���ֶ������¼����ݸ� ovlap ����
	ovlpd.hEvent = hEvent;
	//�ȴ��ͻ�������
	if(!ConnectNamedPipe(hNamedPipe, &ovlpd))
	{
		if(ERROR_IO_PENDING != GetLastError())
		{
			CloseHandle(hNamedPipe);
			CloseHandle(hEvent);
			std::cout<<"�ȴ��ͻ�������ʧ�� ..."<<std::endl;
			return;
		}
	}
	//�ȴ��¼� hEvent ʧ��
	if(WAIT_FAILED == WaitForSingleObject(hEvent, INFINITE))
	{
		CloseHandle(hNamedPipe);
		CloseHandle(hEvent);
		cout<<"�ȴ�����ʧ�� ..."<<endl<<endl;
		return;
	}
	CloseHandle(hEvent);
}
 
 
void NamedPipeReadInServer()
{
	char *            pReadBuf;
	DWORD            dwRead;
	 
	pReadBuf = new char[strlen(pStr) + 1];
	memset(pReadBuf, 0, strlen(pStr) + 1);
	 
	//�������ܵ��ж�ȡ����
	if(!ReadFile(hNamedPipe, pReadBuf, strlen(pStr), &dwRead, NULL))
	{
		delete []pReadBuf;
		cout<<"��ȡ����ʧ��..."<<endl<<endl;
		return;
	}
	cout<<"��ȡ���ݳɹ���"<<pReadBuf<<endl<<endl;
}
 
 
void NamedPipeWriteInServer()
{
	DWORD            dwWrite;
	 
	//�������ܵ���д������
	if(!WriteFile(hNamedPipe, pStr, strlen(pStr), &dwWrite, NULL))
	{
		cout<<"д������ʧ�� ..."<<endl<<endl;
		return;
	}
	cout<<"д�����ݳɹ���    "<<pStr<<endl<<endl;
}
