#if !defined(MAINWND_H)
#define MAINWND_H

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <time.h>

// Main Window Class For Message Handling
class	CMainWnd
{
public:

	// Constructor and Destructor
	CMainWnd();
	~CMainWnd();

	// Program Variables
	HINSTANCE			m_hInst;
	HWND				m_hWnd;
	HMENU				m_hMenu;

	// BackGround Memory DC and Bitmap for Blting
	HDC					m_hMemDC;
	HBITMAP				m_hDDBitmap;

	// Scroll Bar Variables
	int					iVScrollPos,iHScrollPos;
	RECT				m_Rect;

	// Timer Interval
	long				m_iTimerInterval;

	// Store the Program Instance
	void	SetInstance(HINSTANCE hInst);

	// Message Handling Function Prototypes
	BOOL	OnCreate(HWND hWnd,CREATESTRUCT FAR* lpCreateStruct);
	void	OnDestroy(HWND hWnd);
	void	OnSize(HWND hWnd,UINT state,int cx,int cy);
	void	OnPaint(HWND hWnd);
	void	OnTimer(HWND hWnd,UINT iId);
	void	OnCommand(HWND hWnd,int iId,HWND hWndCtl,UINT iCodeNotify);
	void	OnVScroll(HWND hWnd,HWND hWndCtl,UINT iCode,int iPos);
	void	OnHScroll(HWND hWnd,HWND hWndCtl,UINT iCode,int iPos);
	void	GetScreen();
	void	OnLButtonDblClk(HWND hWnd,BOOL fDoubleClick,int x,int y,UINT keyFlags);
	void	OnLButtonDown(HWND hWnd,BOOL fDoubleClick,int x,int y,UINT keyFlags);
	void	OnLButtonUp(HWND hWnd,int x,int y,UINT keyFlags);
	void	OnMButtonDblClk(HWND hWnd,BOOL fDoubleClick,int x,int y,UINT keyFlags);
	void	OnMButtonDown(HWND hWnd,BOOL fDoubleClick,int x,int y,UINT keyFlags);
	void	OnMButtonUp(HWND hWnd,int x,int y,UINT keyFlags);
	void	OnRButtonDblClk(HWND hWnd,BOOL fDoubleClick,int x,int y,UINT keyFlags);
	void	OnRButtonDown(HWND hWnd,BOOL fDoubleClick,int x,int y,UINT keyFlags);
	void	OnRButtonUp(HWND hWnd,int x,int y,UINT keyFlags);
	void	OnMouseMove(HWND hWnd,int x,int y,UINT keyFlags);
	void	OnKeyDown(HWND hWnd,UINT vk,BOOL fDown,int cRepeat,UINT flags);
	void	OnKeyUp(HWND hWnd,UINT vk,BOOL fDown,int cRepeat,UINT flags);
};

#endif