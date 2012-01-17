/*--------------------------------------------------------------
   HelloMsg.c -- Displays "Hello, Windows 98!" in a message box
                 (c) Charles Petzold, 1998
  --------------------------------------------------------------*/

#include <windows.h>
//#include <tchar.h>   
#include <stdio.h>   


int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	int i=6;		
	TCHAR szBuffer[100] ;
	unsigned short buffer1[100];
	static TCHAR * szFormat[2] = {
               TEXT ("%13s %3d %-15s%c%6u %4d %3s %3s %4s %4s"),
               TEXT ("%-13s            0x%04X%1s%c %6u %4d %3s %3s %4s %4s")};

	/*for(i=1;i<5;i++)
	{
		wsprintf(szBuffer, TEXT("The sum of %d and %d is %d"), i, i+2, (i<<1)+2) ;
		MessageBox (NULL, szBuffer, TEXT ("HelloMsg"), 0);
	}*/

	
	wsprintf(buffer1, szFormat[0],TEXT("��һ��"), 23, TEXT("�ڶ���"),'c',234,675,TEXT("������"),TEXT("������"),TEXT("������"),TEXT("������")) ;
	MessageBox (NULL, buffer1, TEXT ("HelloMsg"), 0);
	return 0 ;
}