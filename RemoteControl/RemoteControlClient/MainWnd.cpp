#include "MainWnd.h"
#include "WndProc.h"
#include "client.h"
#include "ServerIP.h"
#include "Compression.h"
#include "ColorMode.h"
#include "GridSpacing.h"
#include "Gdi.h"
#include "resource.h"

#define	DISCONNECT_MSG		"DISCONNECT"

// Pointer to the Server IP Class
extern	CServerIP				*pServerIP;

// Pointer to the Compression Class
extern	CCompression			*pCompression;

// Pointer to the Grid Spacing Class
extern	CGridSpacing			*pGridSpacing;

// Pointer to the Color Mode Class
extern	CColorMode				*pColorMode;

// Bitmap and Socket Variables
extern	"C" char				*pDIBitmap;
extern	"C" BOOL				fDIBitmap;
extern	"C"	int					iWidth,iHeight;
extern	"C"	int					iScreenWidth,iScreenHeight;
extern	"C"	int					iWidth1,iWidth2,iHeight1,iHeight2;
extern	"C"	int					iCompressionLevel;
extern	"C" LPBITMAPINFOHEADER	lpBitmapIH;
extern	"C" SOCKET				sClient;
extern	"C"	BOOL				fConnected;
extern	"C"	struct	GdiList		GdiStart;
extern	"C"	struct	GdiList		*pGdiNode;
extern	"C"	int					nGridX,nGridY;
extern	"C"	BOOL				fGridX,fGridY;
extern	"C"	WORD				bmBitsPixel;

// Connected, Sending and Receiving Variables
int		iSent,iRecv;
char	szMouseMessage[81];

// Constructor
CMainWnd::CMainWnd()
{
	// Initialize the Scroll Bars
	iHScrollPos = 0;
	iVScrollPos = 0;
	GdiStart.pNext = NULL;

	// Set the Initial Timer Interval
	m_iTimerInterval = 398;
}

// Destructor
CMainWnd::~CMainWnd()
{
	// Delete the Pointer to the Main Window
	delete this;

	// Free the Global Memory
	if (fDIBitmap)
		free(pDIBitmap);

	// Free the Global Regional Memory
	pGdiNode = GdiStart.pNext;
	while (pGdiNode)
	{
		// Check if the Memory has been Allocated
		if (pGdiNode->Gdi.fDIBitmap)
		{
			free(pGdiNode->Gdi.pDIBitmap);
			free(pGdiNode->Gdi.pDIB);
		}

		// Move to the Next Element
		pGdiNode = pGdiNode->pNext;
	}
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

	// Get a Handle to the Menu
	m_hMenu = GetMenu(m_hWnd);

	// Disable the Disconnect Menu Item
	EnableMenuItem(m_hMenu,IDM_DISCONNECT,MF_BYCOMMAND|MF_GRAYED);

	// Disable the Color Mode Menu Item
	EnableMenuItem(m_hMenu,IDM_COLORMODE,MF_BYCOMMAND|MF_GRAYED);

	// Set the Default Compression Level
	iCompressionLevel = 10;

	return TRUE;
}

// Handle the WM_DESTROY Message
void CMainWnd::OnDestroy(HWND hWnd)
{
	// Check if a DIB was Retrieved
	if (fDIBitmap)
	{
		// Kill the Refresh Timer
		KillTimer(m_hWnd,0);
	}

	// Check for a Current Connection
	if (fConnected)
	{
		// Send the Message to the Server to End the Thread
		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		strcpy(szMouseMessage,DISCONNECT_MSG);

		// Send the Message to the Server
		iSent = Send(sClient,szMouseMessage);

		// Close the Socket
		closesocket(sClient);

		// Cleanup
		WSACleanup();

		// Set the Connection State
		fConnected = FALSE;
	}

	// Post the Windows Quit message to the window
	PostMessage(hWnd,WM_QUIT,(WPARAM)0,0L);
}

// Handle the WM_SIZE Message
void CMainWnd::OnSize(HWND hWnd,UINT state,int cx,int cy)
{
	// Check if we have a DIB
	if (fDIBitmap)
	{
		// Get the Client Rectangle
		GetClientRect(m_hWnd,&m_Rect);

		// Set the Scroll Ranges for the New Screen Size
		SetScrollRange(m_hWnd,SB_HORZ,0,iScreenWidth - m_Rect.right,FALSE);
		SetScrollPos(m_hWnd,SB_HORZ,iHScrollPos,TRUE);
		SetScrollRange(m_hWnd,SB_VERT,0,iScreenHeight - m_Rect.bottom,FALSE);
		SetScrollPos(m_hWnd,SB_VERT,iVScrollPos,TRUE);

		// Generate a WM_PAINT Message
		InvalidateRect(hWnd,NULL,FALSE);
	}
}

