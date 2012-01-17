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
	//ȫ�ֹ��ӱ������Dll����.
	//hHook=SetWindowsHookEx(WH_KEYBOARD,KeyboardProc,0,0);

	hHook=SetWindowsHookEx(WH_KEYBOARD,KeyboardProc,0,GetCurrentThreadId()); 
	MessageBox(NULL,TEXT("ж�ؼ��̹��ӣ������ڸô���ʱ�������ᱻ��¼������"),TEXT("HookDemo"),MB_OK);
	if(hHook) 
		UnhookWindowsHookEx(hHook); 
	return 0;
}


LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
	std::cout<<"nCode:"<<nCode<<"\tWPARAM:"<<wParam<<"\tLPARAM:"<<lParam<<std::endl;


	//���ݹ�����Ϣ 
	return CallNextHookEx(hHook,nCode,wParam,lParam); 
} 

