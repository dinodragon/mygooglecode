#include "MainWnd.h"
#include "WndProc.h"
#include "Server.h"
#include "Gdi.h"
#include "resource.h"

extern	"C"	SOCKET	Listen;
extern	"C"	HWND	hServerWnd;
extern	"C"	BOOL	fDIBitmap;
extern	"C"	struct	GdiList	GdiStart;
extern	"C"	struct	GdiList	*pGdiNode;

// Thread Variables
HANDLE	hThread;
DWORD	dwThreadId;

// Constructor
CMainWnd::CMainWnd()
{
}

// Destructor
CMainWnd::~CMainWnd()
{
	// Delete the Pointer to the Main Window
	delete this;

	// Free the Global Regional DIBs
	ClearDisplay(m_hWnd);
}

// Set the Program Instance
void CMainWnd::SetInstance(HINSTANCE hInst)
{
	// Set the Instance Variable
	m_hInst = hInst;
}

// Handle the WM_CREATE Message
BOOL CMainWnd::OnCreate(HWND hWnd,CREATESTRUCT FAR *lpCreateStruct)
{
	// Show the window according to WinMains nCmdShow parameter
	ShowWindow(hWnd,*(LPINT)lpCreateStruct->lpCreateParams);

	// Set the Main Window Variable
	m_hWnd = hWnd;

	// Get a Handle to the System Menu
	m_hMenu = GetMenu(m_hWnd);

	// Set the Default State of the Commands
	EnableMenuItem(m_hMenu,IDM_STARTSERVER,MF_BYCOMMAND|MF_ENABLED);
	EnableMenuItem(m_hMenu,IDM_STOPSERVER,MF_BYCOMMAND|MF_GRAYED);

	return TRUE;
}

// Handle the WM_DESTROY Message
void CMainWnd::OnDestroy(HWND hWnd)
{
	// Close the Listener Socket
	closesocket(Listen);

	// Do Socket Cleanup
	WSACleanup();

	// Post the Windows Quit message to the window
	PostMessage(hWnd,WM_QUIT,(WPARAM)0,0L);
}

// Handle the WM_GETMINMAXINFO Message
void CMainWnd::OnGetMinMaxInfo(HWND hWnd,MINMAXINFO FAR* lpMinMaxInfo)
{
	// Set the Tracking Size
	lpMinMaxInfo->ptMaxTrackSize.x = 200;
	lpMinMaxInfo->ptMaxTrackSize.y = 70;

	// Set the Coordinate Size
	lpMinMaxInfo->ptMaxSize.x = 200;
	lpMinMaxInfo->ptMaxSize.y = 70;
}

// Handle WM_KEYDOWN Messages
void CMainWnd::OnKeyDown(HWND hWnd,UINT vk,BOOL fDown,int cRepeat,UINT flags)
{
	if (vk == VK_ESCAPE || vk == VK_F12)
		PostMessage(hWnd,WM_CLOSE,0,0);
}

// Handle WM_COMMAND
void CMainWnd::OnCommand(HWND hWnd,int iId,HWND hWndCtl,UINT iCodeNotify)
{
	if (iId == IDM_EXIT)
	{
		// Terminate the Thread
		if (hThread)
		{
			// Close the Listener Socket
			closesocket(Listen);

			// Do Socket Cleanup
			WSACleanup();
		}

		// Quit the Program
		PostQuitMessage(0);
	}
	else if (iId == IDM_STARTSERVER)
	{
		// Minimize the Window
		ShowWindow(hWnd,SW_MINIMIZE);

		// Cause a WM_PAINT
		RedrawWindow(hWnd,NULL,NULL,RDW_ERASE|RDW_INVALIDATE);

		// Start the Server as a new Thread
		hThread = CreateThread(NULL,0,LoadWinsock,(LPVOID)NULL,0,&dwThreadId);
		if (hThread == NULL)
			MessageBox(hWnd,"Failed to Create Socket Thread","Remote Control Server",MB_ICONEXCLAMATION|MB_OK);
		else
		{
			// Initialize the Display Variables
			InitDisplay(hWnd);
			hServerWnd = hWnd;
			EnableMenuItem(m_hMenu,IDM_STARTSERVER,MF_BYCOMMAND|MF_GRAYED);
			EnableMenuItem(m_hMenu,IDM_STOPSERVER,MF_BYCOMMAND|MF_ENABLED);
		}
	}
	else if (iId == IDM_STOPSERVER)
	{
		EnableMenuItem(m_hMenu,IDM_STARTSERVER,MF_BYCOMMAND|MF_ENABLED);
		EnableMenuItem(m_hMenu,IDM_STOPSERVER,MF_BYCOMMAND|MF_GRAYED);

		// Clear the Display Variables
		ClearDisplay(hWnd);

		// Terminate the Thread
		if (hThread)
		{
			// Close the Listener Socket
			closesocket(Listen);
		}
	}
}