// Handle the WM_PAINT Message
void CMainWnd::OnPaint(HWND hWnd)
{
	PAINTSTRUCT			ps;
	HDC					hDC;
	struct	GdiList		*pNode;
	int					iX1,iX2,iY1,iY2;

	// Start the Painting of the Screen
	hDC = BeginPaint(hWnd,&ps);

	// Draw the Full Bitmap
	if (fDIBitmap)
	{
		// Get the Client Rectangle
		GetClientRect(m_hWnd,&m_Rect);

		// Only Create the Bkg DC and Bitmap on the Fly if Offline (To Preserve Screen State)
		if (!fConnected)
		{
			// Build the Full Bitmap into a Mem DC from the Regions
			m_hMemDC = CreateCompatibleDC(hDC);

			// Create a Compatible Bitmap for the Mem DC
			m_hDDBitmap = CreateCompatibleBitmap(hDC,iScreenWidth,iScreenHeight);

			// Select the Bitmap into the Memory DC for Drawing
			SelectObject(m_hMemDC,m_hDDBitmap);
		}

		// Loop through the Regions
		pNode = GdiStart.pNext;
		while (pNode)
		{
			// Check if we have a DIB for the Region
			if (pNode->Gdi.fDIBitmap)
			{
				// Draw the Region into the Memory DC
				StretchDIBits(m_hMemDC,
					pNode->Gdi.iWidth1,pNode->Gdi.iHeight1,
					pNode->Gdi.lpBitmapIH->biWidth,pNode->Gdi.lpBitmapIH->biHeight,
					0,0,
					pNode->Gdi.lpBitmapIH->biWidth,pNode->Gdi.lpBitmapIH->biHeight,
					(LPBYTE)pNode->Gdi.lpBitmapIH + (pNode->Gdi.lpBitmapIH->biSize + (1 << pNode->Gdi.lpBitmapIH->biBitCount) * sizeof(RGBQUAD)),
					(LPBITMAPINFO)pNode->Gdi.lpBitmapIH,DIB_RGB_COLORS,SRCCOPY);
			}

			// Draw Horizontal Grid Lines
			if (fGridX)
			{
				// Get the Line Coordinates
				iX1 = pNode->Gdi.iWidth1;
				iY1 = pNode->Gdi.iHeight1;
				iY2 = pNode->Gdi.iHeight2;

				// Draw Vertical Lines at Horizontal Tics
				MoveToEx(m_hMemDC,iX1,iY1,NULL);
				LineTo(m_hMemDC,iX1,iY2);
			}

			// Draw Vertical Grid Lines
			if (fGridY)
			{
				// Get the Line Coordinates
				iX1 = pNode->Gdi.iWidth1;
				iX2 = pNode->Gdi.iWidth2;
				iY1 = pNode->Gdi.iHeight1;

				// Draw Horizontal Lines at Vertical Tics
				MoveToEx(m_hMemDC,iX1,iY1,NULL);
				LineTo(m_hMemDC,iX2,iY1);
			}

			// Move to the Next Element
			pNode = pNode->pNext;
		}

		// Blit the Built DIB From the Memory DC to the Screen DC
		BitBlt(hDC,0,0,iScreenWidth,iScreenHeight,m_hMemDC,iHScrollPos,-iVScrollPos,SRCCOPY);

		// Only Delete the Bkg DC and Bitmap on the Fly if Offline (To Preserve Screen State)
		if (!fConnected)
		{
			// Delete the Bitmap
			DeleteObject(m_hDDBitmap);

			// Delete the Mem DC
			DeleteDC(m_hMemDC);
		}
	}

	// End the Painting of the Screen
	EndPaint(hWnd,&ps);
}

// Handle WM_TIMER Messages
void CMainWnd::OnTimer(HWND hWnd,UINT iId)
{
	// If we are connected
	if (fConnected)
	{
		// Get a New Screen
		GetScreen();
	}
}

