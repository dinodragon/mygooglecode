/*----------------------------------------
COLORS1.C -- Colors Using Scroll Bars
(c) Charles Petzold, 1998
----------------------------------------*/

#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM) ;
BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT message,WPARAM wParam, LPARAM lParam);

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT ("Colors1") ;
	HWND         hwnd ;
	MSG          msg ;
	WNDCLASS     wndclass ;

	wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc   = WndProc ;
	wndclass.cbClsExtra    = 0 ;
	wndclass.cbWndExtra    = 0 ;
	wndclass.hInstance     = hInstance ;
	wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hbrBackground = CreateSolidBrush (RGB(100,000,255)) ;
	wndclass.lpszMenuName  = NULL ;
	wndclass.lpszClassName = szAppName ;

	if (!RegisterClass (&wndclass))
	{
		MessageBox (NULL, TEXT ("This program requires Windows NT!"),
			szAppName, MB_ICONERROR) ;
		return 0 ;
	}

	hwnd = CreateWindow (szAppName, TEXT ("Color Scroll"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL) ;

	ShowWindow (hwnd, iCmdShow) ;
	UpdateWindow (hwnd) ;

	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg) ;
		DispatchMessage  (&msg) ;
	}
	return msg.wParam ;
}


LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	static HINSTANCE hInstance ;
	static HWND ScrollWnd,EditWnd;
	static HWND hwndValue;
	int i=100;
	static RECT rect;
	TCHAR buffer[100];
	HMENU hMenu;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE :
		hInstance = (HINSTANCE) GetWindowLong (hwnd, GWL_HINSTANCE) ;
		hwndValue = CreateWindow (TEXT ("static"), NULL,
			WS_CHILD | WS_VISIBLE | SS_CENTER,
			400, 0, 100, 400,
			hwnd, (HMENU) 9, hInstance, NULL) ;

		ScrollWnd=CreateWindow (TEXT ("Scrollbar"), NULL,
			WS_CHILD | WS_VISIBLE | 
			WS_TABSTOP | SBS_VERT,
			200, 0, 100, 400, 
			hwnd, (HMENU) 7, hInstance, NULL) ;

		EditWnd = CreateWindow (TEXT ("edit"), NULL,
			WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL |
			WS_BORDER | ES_LEFT | ES_MULTILINE |
			ES_AUTOHSCROLL | ES_AUTOVSCROLL,
			20, 20, 100,500, hwnd, (HMENU)1,
			((LPCREATESTRUCT) lParam) -> hInstance, NULL) ;

		GetWindowRect(hwnd,&rect);

		SetScrollRange(ScrollWnd, SB_CTL, 0, 255, FALSE) ;
		SetScrollPos(ScrollWnd, SB_CTL, 100, FALSE) ;
		i = GetWindowLong (ScrollWnd, GWL_ID) ;

		hMenu = LoadMenu (hInstance, MAKEINTRESOURCE (IDR_MENU1)) ;
		SetMenu(hwnd,hMenu);
		return 0;

	case WM_VSCROLL :
		i = GetWindowLong ((HWND) lParam, GWL_ID);
		wsprintf(buffer,TEXT("i = %d"),i);
		//MessageBox(hwnd,buffer,TEXT("i"),MB_OK);

		return 0;

	case WM_COMMAND:
		hMenu = GetMenu (hwnd) ;
		switch(LOWORD(wParam))
		{
			case ID_40001:
				MessageBox(hwnd,TEXT("新建"),TEXT("菜单"),MB_OK);
				CheckMenuItem (hMenu, ID_40001, MF_CHECKED) ;
				EnableMenuItem(hMenu, ID_40002, MF_GRAYED) ; 
				return 0;
			case ID_40005:
				//MessageBox(hwnd,TEXT("打开"),TEXT("菜单"),MB_OK);
				DialogBox (hInstance,TEXT ("ABOUTBOX"),hwnd,AboutDlgProc) ;
				return 0;

			case ID_40006:
				//MessageBox(hwnd,TEXT("打开"),TEXT("菜单"),MB_OK);
				DialogBox (hInstance,TEXT ("IDD_DIALOG6"),hwnd,AboutDlgProc) ;
				return 0;

			case ID_40007:
				hdc = GetDC(hwnd);
				InvalidateRect(hwnd,&rect,TRUE);
				ReleaseDC(hwnd,hdc);
				return 0;

			case ID_DESTROY:
				DestroyWindow(hwnd);
				return 0;
		
		}

		return 0;


	case WM_LBUTTONDOWN:
		//i = SendMessage (EditWnd, EM_GETLINECOUNT, 0, 0) ;
		//DialogBox(hInstance,TEXT("ABOUTBOX"),hwnd,AboutDlgProc) ;
		//wsprintf(buffer,TEXT("i = %d"),i);
		//SetWindowText (hwndValue, buffer) ;

		hdc = GetDC(hwnd);
		TextOut(hdc,500,90,TEXT("文本输出"),4);
		ReleaseDC(hwnd,hdc);

		GetWindowText(EditWnd,buffer,100);
		//MessageBox(hwnd,buffer,TEXT("文本内容"),MB_OK);
		//i = 3;
		return 0;

		/*case WM_SETFOCUS :
		MessageBox(NULL,TEXT("获得焦点!"),TEXT("SETFOCUS"),MB_OK);
		return 0;*/

	case WM_DESTROY :
		PostQuitMessage (0) ;
		return 0 ;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}

BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT message,WPARAM wParam, LPARAM lParam)
        
{
        
           switch (message)
        
           {
        
           case   WM_INITDIALOG :
        
                  return TRUE ;
        
        
        
           case   WM_COMMAND :
        
                  switch (LOWORD (wParam))
        
                  {
        
                  case   IDOK :
        
                  case   IDCANCEL :
        
                                         EndDialog (hDlg, 0) ;
        
                                         return TRUE ;
        
         }
        
                  break ;
        
    }
        
  return TRUE ;
        
}
