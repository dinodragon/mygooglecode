#include "header.h"

void GetCPUInfo(int cpuinfo[4], int tp)
{
  __asm
  {
    mov eax, tp
      cpuid
      mov edi, cpuinfo
      mov dword ptr [edi], eax
      mov dword ptr [edi+4], ebx
      mov dword ptr [edi+8], ecx
      mov dword ptr [edi+12], edx
  }
}

void ShowCPUInfo()
{
  char cpuName[64] = {0};
  int (*pTmp)[4] = (int(*)[4])cpuName;

  GetCPUInfo(*pTmp++, 0x80000002);
  GetCPUInfo(*pTmp++, 0x80000003);
  GetCPUInfo(*pTmp++, 0x80000004);
  printf("%s\n", cpuName);
}