// Handle WM_COMMAND
void CMainWnd::OnCommand(HWND hWnd,int iId,HWND hWndCtl,UINT iCodeNotify)
{
	// Selected Exit from the Menu
	if (iId == IDM_EXIT)
	{
		// Check for a Current Connection
		if (fConnected)
		{
			// Send the Message to the Server to End the Thread
			memset(szMouseMessage,'\0',sizeof(szMouseMessage));
			strcpy(szMouseMessage,DISCONNECT_MSG);

			// Send the Message to the Server
			iSent = Send(sClient,szMouseMessage);

			// Close the Socket
			closesocket(sClient);

			// Cleanup
			WSACleanup();

			// Set the Connection State
			fConnected = FALSE;

			// Delete the Bkg Bitmap
			DeleteObject(m_hDDBitmap);

			// Delete the Bkg Mem DC
			DeleteDC(m_hMemDC);
		}

		// Quit the Application
		PostQuitMessage(0);
	}
	// Selected Connect from the Menu
	else if (iId == IDM_CONNECT) // Connect to the Server
	{
		// Initialize the IP Address
		strcpy(pServerIP->szIP,"AAA.BBB.CCC.DDD\0");

		// Create the ServerIP Dialog Box
		if (DialogBox(m_hInst,MAKEINTRESOURCE(IDD_SERVERIP),m_hWnd,(DLGPROC)ServerIPDlgProc))
		{
			// Load Winsock and Connect to the Server
			if (LoadWinsock(m_hWnd,pServerIP->szIP) == 0)
				fConnected = TRUE;
			else
				fConnected = FALSE;

			// Check if a DIB was Retrieved
			if (fConnected)
			{
				// Enable the Disconnect Menu Item
				EnableMenuItem(m_hMenu,IDM_DISCONNECT,MF_BYCOMMAND|MF_ENABLED);

				// Disable the Connect Menu Item
				EnableMenuItem(m_hMenu,IDM_REFRESH,MF_BYCOMMAND|MF_GRAYED);

				// Enable the Color Mode Menu Item
				EnableMenuItem(m_hMenu,IDM_COLORMODE,MF_BYCOMMAND|MF_ENABLED);

				if (fDIBitmap)
				{
					// Build the Full Bitmap into a Mem DC from the Regions
					m_hMemDC = CreateCompatibleDC(GetDC(NULL));

					// Create a Compatible Bitmap for the Mem DC
					m_hDDBitmap = CreateCompatibleBitmap(GetDC(NULL),iScreenWidth,iScreenHeight);

					// Select the Bitmap into the Memory DC for Drawing
					SelectObject(m_hMemDC,m_hDDBitmap);

					// Get the Client Rectangle
					GetClientRect(m_hWnd,&m_Rect);

					// Set the Scroll Bar Ranges
					SetScrollRange(m_hWnd,SB_HORZ,0,iScreenWidth - m_Rect.right,FALSE);
					SetScrollPos(m_hWnd,SB_HORZ,iHScrollPos,TRUE);
					SetScrollRange(m_hWnd,SB_VERT,0,iScreenHeight - m_Rect.bottom,FALSE);
					SetScrollPos(m_hWnd,SB_VERT,iVScrollPos,TRUE);

					// Set the Refresh Timer
					SetTimer(m_hWnd,0,m_iTimerInterval,NULL);
				}
			}
		}
	}
	// Selected Disconnect from the Menu
	else if (iId == IDM_DISCONNECT)
	{
		if (fConnected)
		{
			// Kill the Refresh Timer
			KillTimer(m_hWnd,0);

			// Disable the Disconnect Menu Item
			EnableMenuItem(m_hMenu,IDM_DISCONNECT,MF_BYCOMMAND|MF_GRAYED);

			// Disable the Color Mode Menu Item
			EnableMenuItem(m_hMenu,IDM_COLORMODE,MF_BYCOMMAND|MF_GRAYED);

			// Enable the Connect Menu Item
			EnableMenuItem(m_hMenu,IDM_REFRESH,MF_BYCOMMAND|MF_ENABLED);

			// Send the Message to the Server to End the Thread
			memset(szMouseMessage,'\0',sizeof(szMouseMessage));
			strcpy(szMouseMessage,DISCONNECT_MSG);

			// Send the Message to the Server
			iSent = Send(sClient,szMouseMessage);

			// Close the Socket
			closesocket(sClient);

			// Cleanup
			WSACleanup();

			// Set the Connection State
			fConnected = FALSE;

			// Delete the Bkg Bitmap
			DeleteObject(m_hDDBitmap);

			// Delete the Bkg Mem DC
			DeleteDC(m_hMemDC);
		}
	}
	// Selected Compression From the Menu
	else if (iId == IDM_COMPRESSION)
	{
		// Set the Current Compression Level to the Compression Class
		pCompression->m_iCompressionLevel = iCompressionLevel;

		// Bring up the Compression Level Dialog Box
		if (DialogBox(m_hInst,MAKEINTRESOURCE(IDD_COMPRESSION),m_hWnd,(DLGPROC)CompressionDlgProc))
		{
			// Get the New Compression Level and Scheme
			iCompressionLevel = pCompression->m_iCompressionLevel;

			// If We are Connected then Set the New Level
			if (fConnected)
			{
				// Kill the Refresh Timer
				KillTimer(m_hWnd,0);

				// Build the Compression Message
				memset(szMouseMessage,'\0',sizeof(szMouseMessage));
				sprintf(szMouseMessage,"WM_COMP;%d;0;0;0;\0",iCompressionLevel);

				// Set the Compression Level
				SendCommand(hWnd,1,szMouseMessage);

				// Set the Grids
				SetGrids(m_hWnd);

				// Get the New Gridded Screen for the First Time
				UpdateRegionalScreen(m_hWnd,sClient,TRUE);

				// Engage the Timer
				SetTimer(m_hWnd,0,m_iTimerInterval,NULL);
			}
		}
	}
	// Selected Grid Spacing from the Menu
	else if (iId == IDM_GRIDSPACING)
	{
		// Set the Current Grid Spacing
		pGridSpacing->m_nGridX = nGridX;
		pGridSpacing->m_nGridY = nGridY;
		pGridSpacing->m_fGridX = fGridX;
		pGridSpacing->m_fGridY = fGridY;

		// Bring up the Grid Spacing Dialog Box
		if (DialogBox(m_hInst,MAKEINTRESOURCE(IDD_GRIDSPACING),m_hWnd,(DLGPROC)GridSpacingDlgProc))
		{
			BOOL	fChange = FALSE;

			// Check for Getting the New Screen from Scratch
			if (nGridX != pGridSpacing->m_nGridX)
				fChange = TRUE;
			if (nGridY != pGridSpacing->m_nGridY)
				fChange = TRUE;

			// Get the New Grid Spacing Values
			nGridX = pGridSpacing->m_nGridX;
			nGridY = pGridSpacing->m_nGridY;

			// Get the Grid Drawing Flags
			fGridX = pGridSpacing->m_fGridX;
			fGridY = pGridSpacing->m_fGridY;

			// Set the New Grid Spacing on the Fly for a Connection
			if (fConnected && fChange)
			{
				// Kill the Refresh Timer
				KillTimer(m_hWnd,0);

				// Set the Grids
				SetGrids(m_hWnd);

				// Get the New Gridded Screen for the First Time
				UpdateRegionalScreen(m_hWnd,sClient,TRUE);

				// Engage the Timer
				SetTimer(m_hWnd,0,m_iTimerInterval,NULL);
			}
		}
	}
	// Selected Color Mode from the Menu
	else if (iId == IDM_COLORMODE)
	{
		// Set the Current Compression Level to the Compression Class
		pColorMode->m_bmBitsPixel = bmBitsPixel;

		// Bring up the Compression Level Dialog Box
		if (DialogBox(m_hInst,MAKEINTRESOURCE(IDD_COLORMODE),m_hWnd,(DLGPROC)ColorModeDlgProc))
		{
			// Get the New Color Mode
			bmBitsPixel = pColorMode->m_bmBitsPixel;

			// If We are Connected then Set the New Level
			if (fConnected)
			{
				// Kill the Refresh Timer
				KillTimer(m_hWnd,0);

				// Build the Color Mode Message
				memset(szMouseMessage,'\0',sizeof(szMouseMessage));
				sprintf(szMouseMessage,"WM_CMOD;%d;0;0;0;\0",bmBitsPixel);

				// Set the Compression Level
				SendCommand(hWnd,1,szMouseMessage);

				// Set the Grids
				SetGrids(m_hWnd);

				// Get the New Gridded Screen for the First Time
				UpdateRegionalScreen(m_hWnd,sClient,TRUE);

				// Engage the Timer
				SetTimer(m_hWnd,0,m_iTimerInterval,NULL);
			}
		}
	}
}

