#include "header.h"
#include <WinVer.h>
#include <Windows.h>
#include <stdio.h>
#include <TCHAR.h>

#pragma comment(lib,"Version.lib")

int ieInfo(void)
{

  TCHAR szFilename[] = _T("mshtml.dll");  
  DWORD dwMajorVersion =0, dwMinorVersion = 0;  
  DWORD dwBuildNumber =0, dwRevisionNumber = 0;  
  DWORD dwHandle = 0;  
  DWORD dwVerInfoSize = GetFileVersionInfoSize(szFilename, &dwHandle);  

  if (dwVerInfoSize)  
  {  
    LPVOID lpBuffer = LocalAlloc(LPTR, dwVerInfoSize);  
    if (lpBuffer)  
    {  
      if (GetFileVersionInfo(szFilename, dwHandle, dwVerInfoSize, lpBuffer))  
      {  
        VS_FIXEDFILEINFO * lpFixedFileInfo = NULL;  
        UINT nFixedFileInfoSize = 0;  
        if (VerQueryValue(lpBuffer, TEXT("\\"), (LPVOID*)&lpFixedFileInfo, &nFixedFileInfoSize) &&(nFixedFileInfoSize))  
        {  
          dwMajorVersion = HIWORD(lpFixedFileInfo->dwFileVersionMS);    
          dwMinorVersion = LOWORD(lpFixedFileInfo->dwFileVersionMS);    
          dwBuildNumber = HIWORD(lpFixedFileInfo->dwFileVersionLS);    
          dwRevisionNumber = LOWORD(lpFixedFileInfo->dwFileVersionLS);  
        }  
      }  
      LocalFree(lpBuffer);  
    }  
  }  
  printf("mshtml.dll VersionInfo: \n\tMajorVersion=%d\n\tMinorVersion=%d\n\tBuildNumber=%d\n\tRevisionNumber=%d\n",  
    dwMajorVersion, dwMinorVersion, dwBuildNumber, dwRevisionNumber);  
  return 0;
}

