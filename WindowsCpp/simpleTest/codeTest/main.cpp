#include <iostream>
#include <tchar.h>
#include <Windows.h>


int main(int argc, _TCHAR* argv[])
{
	char str[] = "����";
	std::cout << sizeof(str) <<std::endl;
	MessageBox(NULL,str,TEXT("����"),MB_OK);
//	std::cout<<"??"<<std::endl;
	return 0;
}