// Handle WM_VSCROLL
void CMainWnd::OnVScroll(HWND hWnd,HWND hWndCtl,UINT iCode,int iPos)
{
	if (fDIBitmap)
	{
		if (iCode == SB_LINEUP)
			iVScrollPos = iVScrollPos + 1;
		else if (iCode == SB_LINEDOWN)
			iVScrollPos = iVScrollPos - 1;
		else if (iCode == SB_PAGEUP)
			iVScrollPos = iVScrollPos + 64;
		else if (iCode == SB_PAGEDOWN)
			iVScrollPos = iVScrollPos - 64;
		else if (iCode == SB_THUMBTRACK)
			iVScrollPos = -iPos;
		else if (iCode == SB_THUMBPOSITION)
			iVScrollPos = -iPos;

		// Check the Scroll Boundaries
		if (-iVScrollPos < 0)
			iVScrollPos = 0;
		if (-iVScrollPos > (iScreenHeight - m_Rect.bottom))
			iVScrollPos = -(iScreenHeight - m_Rect.bottom);

		// Set the New Scroll Position
		SetScrollPos(hWnd,SB_VERT,-iVScrollPos,TRUE);

		// Cause a WM_PAINT
		InvalidateRect(hWnd,NULL,FALSE);
	}
}

// Handle WM_HSCROLL
void CMainWnd::OnHScroll(HWND hWnd,HWND hWndCtl,UINT iCode,int iPos)
{
	// Check if a DIB was Received
	if (fDIBitmap)
	{
		if (iCode == SB_LINEUP)
			iHScrollPos = iHScrollPos - 1;
		else if (iCode == SB_LINEDOWN)
			iHScrollPos = iHScrollPos + 1;
		else if (iCode == SB_PAGEUP)
			iHScrollPos = iHScrollPos - 48;
		else if (iCode == SB_PAGEDOWN)
			iHScrollPos = iHScrollPos + 48;
		else if (iCode == SB_THUMBTRACK)
			iHScrollPos = iPos;
		else if (iCode == SB_THUMBPOSITION)
			iHScrollPos = iPos;

		// Check the Scroll Boundaries
		if (iHScrollPos < 0)
			iHScrollPos = 0;
		if (iHScrollPos > (iScreenWidth - m_Rect.right))
			iHScrollPos = iScreenWidth - m_Rect.right;

		// Set the New Scroll Position
		SetScrollPos(hWnd,SB_HORZ,iHScrollPos,TRUE);

		// Cause a WM_PAINT
		InvalidateRect(hWnd,NULL,FALSE);
	}
}

