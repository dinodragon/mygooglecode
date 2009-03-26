#include "my.h"//原该嵌入mfc.h就好,但为了CMyWinApp的定义,所以...

extern CMyWinApp theApp;

CWinApp *AfxGetApp()
{
	return theApp.m_pCurrentWinApp;
}