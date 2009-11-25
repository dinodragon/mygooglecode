//#include <windows.h>
//
//struct
//{
//	int iStyle ;
//	TCHAR *szText ;
//}
//button[] =
//{
//	BS_PUSHBUTTON, TEXT("PUSHBUTTON"),
//	BS_DEFPUSHBUTTON, TEXT("DEFPUSHBUTTON"),
//	BS_CHECKBOX, TEXT("CHECKBOX"),
//	BS_AUTOCHECKBOX, TEXT ("AUTOCHECKBOX"),
//	BS_RADIOBUTTON,TEXT ("RADIOBUTTON"),
//	BS_3STATE,TEXT("3STATE"),
//	BS_AUTO3STATE, TEXT("AUTO3STATE"),
//	BS_GROUPBOX, TEXT ("GROUPBOX"),
//	BS_AUTORADIOBUTTON, TEXT("AUTORADIO"),
//	BS_OWNERDRAW,TEXT ("OWNERDRAW")
//};
//
//HINSTANCE ghInstance;
//
//#define NUM sizeof(button)/sizeof(button[0])
//
//LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
//
//int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
//{
//	static TCHAR szAppName[] = TEXT("MenuTest");
//	HWND hwnd;
//	MSG msg;
//
//	WNDCLASS wndclass;
//	wndclass.cbClsExtra = 0;
//	wndclass.cbWndExtra = 0;
//	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
//	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
//	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
//	wndclass.hInstance = hInstance;
//	wndclass.lpfnWndProc = WindowProc;
//	wndclass.lpszClassName = szAppName;
//	wndclass.lpszMenuName = NULL;
//	wndclass.style = CS_HREDRAW | CS_VREDRAW;
//	
//	ghInstance = hInstance;
//
//	if(!RegisterClass(&wndclass))
//	{
//		MessageBox(NULL,TEXT("要求Windows NT!"),szAppName,MB_ICONERROR);
//		return 0;
//	}
//
//	hwnd = CreateWindow(szAppName,
//						TEXT("按扭控件"),
//						WS_OVERLAPPEDWINDOW,
//						CW_USEDEFAULT,
//						CW_USEDEFAULT,
//						CW_USEDEFAULT,
//						CW_USEDEFAULT,
//						NULL,
//						NULL,
//						hInstance,
//						NULL
//						);
//
//	ShowWindow(hwnd,nShowCmd);
//	UpdateWindow(hwnd);
//
//	while(GetMessage(&msg,NULL,0,0))
//	{
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//
//	return (int)msg.wParam;
//}
//
//LRESULT CALLBACK WindowProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
//{
//	static HWND hButtonWnd[NUM];
//	int y=0,i;
//    static int cxChar, cyChar ;
//	HDC hdc;
//	TCHAR buf[100];
//
//	switch(message)
//	{
//		case WM_CREATE:
//			cxChar = LOWORD (GetDialogBaseUnits ()) ;
//			cyChar = HIWORD (GetDialogBaseUnits ()) ;
//
//			for(i = 0;i<NUM;i++)
//				hButtonWnd[i] = CreateWindow(TEXT("button"),button[i].szText,WS_CHILD|WS_VISIBLE|button[i].iStyle,
//				20,y += 40,150,30,hwnd,(HMENU)i,ghInstance,NULL);
//			return 0;
//
//		case WM_LBUTTONDOWN:
//			MessageBox(NULL,TEXT("左键按下!"),TEXT("消息"),MB_OK);
//			return 0;
//
//		case WM_DRAWITEM :
//			hdc = GetDC(hwnd);
//			TextOut(hdc,200,cyChar += 20,buf,wsprintf(buf,TEXT("DrawItem,Msg:%d wParam:%d lParam:%d"),message,wParam,lParam));
//			ReleaseDC(hwnd,hdc);
//			return 0;
//
//		case WM_COMMAND:
//			hdc = GetDC(hwnd);
//			TextOut(hdc,200,cyChar += 20,buf,wsprintf(buf,TEXT("WM_COMMAND,Msg:%d wParam:%d lParam:%d"),message,wParam,lParam));
//			ReleaseDC(hwnd,hdc);
//			return 0;
//
//		case WM_CLOSE:
//			if(IDYES==MessageBox(hwnd,TEXT("是否真的结束？"),TEXT("消息"),MB_YESNO))
//			{
//				DestroyWindow(hwnd);
//			}
//			return 0 ;
//		case WM_DESTROY:
//			PostQuitMessage(0);
//			return 0;
//	}
//	return DefWindowProc(hwnd,message,wParam,lParam);
//}
