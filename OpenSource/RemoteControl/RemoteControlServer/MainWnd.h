#if !defined(MAINWND_H)
#define MAINWND_H

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>

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

	// Store the Program Instance
	void	SetInstance(HINSTANCE hInst);

	// Message Handling Function Prototypes
	BOOL	OnCreate(HWND hWnd,CREATESTRUCT FAR* lpCreateStruct);
	void	OnDestroy(HWND hWnd);
	void	OnGetMinMaxInfo(HWND hWnd,MINMAXINFO FAR *lpMinMaxInfo);
	void	OnKeyDown(HWND hWnd,UINT vk,BOOL fDown,int cRepeat,UINT flags);
	void	OnCommand(HWND hWnd,int iId,HWND hWndCtl,UINT iCodeNotify);
};

#endif