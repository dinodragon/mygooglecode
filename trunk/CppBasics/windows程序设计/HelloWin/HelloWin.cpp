/*------------------------------------------------------------
   HELLOWIN.C -- Displays "Hello, Windows 98!" in client area
                 (c) Charles Petzold, 1998
 在选项-属性-配置属性-链接器-输入-附加依赖项：WINMM.LIB（Windows multimedia－Windows多媒体）。
  ------------------------------------------------------------*/

#include <windows.h>
//#include <mmsystem.h>
/*
窗口消息处理程序总是定义为如下形式：
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
*/
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, //应用程序当前实例句柄
					HINSTANCE hPrevInstance, //应用程序其他实例句柄
					PSTR szCmdLine,  //指向程序命令行参数的指针
					int iCmdShow)  //应用程序开始执行时窗口显示方式的整数值
{
     static TCHAR szAppName[] = TEXT ("HelloWin") ;
     HWND         hwnd ;
     MSG          msg ;
 /*
 型态MSG在WINUSER.H中定义如下：
 typedef struct tagMSG
{
	HWND   hwnd ;hwnd 接收消息的窗口句柄。在HELLOWIN程序中，这一参数与CreateWindow传回的hwnd值相同，因为这是该程序拥有的唯一窗口。
	UINT   message ;消息标识符。这是一个数值，用以标识消息。对于每个消息，均有一个对应的标识符，这些标识符定义于Windows表头文件（其中大多数在WINUSER.H中），以前缀WM（「window message」，窗口消息）开头。例如，使用者将鼠标光标放在HELLOWIN显示区域之内，并按下鼠标左按钮，Windows就在消息队列中放入一个消息，该消息的message字段等于WM_LBUTTONDOWN。这是一个常数，其值为0x0201。
	WPARAM wParam ; 一个32位的「message parameter（消息参数）」，其含义和数值根据消息的不同而不同。
	LPARAM lParam ;lParam 一个32位的消息参数，其值与消息有关。
	DWORD  time ; 消息放入消息队列中的时间。
	POINT  pt ; 消息放入消息队列时的鼠标坐标。
				POINT数据型态也是一个结构，它在WINDEF.H中定义如下：
				typedef struct tagPOINT
				{
					LONG  x ;
					LONG  y ;
				}
				POINT, * PPOINT;
}
MSG, * PMSG ;
 */
     WNDCLASS     wndclass ;

     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = szAppName ;

     if (!RegisterClass (&wndclass))
     {
          MessageBox (NULL, TEXT ("This program requires Windows NT!"), 
                      szAppName, MB_ICONERROR) ;
          return 0 ;
     }
     
     hwnd = CreateWindow (szAppName,                  // window class name
                          TEXT ("The Hello Program"), // window caption
                          WS_OVERLAPPEDWINDOW,        // window style
                          CW_USEDEFAULT,              // initial x position
                          CW_USEDEFAULT,              // initial y position
                          CW_USEDEFAULT,              // initial x size
                          CW_USEDEFAULT,              // initial y size
                          NULL,                       // parent window handle
                          NULL,                       // window menu handle
                          hInstance,                  // program instance handle
                          NULL) ;                     // creation parameters
     
     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;
     
     while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return msg.wParam;
	 /*
		return msg.wParam ;
		结构的wParam字段是传递给PostQuitMessage函数的值（通常是0）。
		然后return叙述将退出WinMain并终止程序。
	 */
}

LRESULT CALLBACK WndProc (HWND hwnd, //窗口句柄
						  UINT message, //代表所处理消息的消息值
						  WPARAM wParam, //消息的附加参数
						  LPARAM lParam) //消息的附加参数
{
     HDC         hdc ;
     PAINTSTRUCT ps ;
     RECT        rect ;
     
     switch (message)
     {
     case WM_CREATE:
          PlaySound (TEXT ("hellowin.wav"), NULL, SND_FILENAME | SND_ASYNC) ;
          return 0 ;
          
     case WM_PAINT:
		 /*
			对WM_PAINT的处理几乎总是从一个BeginPaint呼叫开始：
			hdc = BeginPaint (hwnd, &ps) ;
			而以一个EndPaint呼叫结束：
			EndPaint (hwnd, &ps) ;
			在这两个呼叫中，第一个参数都是程序的窗口句柄，第二个参数是指向型态为PAINTSTRUCT的结构指针。PAINTSTRUCT结构中包含一些窗口消息处理程序，可以用来更新显示区域的内容。我们将在下一章中讨论该结构的各个字段。现在我们只在BeginPaint和EndPaint函数中用到它。
		 */
          hdc = BeginPaint (hwnd, &ps) ;
          GetClientRect (hwnd, &rect) ;
		  /*
			第一个参数是程序窗口的句柄。第二个参数是一个指标，指向一个RECT型态的rectangle结构。
			该结构有四个LONG字段，分别为left、top、right和bottom。
			GetClientRect将这四个字段设定为窗口显示区域的尺寸。
			left和top字段通常设定为0，right和bottom字段设定为显示区域的宽度和高度（像素点数）。
		  */
          DrawText (hdc, TEXT ("Hello, Windows 98!"), -1, &rect,DT_SINGLELINE | DT_CENTER | DT_VCENTER) ;
		  /*
			DrawText可以输出文字（正如其名字所表明的一样）。
			由于该函数要输出文字，第一个参数是从BeginPaint传回的设备内容句柄，第二个参数是要输出的文字，
			第三个参数是 -1，指示字符串是以字节0终结的。
			DrawText最后一个参数是一系列位旗标，它们均在WINUSER.H中定义（虽然由于其显示输出的效果，
			使得DrawText像一个GDI函数呼叫，但它确实因为相当高级的画图功能而成为User模块的一部分。
			此函数在/Platform SDK/Graphics and Multimedia Services/GDI/Fonts and Text中说明）。
			旗标指示了文字必须显示在一行上，水平方向和垂直方向都位于第四个参数指定的矩形中央。
			因此，这个函数呼叫将让字符串「Hello, Windows 98!」显示在显示区域的中央。
		  */
          EndPaint (hwnd, &ps) ;
          return 0 ;
          
     case WM_DESTROY:
		 /*
			HELLOWIN通过呼叫PostQuitMessage以标准方式响应WM_DESTROY消息：
			PostQuitMessage (0) ;
		 */
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
		 /*
		 这是处理其他，窗口消息处理程序不予处理的消息。
		 呼叫DefWindowProc来为窗口消息处理程序不予处理的所有消息提供内定处理，这是很重要的。不然一般动作，如终止程序，将不会正常执行。
		 窗口消息处理程序不予处理的所有消息应该被传给名为DefWindowProc的Windows函数。从DefWindowProc传回的值必须由窗口消息处理程序传回。
		 */
}