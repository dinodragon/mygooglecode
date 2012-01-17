/*------------------------------------------------------------------
        
    SYSMETS2.C -- System Metrics Display Program No. 2
        
            (c) Charles Petzold, 1998
        
------------------------------------------------------------------*/
        
#include <windows.h>
        
#include "sysmets.h"
        
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
        
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
        
                 PSTR szCmdLine, int iCmdShow)
        
{
        
    static TCHAR szAppName[] = TEXT ("SysMets2") ;
        
    HWND   hwnd ;
        
    MSG    msg ;
        
    WNDCLASS wndclass ;
        
    wndclass.style           = CS_HREDRAW | CS_VREDRAW ;   //horizontal:地平线,水平的.vertical:垂直的, 直立的, 顶点的, 
        
    wndclass.lpfnWndProc  = WndProc ;
        
    wndclass.cbClsExtra   = 0 ;
        
    wndclass.cbWndExtra   = 0 ;
        
    wndclass.hInstance       = hInstance ;
        
    wndclass.hIcon        = LoadIcon (NULL, IDI_APPLICATION) ;
        
    wndclass.hCursor         = LoadCursor (NULL, IDC_ARROW) ;
        
    wndclass.hbrBackground        = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
        
    wndclass.lpszMenuName         = NULL ;
        
    wndclass.lpszClassName        = szAppName ;
        

    if (!RegisterClass (&wndclass))
        
    {
        
    MessageBox (NULL, TEXT ("This program requires Windows NT!"),
        
           szAppName, MB_ICONERROR) ;
        
    return 0 ;
        
    }
        

    hwnd = CreateWindow (szAppName, TEXT ("Get System Metrics No. 2"),
        
                   WS_OVERLAPPEDWINDOW | WS_VSCROLL,  //加入垂直滚动条
        
                   CW_USEDEFAULT, CW_USEDEFAULT,
        
                   CW_USEDEFAULT, CW_USEDEFAULT,
        
                   NULL, NULL, hInstance, NULL) ;
        
    ShowWindow (hwnd, iCmdShow) ;
        
    UpdateWindow (hwnd) ;
        

    while (GetMessage (&msg, NULL, 0, 0))
        
    {
        
       TranslateMessage (&msg) ;
        
        DispatchMessage (&msg) ;
        
    }
        
    return msg.wParam;
        
}
        
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
        
