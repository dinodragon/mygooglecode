/*------------------------------------------------------------
   HELLOWIN.C -- Displays "Hello, Windows 98!" in client area
                 (c) Charles Petzold, 1998
 ��ѡ��-����-��������-������-����-���������WINMM.LIB��Windows multimedia��Windows��ý�壩��
  ------------------------------------------------------------*/

#include <windows.h>
//#include <mmsystem.h>
/*
������Ϣ����������Ƕ���Ϊ������ʽ��
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
*/
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, //Ӧ�ó���ǰʵ�����
					HINSTANCE hPrevInstance, //Ӧ�ó�������ʵ�����
					PSTR szCmdLine,  //ָ����������в�����ָ��
					int iCmdShow)  //Ӧ�ó���ʼִ��ʱ������ʾ��ʽ������ֵ
{
     static TCHAR szAppName[] = TEXT ("HelloWin") ;
     HWND         hwnd ;
     MSG          msg ;
 /*
 ��̬MSG��WINUSER.H�ж������£�
 typedef struct tagMSG
{
	HWND   hwnd ;hwnd ������Ϣ�Ĵ��ھ������HELLOWIN�����У���һ������CreateWindow���ص�hwndֵ��ͬ����Ϊ���Ǹó���ӵ�е�Ψһ���ڡ�
	UINT   message ;��Ϣ��ʶ��������һ����ֵ�����Ա�ʶ��Ϣ������ÿ����Ϣ������һ����Ӧ�ı�ʶ������Щ��ʶ��������Windows��ͷ�ļ������д������WINUSER.H�У�����ǰ׺WM����window message����������Ϣ����ͷ�����磬ʹ���߽���������HELLOWIN��ʾ����֮�ڣ������������ť��Windows������Ϣ�����з���һ����Ϣ������Ϣ��message�ֶε���WM_LBUTTONDOWN������һ����������ֵΪ0x0201��
	WPARAM wParam ; һ��32λ�ġ�message parameter����Ϣ�����������京�����ֵ������Ϣ�Ĳ�ͬ����ͬ��
	LPARAM lParam ;lParam һ��32λ����Ϣ��������ֵ����Ϣ�йء�
	DWORD  time ; ��Ϣ������Ϣ�����е�ʱ�䡣
	POINT  pt ; ��Ϣ������Ϣ����ʱ��������ꡣ
				POINT������̬Ҳ��һ���ṹ������WINDEF.H�ж������£�
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
		�ṹ��wParam�ֶ��Ǵ��ݸ�PostQuitMessage������ֵ��ͨ����0����
		Ȼ��return�������˳�WinMain����ֹ����
	 */
}

LRESULT CALLBACK WndProc (HWND hwnd, //���ھ��
						  UINT message, //������������Ϣ����Ϣֵ
						  WPARAM wParam, //��Ϣ�ĸ��Ӳ���
						  LPARAM lParam) //��Ϣ�ĸ��Ӳ���
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
			��WM_PAINT�Ĵ��������Ǵ�һ��BeginPaint���п�ʼ��
			hdc = BeginPaint (hwnd, &ps) ;
			����һ��EndPaint���н�����
			EndPaint (hwnd, &ps) ;
			�������������У���һ���������ǳ���Ĵ��ھ�����ڶ���������ָ����̬ΪPAINTSTRUCT�Ľṹָ�롣PAINTSTRUCT�ṹ�а���һЩ������Ϣ������򣬿�������������ʾ��������ݡ����ǽ�����һ�������۸ýṹ�ĸ����ֶΡ���������ֻ��BeginPaint��EndPaint�������õ�����
		 */
          hdc = BeginPaint (hwnd, &ps) ;
          GetClientRect (hwnd, &rect) ;
		  /*
			��һ�������ǳ��򴰿ڵľ�����ڶ���������һ��ָ�ָ꣬��һ��RECT��̬��rectangle�ṹ��
			�ýṹ���ĸ�LONG�ֶΣ��ֱ�Ϊleft��top��right��bottom��
			GetClientRect�����ĸ��ֶ��趨Ϊ������ʾ����ĳߴ硣
			left��top�ֶ�ͨ���趨Ϊ0��right��bottom�ֶ��趨Ϊ��ʾ����Ŀ�Ⱥ͸߶ȣ����ص�������
		  */
          DrawText (hdc, TEXT ("Hello, Windows 98!"), -1, &rect,DT_SINGLELINE | DT_CENTER | DT_VCENTER) ;
		  /*
			DrawText����������֣�������������������һ������
			���ڸú���Ҫ������֣���һ�������Ǵ�BeginPaint���ص��豸���ݾ�����ڶ���������Ҫ��������֣�
			������������ -1��ָʾ�ַ��������ֽ�0�ս�ġ�
			DrawText���һ��������һϵ��λ��꣬���Ǿ���WINUSER.H�ж��壨��Ȼ��������ʾ�����Ч����
			ʹ��DrawText��һ��GDI�������У�����ȷʵ��Ϊ�൱�߼��Ļ�ͼ���ܶ���ΪUserģ���һ���֡�
			�˺�����/Platform SDK/Graphics and Multimedia Services/GDI/Fonts and Text��˵������
			���ָʾ�����ֱ�����ʾ��һ���ϣ�ˮƽ����ʹ�ֱ����λ�ڵ��ĸ�����ָ���ľ������롣
			��ˣ�����������н����ַ�����Hello, Windows 98!����ʾ����ʾ��������롣
		  */
          EndPaint (hwnd, &ps) ;
          return 0 ;
          
     case WM_DESTROY:
		 /*
			HELLOWINͨ������PostQuitMessage�Ա�׼��ʽ��ӦWM_DESTROY��Ϣ��
			PostQuitMessage (0) ;
		 */
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
		 /*
		 ���Ǵ���������������Ϣ��������账�����Ϣ��
		 ����DefWindowProc��Ϊ������Ϣ��������账���������Ϣ�ṩ�ڶ��������Ǻ���Ҫ�ġ���Ȼһ�㶯��������ֹ���򣬽���������ִ�С�
		 ������Ϣ��������账���������ϢӦ�ñ�������ΪDefWindowProc��Windows��������DefWindowProc���ص�ֵ�����ɴ�����Ϣ������򴫻ء�
		 */
}