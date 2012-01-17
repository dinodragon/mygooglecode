//*******************************************************************

// 工程：hello

// 文件：hello.cpp

// 内容：创建第一个DirectDraw应用程序，

//*******************************************************************



#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>

LPDIRECTDRAW lpDD; // DirectDraw对象
LPDIRECTDRAWSURFACE lpDDSPrimary; // DirectDraw主页面
char szMsg1[] = "Hello World, I am DirectDraw boy !";
char szMsg2[] = "按 ESC 退出";

//函数声明

LRESULT CALLBACK WinProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
BOOL InitWindow( HINSTANCE hInstance, int nCmdShow );
BOOL InitDDraw( void );
void FreeDDraw( void );

//*******************************************************************
//函数：WinMain()
//功能：Win32应用程序入口函数。进行初始化工作，处理消息循环
//*******************************************************************

int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nCmdShow)

{
	MSG msg;
	//初始化主窗口
	if ( !InitWindow( hInstance, nCmdShow ) )
		return FALSE;

	//初始化DirectDraw环境，并实现DirectDraw功能
	if ( !InitDDraw())
	{
		MessageBox(GetActiveWindow(), "初始化DirectDraw过程中出错！", "Error", MB_OK );
		FreeDDraw();
		DestroyWindow(GetActiveWindow());
		return FALSE;
	}

	//进入消息循环
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}



//******************************************************************
//函数：InitWindow()
//功能：创建主窗口。
//******************************************************************

static BOOL InitWindow( HINSTANCE hInstance, int nCmdShow )
{
	HWND hwnd; //窗口句柄
	WNDCLASS wc; //窗口类结构

	//填充窗口类结构
	wc.style = 0;
	wc.lpfnWndProc = WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon( hInstance, IDI_APPLICATION );
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "dxHello";

	//注册窗口类
	RegisterClass( &wc );

	//创建主窗口
	hwnd = CreateWindowEx(
		0,
		"dxHello",
		"",
		WS_POPUP,
		0, 0,
		GetSystemMetrics( SM_CXSCREEN ),
		GetSystemMetrics( SM_CYSCREEN ),
		NULL,
		NULL,
		hInstance,
		NULL );

	if( !hwnd ) return FALSE;
	//显示并更新窗口
	ShowWindow( hwnd, nCmdShow );
	UpdateWindow( hwnd );
	return TRUE;
}

//******************************************************************
//函数：WinProc()
//功能：处理主窗口消息
//******************************************************************

LRESULT CALLBACK WinProc( HWND hWnd, UINT message,
						 WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hdc;
	char szHello[] = "Hello, you crazy world you!";
	switch( message )
	{
	case WM_KEYDOWN://击键消息
		switch( wParam )
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		}
		break;
	case WM_DESTROY://退出消息
		FreeDDraw();
		PostQuitMessage( 0 );
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		RECT rt;
		GetClientRect(hWnd, &rt);
		DrawText(hdc, szHello, strlen(szHello), &rt,DT_CENTER | DT_VCENTER | DT_SINGLELINE );
		TextOut( hdc, 220, 200, szMsg1, lstrlen(szMsg1));
		TextOut( hdc, 280, 240, szMsg2, lstrlen(szMsg2));
		EndPaint(hWnd, &ps);
		break;
	}
	//调用缺省消息处理过程
	return DefWindowProc(hWnd, message, wParam, lParam);
}



//******************************************************************
//函数：InitDDraw()
//功能：初始化DirectDraw环境并实现其功能。包括：创建DirectDraw对象，
// 设置显示模式，创建主页面，输出文字。
//******************************************************************

BOOL InitDDraw(void)

{
	DDSURFACEDESC ddsd; //页面描述
	HDC hdc; //设备环境句柄

	//创建DirectCraw对象
	if ( DirectDrawCreate( NULL, &lpDD, NULL ) != DD_OK ) return FALSE;

	// 取得独占和全屏模式
	if (lpDD->SetCooperativeLevel(GetActiveWindow(),DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN ) != DD_OK)
		return FALSE;

	//设置显示模式
	if ( lpDD->SetDisplayMode( 1280, 1024, 65536 ) != DD_OK) return FALSE;

	//填充主页面信息
	ddsd.dwSize = sizeof( ddsd );
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

	//创建主页面对象
	if ( lpDD->CreateSurface( &ddsd, &lpDDSPrimary, NULL ) != DD_OK)
		return FALSE;

	//输出文字
	if ( lpDDSPrimary->GetDC(&hdc) != DD_OK) return FALSE;
	SetBkColor( hdc, RGB( 0, 0, 0 ) );
	SetTextColor( hdc, RGB( 255, 255, 255 ) );
	TextOut( hdc, 220, 200, szMsg1, lstrlen(szMsg1));
	TextOut( hdc, 280, 240, szMsg2, lstrlen(szMsg2));
	lpDDSPrimary->ReleaseDC(hdc);
	return TRUE;
}

//******************************************************************
//函数：FreeDDraw()
//功能：释放所有的DirectDraw对象。
//******************************************************************

void FreeDDraw( void )
{
	if( lpDD != NULL )
	{
		if( lpDDSPrimary != NULL )
		{
			lpDDSPrimary->Release();
			lpDDSPrimary = NULL;
		}
		lpDD->Release();
		lpDD = NULL;
	}

}

