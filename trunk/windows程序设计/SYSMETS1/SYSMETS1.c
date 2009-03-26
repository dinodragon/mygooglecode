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
	typedef struct tagTEXTMETRIC  //metric:���Ƶ�,���Ƶ�,������������׼
	{
		LONG tmHeight ;
		LONG tmAscent ;  //Ascent:����
		LONG tmDescent ;
		LONG tmInternalLeading ;
		LONG tmExternalLeading ;
		LONG tmAveCharWidth ;
		LONG tmMaxCharWidth ;
		�����ṹ�ֶ�
	}TEXTMETRIC, * PTEXTMETRIC ;
	*/
    switch (message)
    {
		case WM_CREATE:
			hdc = GetDC (hwnd) ;  //ȡ���豸���ݾ��
			GetTextMetrics (hdc, &tm) ;
			cxChar = tm.tmAveCharWidth ;  //ƽ���ַ����
			cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2 ;  //��д��ĸ��ƽ�����,ԼΪcxChar����150��,
															//���ڿɱ������壬TEXTMETRIC�ṹ�е�tmPitchAndFamily�ֶεĵ�λΪ1��
															/*���ڹ̶�������壬��ֵΪ0�� SYSMETS1ʹ�����λ��cxChar����cxCaps*/
			cyChar = tm.tmHeight + tm.tmExternalLeading ; //�ַ����ܸ߶ȣ������ⲿ��ࣩ
			ReleaseDC (hwnd, hdc) ;
			return 0 ;
		case WM_PAINT :
			hdc = BeginPaint (hwnd, &ps) ;
			for (i = 0 ; i < NUMLINES ; i++)
			{
				/*TextOut (hdc,  //�豸���ݾ�������ȿ�����GetDC�Ĵ���ֵ��Ҳ�������ڴ���WM_PAINT��ϢʱBeginPaint�Ĵ���ֵ��
									�豸���ݵ����Կ����˱���ʾ���ַ��������������磬�豸��������һ������ָ��������ɫ���ڶ���ɫΪ��ɫ���ڶ��豸���ݻ������˰�ɫ�ı������ڳ�������ʾ���������ʱ��Windowsʹ���������ɫ�������ַ���Χ�ľ��οռ䣨��Ϊ���ַ��򡹣���
							x,	//x��y������ʾ�������ַ����Ŀ�ʼλ�ã�x��ˮƽλ�ã�y�Ǵ�ֱλ�á�
									�ַ����е�һ���ַ������Ͻ�λ�������(x,y)�����ڶ����豸�����У�ԭ�㣨x��y��Ϊ0�ĵ㣩����ʾ��������Ͻǡ�
									�����TextOut�н�x��y��Ϊ0���򽫴���ʾ�������Ͻǿ�ʼ����ַ�����
							y,
							psText, //ָ���ַ�����ָ��
							iLength) ; //�ַ����ĳ��� ���psTextָ��Unicode�ַ��������ַ����е��ֽ�������iLengthֵ��������
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
				TextOut(hdc,22 * cxCaps, //��һ����ʾ����Ĵ�д��ʶ����20���ַ�����˵ڶ��б����ڵ�һ�����ֿ�ͷ����20 �� cxCaps����ʼ����ʹ��22����������֮���һ�����Ŀռ䡣
						cyChar * i,sysmetrics[i].szDesc,lstrlen (sysmetrics[i].szDesc)) ;
				//�������ʹ�ø�ʽ�����Ҷ������ֵ��Щ���֡���0��9�����־�����ͬ�Ŀ�ȣ����������ȱȿո��ȴ���ֵ���Ա�һ�����ֿ����Բ�ͬ����ֵӦ�ôӲ�ͬ�ĺ���λ�ÿ�ʼ��
				//��ô���������ָ���ַ���������ͼ��λ�ã�������ָ���ַ����Ŀ�ʼλ�ã��Դ����Ҷ�����ֵ���Ƿ������һЩ�أ���SetTextAlign�����Ϳ���������һ�㡣��SYSMETS1���У�
				//SetTextAlign (hdc, TA_RIGHT | TA_TOP) ;
				//֮�󣬴�������TextOut���������꽫ָ���ַ��������Ͻǣ����������Ͻǡ�
				//��ʾ������TextOut�����ĵڶ��������趨Ϊ��
				//22 * cxCaps + 40 * cxChar
				//ֵ40*cxChar�����˵ڶ��еĿ�Ⱥ͵����еĿ�ȡ���TextOut����֮����һ����SetTextAlign�ĺ��н����뷽ʽ�趨����ͨ��ʽ���Խ����´�ѭ����
				SetTextAlign (hdc, TA_RIGHT | TA_TOP) ;
				TextOut (hdc, 22 * cxCaps + 40 * cxChar, cyChar * i,szBuffer,wsprintf (szBuffer, TEXT ("%5d"),i,GetSystemMetrics (sysmetrics[i].iIndex))) ;
				SetTextAlign (hdc, TA_LEFT | TA_TOP) ;
			}
            EndPaint (hwnd, &ps) ;
            return 0 ;
		case WM_DESTROY :
			//MessageBox(NULL, TEXT ("���Ҫ�˳�?"),TEXT("����"), 3);
			PostQuitMessage (0) ;
			return 0 ;
	}
	
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}
