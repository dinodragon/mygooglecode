#include <iostream>
#include "windows.h"

void main()
{
  SECURITY_ATTRIBUTES SecAtrrs={0};
  SecAtrrs.nLength=sizeof(SecAtrrs);
  SecAtrrs.lpSecurityDescriptor=NULL;
  SecAtrrs.bInheritHandle=TRUE;


  HANDLE houtputFile = CreateFile(TEXT("D:\\out.txt"),
    GENERIC_READ|GENERIC_WRITE, 
    FILE_SHARE_READ|FILE_SHARE_WRITE,
    &SecAtrrs,
    OPEN_ALWAYS,
    FILE_ATTRIBUTE_NORMAL| FILE_FLAG_WRITE_THROUGH,
    NULL);
  if (houtputFile == INVALID_HANDLE_VALUE)
    return ;


  STARTUPINFO si;
  ZeroMemory( &si, sizeof(si) );
  si.cb=sizeof(STARTUPINFO);
  si.dwFlags=STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
  si.wShowWindow =SW_HIDE;
  si.hStdOutput=houtputFile;
  si.lpReserved=NULL;   
  si.lpReserved2=NULL;   
  si.lpDesktop=NULL;   

  PROCESS_INFORMATION pi;
  ZeroMemory( &pi, sizeof(pi) );
  TCHAR cmdline[80] = TEXT("cmd.exe dir");
  // Start the child process. 
  if( !CreateProcess(NULL,   // No module name (use command line). 
    cmdline, // Command line. 
    NULL,             // Process handle not inheritable. 
    NULL,             // Thread handle not inheritable. 
    FALSE,            // Set handle inheritance to FALSE. 
    0,                // No creation flags. 
    NULL,             // Use parent's environment block. 
    NULL,             // Use parent's starting directory. 
    &si,              // Pointer to STARTUPINFO structure.
    &pi )             // Pointer to PROCESS_INFORMATION structure.
    ) 
  {
    printf( "CreateProcess failed (%d).\n", GetLastError() );
    return;
  }
  // Wait until child process exits.
  WaitForSingleObject( pi.hProcess, INFINITE );
  // Close process and thread handles. 
  CloseHandle(houtputFile);
  CloseHandle( pi.hProcess );
  CloseHandle( pi.hThread );
  return;
}