#include "header.h"

using namespace std;
void getVersion()
{
  OSVERSIONINFOEX ifo;
  ifo.dwOSVersionInfoSize=sizeof(OSVERSIONINFOEX);
  GetVersionEx((OSVERSIONINFO *)&ifo);
  TCHAR buf[100];
  swprintf_s(
    buf,
    sizeof(buf)/sizeof(TCHAR),
    TEXT("%d.%d.%d %s"),
    ifo.dwMajorVersion,
    ifo.dwMinorVersion,
    ifo.dwBuildNumber,
    ifo.szCSDVersion);
  //str.Format();
  //MessageBox(NULL,buf,TEXT("T"),MB_OK);
  wcout<<buf<<endl;
}