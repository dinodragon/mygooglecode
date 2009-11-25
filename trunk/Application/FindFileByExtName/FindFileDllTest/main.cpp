#include <iostream>
#include "windows.h"

using namespace std;


extern "C" int FindByExtFix(const wstring pwszPath,const wstring pwszPostfix,wstring arrFileName[]);

void main()
{
	wstring str[80];
	wstring path = TEXT("G:\\QQDownload\\");
	wstring ext = TEXT(".rar");
	FindByExtFix(path,ext,str);

}