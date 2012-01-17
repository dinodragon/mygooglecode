#include <iostream>
#include <Windows.h>

int main()
{
  HANDLE event = CreateEvent(NULL, true, true, NULL);
  std::wcout<<TEXT("start wait...")<<std::endl;
  WaitForSingleObject(event, INFINITE);
  //WaitForSingleObject(event, INFINITE);
  std::wcout<<TEXT("end")<<std::endl;
}