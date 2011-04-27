#include "windows.h"
#include <iostream>

using namespace std;

extern "C" _declspec(dllexport) int add(const int x,const int y);
extern "C" _declspec(dllexport) int len(const char * str);
extern "C" _declspec(dllexport) int wlen(const wchar_t * str);

int add(const int x,const int y)
{
	return x+y;
}

int wlen(const wchar_t * str)
{
	return wcslen(str);
}

int len(const char * str)
{
	return strlen(str);
}