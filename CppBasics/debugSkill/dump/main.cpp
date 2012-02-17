#include <stdio.h>
#include <memory.h>
#include <windows.h>

LONG WINAPI CleanToolExceptionFun(struct _EXCEPTION_POINTERS* ExceptionInfo)
{
  printf("handle exception!\r\n");
  return EXCEPTION_EXECUTE_HANDLER;
}

int main()
{
  SetUnhandledExceptionFilter(CleanToolExceptionFun);
  int *p = 0;
  int a = *p;
  //未读取的变量在Release版会被优化掉。
  printf("%d",a);
  printf("OK\r\n");
}