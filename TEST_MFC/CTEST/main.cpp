#define WINVER 0x0501
#include <iostream>
#include <afx.h>
#include <string>


using namespace std;

DWORD WINAPI Proc1(PVOID pParam);
DWORD WINAPI Proc2(PVOID pParam);

void main()
{
	cout<<"hello"<<endl;
	HANDLE hThread,hThread1;
	hThread = CreateThread(NULL,0,Proc1,NULL,0,NULL);
	hThread1 = CreateThread(NULL,0,Proc2,NULL,0,NULL);
	Sleep(10);
}

DWORD WINAPI Proc1(PVOID pParam)
{
	for(int i=0;i<100;i++)
		cout<<i<<",";
	return 0;
}

DWORD WINAPI Proc2(PVOID pParam)
{
	for(int i=0;i<100;i++)
		cout<<i<<",";
	return 0;
}
