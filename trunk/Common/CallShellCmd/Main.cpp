#include <iostream>
#include "windows.h"

void main()
{
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  ZeroMemory( &si, sizeof(si) );
  si.cb = sizeof(si);
  ZeroMemory( &pi, sizeof(pi) );
  TCHAR cmdline[80] = TEXT("MyChildProcess");
  // Start the child process. 
  if( !CreateProcess(TEXT("C:\\Windows\\System32\\notepad.exe"),   // No module name (use command line). 
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
  CloseHandle( pi.hProcess );
  CloseHandle( pi.hThread );
  return;
}