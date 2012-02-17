#include <stdio.h>
#include <memory.h>
#include <windows.h>

long WINAPI handler(EXCEPTION_POINTERS* lpExceptionInfo) //
{
  printf("handle exception!\r\n");
  return EXCEPTION_EXECUTE_HANDLER;
}

LONG WINAPI CleanToolExceptionFun(struct _EXCEPTION_POINTERS* ExceptionInfo)
{
  printf("handle exception2!\r\n");
  return EXCEPTION_EXECUTE_HANDLER;
}

int main()
{
  SetUnhandledExceptionFilter(CleanToolExceptionFun);
  int *p = 0;
  int a = *p;
  printf("OK\r\n");
}