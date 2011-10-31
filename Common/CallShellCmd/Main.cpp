#include <stdio.h>
#include <Windows.h>

BOOL OnputCreateProcess(char cmdline[128],char outputfilename[256])
{
  BOOL brunsucc = FALSE;

  HANDLE hStream = CreateFile( "testfile:stream",
    GENERIC_READ|GENERIC_WRITE,
    FILE_SHARE_READ|FILE_SHARE_WRITE,
    NULL,
    OPEN_ALWAYS,
    FILE_ATTRIBUTE_NORMAL| FILE_FLAG_WRITE_THROUGH,
    NULL);
  if( hStream == INVALID_HANDLE_VALUE )
    printf( "Cannot open testfile:stream\n" );

  PROCESS_INFORMATION   process; 
  STARTUPINFO   startupInfo={0};   
  startupInfo.cb=sizeof(STARTUPINFO);
  startupInfo.dwFlags=STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
  startupInfo.wShowWindow =SW_HIDE;
  startupInfo.hStdOutput=hStream;
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
    if (!WaitForSingleObject(process.hProcess, INFINITE) == WAIT_FAILED)
    {
      brunsucc = TRUE;
    }
    CloseHandle(process.hThread);   
    CloseHandle(process.hProcess);      
  }

  TCHAR buf[2000];
  DWORD bytes;
  ReadFile(hStream,buf,sizeof(buf)/sizeof(TCHAR),&bytes,NULL);
  buf[bytes] = '\0';
  printf("%s:\r\n%s\r\n",cmdline,buf);
  CloseHandle(hStream);
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
  strcpy(cmdline,"dir www.renren.com");

  char filepath[256]={0};
  GetCurrDirectory(filepath);

  char wfsqlname[256]={0};
  strcpy(wfsqlname,filepath);
  strcat(wfsqlname,"temp.log");
  strcpy(wfsqlname,"D:\\log.txt");
  OnputCreateProcess(cmdline,wfsqlname);
  printf("Hello World!/n");
  return 0;
}

