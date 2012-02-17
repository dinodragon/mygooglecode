#include <Windows.h>
#include <tchar.h>
#include <DbgHelp.h>
#include <stdio.h>

#pragma comment(lib, "DbgHelp.lib")

//最主要的函数, 生成Dump
static void DumpMiniDump(HANDLE hFile, PEXCEPTION_POINTERS excpInfo)
{
  if (excpInfo == NULL) //如果没有传入异常, 比如是在程序里面调用的, 生成一个异常
  {
    // Generate exception to get proper context in dump
    __try 
    {
      wprintf(_T("raising exception\r\n"));
      RaiseException(EXCEPTION_BREAKPOINT, 0, 0, NULL);
    } 
    __except(DumpMiniDump(hFile, GetExceptionInformation()),
      EXCEPTION_CONTINUE_EXECUTION) 
    {
    }
  } 
  else
  {
    wprintf(_T("writing minidump\r\n"));
    MINIDUMP_EXCEPTION_INFORMATION eInfo;
    eInfo.ThreadId = GetCurrentThreadId(); //把需要的信息添进去
    eInfo.ExceptionPointers = excpInfo;
    eInfo.ClientPointers = FALSE;
    // 调用, 生成Dump. 98不支持
    // Dump的类型是小型的, 节省空间. 可以参考MSDN生成更详细的Dump.
    MiniDumpWriteDump(
      GetCurrentProcess(),
      GetCurrentProcessId(),
      hFile,
      MiniDumpNormal,
      excpInfo ? &eInfo : NULL,
      NULL,
      NULL);
  }
}

//最下面是两个测试的函数, main_wrapper函数将调用test1, test1将会生成一个异常(非法内存写)
void test1() {
  int *p;
  p = (int*)0x100; 
  *p = 0; //写0x100地址, 这个是非法的
}

void main_wrapper(int argc, _TCHAR* argv[])
{
  test1();
}


//下面的是程序部分:
int _tmain(int argc, _TCHAR* argv[])
{
  // 创建一个Dump文件
  HANDLE hFile = CreateFile( _T("MiniDump.dmp"), GENERIC_READ | GENERIC_WRITE, 
    0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL ); 
  int code;
  __try 
  {   
    // 把自己实现的main函数包装一下, 放在try .. except 块中. 这样出现了异常可以自动生成dump
    main_wrapper(argc, argv); 
  }
  __except( code=GetExceptionCode(), DumpMiniDump(hFile, GetExceptionInformation() ),       EXCEPTION_EXECUTE_HANDLER ) //出现了异常, 记录异常的code, 生成dump!!
  {
    wprintf(_T("Exception happened. Exception code is %x \r\n"), code);
    //wchar_t msg[512];
    //wsprintf(msg, L"Exception happened. Exception code is %x", code);
    //MessageBox(NULL, msg, L"Exception", MB_OK); //显示消息给用户
  }
  CloseHandle( hFile ); //关闭Dump文件
  //getchar();
  return 0; 
}
