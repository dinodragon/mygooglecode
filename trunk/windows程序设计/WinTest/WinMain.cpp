//
//#include <windows.h>
//
//LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam);
//
//int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
//{
//	/*TCHAR szBuffer[100];
//	wsprintf(szBuffer,TEXT("HINSTANCE: %d , HINSTANCE: %d, LPSTR: %d, nCmdShow: %d"),hInstance,hPrevInstance,lpCmdLine,nCmdShow);
//	MessageBox(NULL,szBuffer,TEXT("标题"),MB_OK);*/
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
//	wndclass.lpfnWndProc = WndProc;
//	wndclass.lpszClassName = TEXT("myProgram");
//	wndclass.lpszMenuName = NULL;
//	wndclass.style = 0;
//	RegisterClass(&wndclass);
//
//	hwnd = CreateWindow(TEXT("myProgram"),
//		TEXT("我的程序"),
//		WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT,
//		CW_USEDEFAULT,
//		CW_USEDEFAULT,
//		CW_USEDEFAULT,
//		NULL,
//		NULL,
//		hInstance,
//		NULL);
//
//	ShowWindow(hwnd,SW_SHOWNORMAL);
//	UpdateWindow(hwnd);
//
//	while( GetMessage(&msg,NULL,0,0) )
//	{
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//	return (int)msg.wParam;
//}
//
//LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
//{
//	TCHAR buf[100];
//	static int x=0,y=0,cyChar,i=0;
//	/*static int xp=0,yp=0;*/
//	HDC hdc;
//	TEXTMETRIC tm;
//	/*static MSG msg[50];
//
//	i = (++i)%50;
//	msg[i].message = message;
//	msg[i].wParam = wParam;
//	msg[i].lParam = lParam;
//
//	hdc = GetDC(hwnd) ;
//
//	int sp = 0;
//	for(int ip = 0;ip<20;ip++)
//	{
//		sp = (i-ip+50) % 50;
//		wsprintf(buf,TEXT("MSG:%d wParam:%d lParam:%d"),msg[sp].message,msg[sp].wParam,msg[sp].lParam);
//		TextOut(hdc,0,cyChar * ip,buf,lstrlen(buf)) ;
//
//	}
//
//	ReleaseDC (hwnd, hdc) ;*/
//
//	switch(message)
//	{
//	case WM_CREATE:
//		hdc = GetDC (hwnd) ;  //取得设备内容句柄
//		GetTextMetrics (hdc, &tm) ;
//		cyChar = tm.tmHeight + tm.tmExternalLeading ; //字符的总高度（包括外部间距）
//		ReleaseDC (hwnd, hdc) ;
//		return 0 ;
//
//	case WM_LBUTTONDOWN:
//		//hdc = GetDC(hwnd) ;
//		//wsprintf(buf,TEXT("鼠标左键按下! wParam:%d X:%d Y:%d"),wParam,lParam&65535,lParam>>16);
//		//TextOut(hdc,0,cyChar * (y++),buf,lstrlen(buf)) ;
//		//ReleaseDC (hwnd, hdc) ;
//		x = LOWORD(lParam);
//		y = HIWORD(lParam);
//		return 0;
//
//		/*case WM_LBUTTONUP:
//		hdc = GetDC(hwnd) ;
//		MoveToEx (hdc,x, y, NULL) ;
//		LineTo (hdc,lParam&65535,lParam>>16) ;
//		ReleaseDC (hwnd, hdc) ;
//		return 0;*/
//
//	case WM_MOUSEMOVE:
//		if(wParam == MK_LBUTTON)
//		{
//			hdc = GetDC(hwnd) ;
//			MoveToEx (hdc,x, y, NULL) ;
//			LineTo (hdc,LOWORD(lParam),HIWORD(lParam)) ;
//			//x = lParam&65535;
//			//y = lParam>>16;
//			ReleaseDC (hwnd, hdc) ;
//		}
//		return 0;
//
//	case WM_CHAR:
//		hdc = GetDC (hwnd) ;
//		//MessageBox(NULL,TEXT("您按键盘了"),TEXT("消息"),MB_OK);
//		wsprintf(buf,TEXT("MSG:%d wParam:%d lParam:%d 字母:%c"),message,wParam,lParam,wParam);
//		TextOut(hdc,0,cyChar * i++,buf,lstrlen(buf)) ;
//		ReleaseDC (hwnd, hdc) ;
//		return 0;
//		//case WM_RBUTTONDOWN:
//		//	hdc = GetDC(hwnd) ; 
//		//	wsprintf(buf,TEXT("鼠标右键按下! wParam:%d X:%d Y:%d"),wParam,lParam&65535,lParam>>16);
//		//	TextOut(hdc,0,cyChar * (y++),buf,lstrlen(buf)) ;
//		//	ReleaseDC (hwnd, hdc) ;
//		//	return 0;
//
//	case WM_CLOSE:
//		if(IDYES==MessageBox(hwnd,TEXT("是否真的结束？"),TEXT("消息"),MB_YESNO))
//		{
//			DestroyWindow(hwnd);
//		}
//		return 0 ;
//
//	case WM_DESTROY:
//		PostQuitMessage (0) ;
//		return 0 ;
//	}
//	return DefWindowProc (hwnd, message, wParam, lParam) ;
//}
