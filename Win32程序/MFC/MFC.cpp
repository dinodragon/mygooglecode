#include "my.h"//ԭ��Ƕ��mfc.h�ͺ�,��Ϊ��CMyWinApp�Ķ���,����...

extern CMyWinApp theApp;

CWinApp *AfxGetApp()
{
	return theApp.m_pCurrentWinApp;
}