// Handle the Left Button Double Clicking in the Window
void CMainWnd::OnLButtonDblClk(HWND hWnd,BOOL fDoubleClick,int x,int y,UINT keyFlags)
{
	// Check for a Connection
	if (fConnected)
	{
		// Adjust the X and Y Coordinates with the Scroll Bar Coordinates
		x += iHScrollPos;
		y += (-1 * iVScrollPos);

		// Build the Left Button Double Click Message
		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_LBK;%d;%d;%d;0;\0",x,y,keyFlags);

		// Send the Command
		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// Handle the Left Button Down in the Window
void CMainWnd::OnLButtonDown(HWND hWnd,BOOL fDoubleClick,int x,int y,UINT keyFlags)
{
	// Check for a Connection
	if (fConnected)
	{
		// Adjust the X and Y Coordinates with the Scroll Bar Coordinates
		x += iHScrollPos;
		y += (-1 * iVScrollPos);

		// Build the Left Button Down Message
		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_LBD;%d;%d;%d;0;\0",x,y,keyFlags);

		// Send the Command
		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// Handle the Left Button Up in the Window
void CMainWnd::OnLButtonUp(HWND hWnd,int x,int y,UINT keyFlags)
{
	// Check for a Connection
	if (fConnected)
	{
		// Adjust the X and Y Coordinates with the Scroll Bar Coordinates
		x += iHScrollPos;
		y += (-1 * iVScrollPos);

		// Build the Left Button Up Message
		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_LBU;%d;%d;%d;0;\0",x,y,keyFlags);

		// Send the Command
		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// Handle the Middle Button Double Clicking in the Window
void CMainWnd::OnMButtonDblClk(HWND hWnd,BOOL fDoubleClick,int x,int y,UINT keyFlags)
{
	// Check for a Connection
	if (fConnected)
	{
		// Adjust the X and Y Coordinates with the Scroll Bar Coordinates
		x += iHScrollPos;
		y += (-1 * iVScrollPos);

		// Build the Middle Button Double Click Message
		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_MBK;%d;%d;%d;0;\0",x,y,keyFlags);

		// Send the Command
		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// Handle the Middle Button Down in the Window
void CMainWnd::OnMButtonDown(HWND hWnd,BOOL fDoubleClick,int x,int y,UINT keyFlags)
{
	// Check for a Connection
	if (fConnected)
	{
		// Adjust the X and Y Coordinates with the Scroll Bar Coordinates
		x += iHScrollPos;
		y += (-1 * iVScrollPos);

		// Build the Middle Button Down Message
		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_MBD;%d;%d;%d;0;\0",x,y,keyFlags);

		// Send the Command
		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// Handle the Middle Button Up in the Window
void CMainWnd::OnMButtonUp(HWND hWnd,int x,int y,UINT keyFlags)
{
	// Check for a Connection
	if (fConnected)
	{
		// Adjust the X and Y Coordinates with the Scroll Bar Coordinates
		x += iHScrollPos;
		y += (-1 * iVScrollPos);

		// Build the Middle Button Up Message
		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_MBU;%d;%d;%d;0;\0",x,y,keyFlags);

		// Send the Command
		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// Handle the Right Button Double Clicking in the Window
void CMainWnd::OnRButtonDblClk(HWND hWnd,BOOL fDoubleClick,int x,int y,UINT keyFlags)
{
	// Check for a Connection
	if (fConnected)
	{
		// Adjust the X and Y Coordinates with the Scroll Bar Coordinates
		x += iHScrollPos;
		y += (-1 * iVScrollPos);

		// Build the Right Button Double Click Message
		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_RBK;%d;%d;%d;0;\0",x,y,keyFlags);

		// Send the Command
		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// Handle the Right Button Down in the Window
void CMainWnd::OnRButtonDown(HWND hWnd,BOOL fDoubleClick,int x,int y,UINT keyFlags)
{
	// Check for a Connection
	if (fConnected)
	{
		// Adjust the X and Y Coordinates with the Scroll Bar Coordinates
		x += iHScrollPos;
		y += (-1 * iVScrollPos);

		// Build the Right Button Down Message
		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_RBD;%d;%d;%d;0;\0",x,y,keyFlags);

		// Send the Command
		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// Handle the Right Button Up in the Window
void CMainWnd::OnRButtonUp(HWND hWnd,int x,int y,UINT keyFlags)
{
	// Check for a Connection
	if (fConnected)
	{
		// Adjust the X and Y Coordinates with the Scroll Bar Coordinates
		x += iHScrollPos;
		y += (-1 * iVScrollPos);

		// Build the Right Button Up Message
		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_RBU;%d;%d;%d;0;\0",x,y,keyFlags);

		// Send the Command
		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// Handle Mouse Moving in the Window
void CMainWnd::OnMouseMove(HWND hWnd,int x,int y,UINT keyFlags)
{
	// Check for a Connection
	if (fConnected)
	{
		// Adjust the X and Y Coordinates with the Scroll Bar Coordinates
		x += iHScrollPos;
		y += (-1 * iVScrollPos);

		// Build the Mouse Move Message
		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_MM;%d;%d;%d;0;\0",x,y,keyFlags);

		// Send the Command
		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// Handle a Key Down Event
void CMainWnd::OnKeyDown(HWND hWnd,UINT vk,BOOL fDown,int cRepeat,UINT flags)
{
	// Check for a Connection
	if (fConnected)
	{
		// Build the Key Down Message
		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_KD;%d;%d;%d;%d;\0",vk,fDown,cRepeat,flags);

		// Send the Command
		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// Handle a Key Up Event
void CMainWnd::OnKeyUp(HWND hWnd,UINT vk,BOOL fDown,int cRepeat,UINT flags)
{
	// Check for a Connection
	if (fConnected)
	{
		// Build the Key Up Message
		memset(szMouseMessage,'\0',sizeof(szMouseMessage));
		sprintf(szMouseMessage,"WM_KU;%d;%d;%d;%d;\0",vk,fDown,cRepeat,flags);

		// Send the Command
		SendCommand(m_hWnd,1,szMouseMessage);
	}
}

// Get a New Screen
void CMainWnd::GetScreen()
{
	// Get the Screen
	SendCommand(m_hWnd,0,NULL);
}
