#include "header.h"

VOID GetMemInfo()
{
  CHAR pBuf[100]; 
  MEMORYSTATUSEX        Meminfo;
  memset(&Meminfo, 0, sizeof(Meminfo));
  Meminfo.dwLength = sizeof(Meminfo);
  BOOL result = GlobalMemoryStatusEx(&Meminfo);
  if (result)
  {
    double dSize;
    dSize = (double)Meminfo.ullTotalPhys;
    dSize /= 1024.0;
    dSize /= 1024.0;
    dSize += 0.5;
    sprintf(pBuf, "%.0f", dSize);
    printf("Mem:%s\r\n",pBuf);
  }
}

