#define UNICODE
#include <iostream>
#include <tchar.h>
#include <Windows.h>


int main(int argc, _TCHAR* argv[])
{
	wchar_t str[] = TEXT("中文");
	std::cout << sizeof(str) <<std::endl;
	MessageBox(NULL,str,TEXT("标题"),MB_OK);
//	std::cout<<"??"<<std::endl;
	return 0;
}

