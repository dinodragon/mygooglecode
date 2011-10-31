#include "header.h"

void systemInfo()
{
  SYSTEM_INFO siSysInfo;

  // Copy the hardware information to the SYSTEM_INFO structure. 

  GetSystemInfo(&siSysInfo); 

  // Display the contents of the SYSTEM_INFO structure. 

  printf("Hardware information: \n");  
  printf("  OEM ID: %u\n", siSysInfo.dwOemId);
  printf("  Number of processors: %u\n", 
    siSysInfo.dwNumberOfProcessors); 
  printf("  Page size: %u\n", siSysInfo.dwPageSize); 
  printf("  Processor type: %u\n", siSysInfo.dwProcessorType); 
  printf("  Minimum application address: %l x\n", 
    siSysInfo.lpMinimumApplicationAddress); 
  printf("  Maximum application address: %l x\n", 
    siSysInfo.lpMaximumApplicationAddress); 
  printf("  Active processor mask: %u\n", 
    siSysInfo.dwActiveProcessorMask); 
}