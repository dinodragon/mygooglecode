#include <stdio.h>
#include <Windows.h>

BOOL OnputCreateProcess(char cmdline[128],char outputfilename[256])
{
  BOOL brunsucc = FALSE;

  SECURITY_ATTRIBUTES SecAtrrs={0};
  SecAtrrs.nLength=sizeof(SecAtrrs);
  SecAtrrs.lpSecurityDescriptor=NULL;
  SecAtrrs.bInheritHandle=TRUE;

  HANDLE houtputFile = CreateFile(outputfilename,
    GENERIC_READ|GENERIC_WRITE, 
    FILE_SHARE_READ|FILE_SHARE_WRITE,
    &SecAtrrs,
    OPEN_ALWAYS,
    FILE_ATTRIBUTE_NORMAL| FILE_FLAG_WRITE_THROUGH,
    NULL);
  if (houtputFile != INVALID_HANDLE_VALUE)
  {
    PROCESS_INFORMATION   process; 
    STARTUPINFO   startupInfo={0};   
    startupInfo.cb=sizeof(STARTUPINFO);
    startupInfo.dwFlags=STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    startupInfo.wShowWindow =SW_HIDE;
    startupInfo.hStdOutput=houtputFile;
    startupInfo.lpReserved=NULL;   
    startupInfo.lpReserved2=NULL;   
    startupInfo.lpDesktop=NULL;   

    BOOL bcrtps=CreateProcess(NULL,
      cmdline,
      NULL,
      NULL,
      TRUE,
      NORMAL_PRIORITY_CLASS,
      NULL,
      NULL,
      &startupInfo,&process);
    if (bcrtps)
    {     
      if (WaitForSingleObject(process.hProcess, INFINITE) == WAIT_FAILED)
      {
        CloseHandle(process.hThread);   
        CloseHandle(process.hProcess);      
      }
      else
      {
        CloseHandle(process.hThread);   
        CloseHandle(process.hProcess);      
        brunsucc = TRUE;
      }
    }
  } 
  CloseHandle(houtputFile);

  return brunsucc;
}

int GetCurrDirectory(char * pDirectory)
{
  char szFilename[256];
  ::GetModuleFileName(NULL, szFilename, 255);

  char drive[_MAX_DRIVE];
  char dir[_MAX_DIR];
  char fname1[_MAX_FNAME];
  char ext[_MAX_EXT];

  _splitpath( szFilename, drive, dir, fname1, ext );

  strcpy(pDirectory,drive);
  strcat(pDirectory,dir);

  return 1; 
}

int main(int argc, char* argv[])
{
  char cmdline[128]={0};
  strcpy(cmdline,"arp -a");

  char filepath[256]={0};
  GetCurrDirectory(filepath);

  char wfsqlname[256]={0};
  strcpy(wfsqlname,filepath);
  strcat(wfsqlname,"temp.log");

  OnputCreateProcess(cmdline,wfsqlname);
  printf("Hello World!/n");
  return 0;
}

