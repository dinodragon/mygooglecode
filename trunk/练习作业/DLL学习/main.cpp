#include <windows.h>
#include <iostream>
#include "dll.h"

using namespace std;

int main(void)
{
	/*
	typedef void (* DLLWITHLIB )(void);
	//����һ������ָ�����
	DLLWITHLIB pfFuncInDll = NULL;
	
	//�������ǵ�dll
	HINSTANCE hinst=::LoadLibrary("dll.dll");
	if (NULL != hinst)
	{
		cout<<"dll loaded!"<<endl;
	}
	
	pfFuncInDll = (DLLWITHLIB)GetProcAddress(hinst, "?FuncInDll@@YAXXZ");
	if (NULL != pfFuncInDll)
	{
		(*pfFuncInDll)();
	}

	*/
	FuncInDll();
	return 0;
}
