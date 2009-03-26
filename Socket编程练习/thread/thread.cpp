#include <windows.h>
#include <iostream>

using namespace std;

DWORD WINAPI Fun1Proc(LPVOID lpParameter);

DWORD WINAPI Fun2Proc(
  LPVOID lpParameter   // thread data
);
int index=0;
int tickets=100;
HANDLE hMutex;
void main()
{
	HANDLE hThread1;
	HANDLE hThread2;
	hThread1=CreateThread(NULL,0,Fun1Proc,NULL,0,NULL);
	hThread2=CreateThread(NULL,0,Fun2Proc,NULL,0,NULL);
	CloseHandle(hThread1);
	CloseHandle(hThread2);

	Sleep(4000);
//	Sleep(10);
}

DWORD WINAPI Fun1Proc(
  LPVOID lpParameter   // thread data
)
{
	cout<<"thread1 is running"<<endl;
	return 0;
}

DWORD WINAPI Fun2Proc( LPVOID lpParameter )

{
	cout<<"thread2 is running"<<endl;
	return 0;
}