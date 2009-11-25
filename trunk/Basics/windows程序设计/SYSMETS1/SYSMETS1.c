/*------------------------------------------------------------------
        
SYSMETS1.C -- System Metrics Display Program No. 1
        
                 (c) Charles Petzold, 1998
        
----------------------------------------------------------------*/
        
#include <windows.h>
        
#include "sysmets.h"
        
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
        
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT ("SysMets1") ;
    HWND hwnd;
    MSG msg;

    WNDCLASS wndclass ;
	wndclass.style	= CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc = WndProc ;
	wndclass.cbClsExtra = 0 ;
	wndclass.cbWndExtra = 0 ;
	wndclass.hInstance = hInstance ;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION) ;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW) ;
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
	wndclass.lpszMenuName = NULL ;
	wndclass.lpszClassName = szAppName ;

	if (!RegisterClass (&wndclass))
    {
		MessageBox(NULL, TEXT ("This program requires Windows NT!"),szAppName, MB_ICONERROR);
		return 0 ;
    }
        
    hwnd = CreateWindow(szAppName,
						TEXT ("Get System Metrics No. 1"),
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						NULL,
						NULL,
						hInstance,
						NULL) ;

	ShowWindow (hwnd, iCmdShow);
	UpdateWindow (hwnd) ;
        
    while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam ;
}
        

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int cxChar, cxCaps, cyChar ;
	HDC hdc ;
	int i ;
	PAINTSTRUCT ps ;     
	TCHAR szBuffer[10];
    TEXTMETRIC  tm ;
	/*
	typedef struct tagTEXTMETRIC  //metric:米制的,公制的,度量：衡量标准
	{
		LONG tmHeight ;
		LONG tmAscent ;  //Ascent:上升
		LONG tmDescent ;
		LONG tmInternalLeading ;
		LONG tmExternalLeading ;
		LONG tmAveCharWidth ;
		LONG tmMaxCharWidth ;
		其它结构字段
	}TEXTMETRIC, * PTEXTMETRIC ;
	*/
    switch (message)
    {
		case WM_CREATE:
			hdc = GetDC (hwnd) ;  //取得设备内容句柄
			GetTextMetrics (hdc, &tm) ;
			cxChar = tm.tmAveCharWidth ;  //平均字符宽度
			cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2 ;  //大写字母的平均宽度,约为cxChar乘以150％,
															//对于可变宽度字体，TEXTMETRIC结构中的tmPitchAndFamily字段的低位为1，
															/*对于固定宽度字体，该值为0。 SYSMETS1使用这个位从cxChar计算cxCaps*/
			cyChar = tm.tmHeight + tm.tmExternalLeading ; //字符的总高度（包括外部间距）
			ReleaseDC (hwnd, hdc) ;
			return 0 ;
		case WM_PAINT :
			hdc = BeginPaint (hwnd, &ps) ;
			for (i = 0 ; i < NUMLINES ; i++)
			{
				/*TextOut (hdc,  //设备内容句柄，它既可以是GetDC的传回值，也可以是在处理WM_PAINT消息时BeginPaint的传回值。
									设备内容的属性控制了被显示的字符串的特征。例如，设备内容中有一个属性指定文字颜色，内定颜色为黑色；内定设备内容还定义了白色的背景。在程序向显示器输出文字时，Windows使用这个背景色来填入字符周围的矩形空间（称为「字符框」）。
							x,	//x和y定义显示区域内字符串的开始位置，x是水平位置，y是垂直位置。
									字符串中第一个字符的左上角位于坐标点(x,y)。在内定的设备内容中，原点（x和y均为0的点）是显示区域的左上角。
									如果在TextOut中将x和y设为0，则将从显示区域左上角开始输出字符串。
							y,
							psText, //指向字符串的指针
							iLength) ; //字符串的长度 如果psText指向Unicode字符串，则字符串中的字节数就是iLength值的两倍。
				*/
				/*
				struct
				{
					 int     iIndex ;
					 TCHAR * szLabel ;
					 TCHAR * szDesc ;
				}
				sysmetrics []
				*/
				TextOut(hdc,0,cyChar * i,sysmetrics[i].szLabel,lstrlen (sysmetrics[i].szLabel)) ;
				TextOut(hdc,22 * cxCaps, //第一列显示的最长的大写标识符有20个字符，因此第二列必须在第一列文字开头向右20 × cxCaps处开始。我使用22，以在两列之间加一点多余的空间。
						cyChar * i,sysmetrics[i].szDesc,lstrlen (sysmetrics[i].szDesc)) ;
				//变宽字体使得格式化向右对齐的数值有些棘手。从0到9的数字具有相同的宽度，但是这个宽度比空格宽度大。数值可以比一个数字宽，所以不同的数值应该从不同的横向位置开始。
				//那么，如果我们指定字符串结束的图素位置，而不是指定字符串的开始位置，以此向右对齐数值，是否会容易一些呢？用SetTextAlign函数就可以做到这一点。在SYSMETS1呼叫：
				//SetTextAlign (hdc, TA_RIGHT | TA_TOP) ;
				//之后，传给后续TextOut函数的坐标将指定字符串的右上角，而不是左上角。
				//显示列数的TextOut函数的第二个参数设定为：
				//22 * cxCaps + 40 * cxChar
				//值40*cxChar包含了第二列的宽度和第三列的宽度。在TextOut函数之后，另一个对SetTextAlign的呼叫将对齐方式设定回普通方式，以进行下次循环。
				SetTextAlign (hdc, TA_RIGHT | TA_TOP) ;
				TextOut (hdc, 22 * cxCaps + 40 * cxChar, cyChar * i,szBuffer,wsprintf (szBuffer, TEXT ("%5d"),i,GetSystemMetrics (sysmetrics[i].iIndex))) ;
				SetTextAlign (hdc, TA_LEFT | TA_TOP) ;
			}
            EndPaint (hwnd, &ps) ;
            return 0 ;
		case WM_DESTROY :
			//MessageBox(NULL, TEXT ("真的要退出?"),TEXT("程序"), 3);
			PostQuitMessage (0) ;
			return 0 ;
	}
	
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}
