// KeyBoardHook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
using namespace std;

HHOOK hHook;
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

int _tmain(int argc, _TCHAR* argv[])
{
	//全局钩子必须放在Dll里面.
	//hHook=SetWindowsHookEx(WH_KEYBOARD,KeyboardProc,0,0);

	hHook=SetWindowsHookEx(WH_KEYBOARD,KeyboardProc,0,GetCurrentThreadId()); 
	MessageBox(NULL,TEXT("卸载键盘勾子？焦点在该窗口时，按键会被记录到窗口"),TEXT("HookDemo"),MB_OK);
	if(hHook) 
		UnhookWindowsHookEx(hHook); 
	return 0;
}


LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
	std::cout<<"nCode:"<<nCode<<"\tWPARAM:"<<wParam<<"\tLPARAM:"<<lParam<<std::endl;


	//传递钩子信息 
	return CallNextHookEx(hHook,nCode,wParam,lParam); 
} 

