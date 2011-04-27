#include <windows.h>
#include <iostream>
#include "dll.h"

using namespace std;

int main(void)
{
	/*
	typedef void (* DLLWITHLIB )(void);
	//定义一个函数指针变量
	DLLWITHLIB pfFuncInDll = NULL;
	
	//加载我们的dll
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