{
        
    static int  cxChar, cxCaps, cyChar, cyClient, iVscrollPos ; //cyClient,显示区域的高度;
        
    HDC         hdc ;    
        
    int         i, y ;   
        
    PAINTSTRUCT ps ;
//typedef struct tagPAINTSTRUCT {
//    HDC         hdc;
//    BOOL        fErase;
//    RECT        rcPaint;
//    BOOL        fRestore;
//    BOOL        fIncUpdate;
//    BYTE        rgbReserved[32];
//} PAINTSTRUCT, *PPAINTSTRUCT, *NPPAINTSTRUCT, *LPPAINTSTRUCT;
        
    TCHAR       szBuffer[10] ;   
        
    TEXTMETRIC  tm ;     
        
    switch (message)     
        
    {
        
case WM_CREATE:
        
    hdc = GetDC (hwnd) ;
        
    GetTextMetrics (hdc, &tm) ;
        
    cxChar = tm.tmAveCharWidth ;
        
    cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2 ;
        
    cyChar = tm.tmHeight + tm.tmExternalLeading ;
        

    ReleaseDC (hwnd, hdc) ;
        
    SetScrollRange (hwnd, SB_VERT, 0, NUMLINES - 1, FALSE) ;
		//在内定情况下，滚动条的范围是从0（顶部或左部）至100（底部或右部），
		//但将范围改变为更方便于程序的数值也是很容易的：
		//SetScrollRange (hwnd, iBar, iMin, iMax, bRedraw) ;
		//参数iBar为SB_VERT或者SB_HORZ，iMin和iMax分别是范围的最小值和最大值。
		//如果想要Windows根据新范围重画滚动条，则设置bRedraw为TRUE
		//（如果在呼叫SetScrollRange后，呼叫了影响滚动条位置的其它函数，则应该将bRedraw设定为FALSE以避免过多的重画）。
    SetScrollPos   (hwnd, SB_VERT, iVscrollPos, TRUE) ;

		//您可以使用SetScrollPos在滚动条范围内设置新的卷动方块位置：
		//SetScrollPos (hwnd, iBar, iPos, bRedraw) ;
		//参数iPos是新位置，它必须在iMin至iMax的范围内。Windows提供了类似的函数
		//（GetScrollRange和GetScrollPos）来取得滚动条的目前范围和位置。
		//在程序内使用滚动条时，程序写作者与Windows共同负责维护滚动条以及更新卷动方块的位置。

		//下面是Windows对滚动条的处理：
			//处理所有滚动条鼠标事件
			//当使用者在滚动条内单击鼠标时，提供一种「反相显示」的闪烁
			//当使用者在滚动条内拖动卷动方块时，移动卷动方块
			//为包含滚动条窗口的窗口消息处理程序发送滚动条消息
		//以下是程序写作者应该完成的工作：
			//初始化滚动条的范围和位置
			//处理窗口消息处理程序的滚动条消息
			//更新滚动条内卷动方块的位置
			//更改显示区域的内容以响应对滚动条的更改

        
            return 0 ;
        

    case WM_SIZE:
        
            cyClient = HIWORD (lParam) ;
				//在窗口大小改变时，Windows给窗口消息处理程序发送一个WM_SIZE消息。
				//传给窗口消息处理程序的lParam参数的  低字组中包含显示区域的宽度，高字组中包含显示区域的高度。
				//与cxChar和cyChar相似，这两个变量在窗口消息处理程序内定义为静态变量，因为在以后处理其它消息时会用到它们。
				//处理WM_SIZE的方法如下：
				//caseWM_SIZE:
				//   cxClient = LOWORD (lParam) ;
				//   cyClient = HIWORD (lParam) ;
				//   return 0 ;
				//        
				//实际上您会在每个Windows程序中看到类似的程序代码。LOWORD和HIWORD宏在Windows表头文件WINDEF.H中定义。
				//	这些宏的定义看起来像这样：
				//#define LOWORD(l) ((WORD)(l))
				//#define HIWORD(l) ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
				//这两个宏传回WORD值（16位的无正负号整数，范围从0到0xFFFF）。
				//一般，将这些值保存在32位有号整数中。这就不会牵扯到任何转换问题，
				//并使得这些值在以后需要的任何计算中易于使用。
            return 0 ;
        

    case WM_VSCROLL:
        
            switch (LOWORD (wParam))
        
         {
        
    case SB_LINEUP:
        
          iVscrollPos -= 1 ;
        
            break ;
        
   
        
    case SB_LINEDOWN:
        
            iVscrollPos += 1 ;
        
            break ;
        

    case SB_PAGEUP:
        
            iVscrollPos -= cyClient / cyChar ;
        
            break ;
        
   
        
    case SB_PAGEDOWN:
        
            iVscrollPos += cyClient / cyChar ;
        
            break ;
        
   
        
    case SB_THUMBPOSITION:
        
            iVscrollPos = HIWORD (wParam) ;
        
            break ;
        
   
        
    default :
        
            break ;
        
         }
        

    iVscrollPos = max (0, min (iVscrollPos, NUMLINES - 1)) ;
        
    if (iVscrollPos != GetScrollPos (hwnd, SB_VERT))
        
         {
        
            SetScrollPos (hwnd, SB_VERT, iVscrollPos, TRUE) ;
        
            InvalidateRect (hwnd, NULL, TRUE) ;
        
         }
        
            return 0 ;
        
    case WM_PAINT:
        
            hdc = BeginPaint (hwnd, &ps) ;
        
            for (i = 0 ; i < NUMLINES ; i++)
        
            {
        
                   y = cyChar * (i - iVscrollPos) ;
        
                   TextOut (hdc, 0, y,
        
                           sysmetrics[i].szLabel,
        
                           lstrlen (sysmetrics[i].szLabel)) ;
        
   
        
                   TextOut (hdc, 22 * cxCaps, y,
        
                           sysmetrics[i].szDesc,
        
                           lstrlen (sysmetrics[i].szDesc)) ;
        
   
        
                   SetTextAlign (hdc, TA_RIGHT | TA_TOP) ;
        
                   TextOut (hdc, 22 * cxCaps + 40 * cxChar, y, szBuffer,
        
                           wsprintf (szBuffer, TEXT ("%5d"),
        
                                          GetSystemMetrics (sysmetrics[i].iIndex))) ;
        
                   SetTextAlign (hdc, TA_LEFT | TA_TOP) ;
        
        }
        
            EndPaint (hwnd, &ps) ;
        
            return 0 ;
        

    case WM_DESTROY:
        
            PostQuitMessage (0) ;
        
            return 0 ;
        
    }
        
    return DefWindowProc (hwnd, message, wParam, lParam) ;
        
}
