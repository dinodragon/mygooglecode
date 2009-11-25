// Module Name: Server.c
//
// Description:
//    A Server that Sends the Desktop to a Connected Client.
//
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <winuser.h>
#include "Server.h"
#include "Command.h"
#include "Gdi.h"
#include "HuffCompress.h"
#include "RLE.h"

#define DEFAULT_PORT        5150
#define SETFLAGS			XP1_GUARANTEED_DELIVERY|XP1_GUARANTEED_ORDER
#define NOTSETFLAGS			XP1_CONNECTIONLESS
#define	LPBMIH				LPBITMAPINFOHEADER

int		nGridX = 8;
int		nGridY = 2;
DWORD	dwLen,dwCompress,dwSendLen;
int		iCompressionLevel = 10;
HWND	hServerWnd;
HDC		hDDC = NULL,hMemDC,hNullDC;
BOOL	fChange = FALSE;
SOCKET	Socket;
SOCKET	Listen;
int		iWidth,iHeight;
WORD	bmBitsPixel = 4;

// Pointer to the Global Bitmap
BOOL	fDIBitmap = FALSE;

// Gdi Region Structure
struct	GdiList	GdiStart;
struct	GdiList	*pGdiNode;

// Structure Used to Pass Information to ClientThread in the LPARAM Parameter
struct	myStruct
{
	SOCKET	Socket;
	HWND	hWnd;
};

int SelectProtocols(DWORD dwSetFlags,DWORD dwNotSetFlags,LPWSAPROTOCOL_INFO lpProtocolBuffer,LPDWORD lpdwBufferLength,WSAPROTOCOL_INFO *pProtocol);

//
//	Function: InitWinsock()
//
//	Description:
//		Load and Initialize Winsock, bind
//		to the local address, create the listening socket, 
//		and wait for client connections.
//
DWORD WINAPI LoadWinsock(LPVOID lpParam)
{
	// Protocol Variables
	LPBYTE				pBuf;
	WSAPROTOCOL_INFO	Protocol;
	int					nRet;
	int					nZero = 0;

	// Winsock Variables
	WSADATA				wsd;
	int					iAddrSize;
	HANDLE				hThread;
	DWORD				dwThreadId;
	char				szClientIP[81];
	char				szString[255];
	struct	sockaddr_in	local,client;

	// Structure Used to Pass Information to ClientThread in the LPARAM Parameter
	struct	myStruct	myStructure;

	// Load Winsock Ver 2.2
	if (WSAStartup(0x202,&wsd) != 0)
	{
		sprintf(szString,"Failed to load Winsock!");
		MessageBox(NULL,szString,"Remote Server",MB_OK);
		return 1;
	}

	// Determine needed buffer size for Protocol Selection of All Available Protocols
	dwLen = 0;
	nRet = WSAEnumProtocols(NULL,NULL,&dwLen);
	if (nRet == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAENOBUFS)
			return 1;
	}

	// Allocate the buffer
	pBuf = malloc(dwLen);

	// Get the Protocol for WSASocket()
	nRet = SelectProtocols(SETFLAGS,NOTSETFLAGS,(LPWSAPROTOCOL_INFO)pBuf,&dwLen,&Protocol);

	// Create our listening socket
//	Listen = WSASocket(AF_INET,SOCK_STREAM,IPPROTO_IP,&Protocol,0,WSA_FLAG_OVERLAPPED);
//	Listen = WSASocket(AF_INET,SOCK_STREAM,IPPROTO_IP,&Protocol,0,SOCK_STREAM);
	Listen = WSASocket(AF_INET,SOCK_STREAM,IPPROTO_IP,NULL,0,SOCK_STREAM);
	if (Listen == SOCKET_ERROR)
	{
		sprintf(szString,"socket() failed: %d",WSAGetLastError());
		MessageBox(NULL,szString,"Remote Server",MB_OK);
		return 1;
	}

	// Select the local interface and bind to it
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	local.sin_family = AF_INET;
	local.sin_port = htons(DEFAULT_PORT);

	// Bind to the Socket
	if (bind(Listen,(struct sockaddr *)&local,sizeof(local)) == SOCKET_ERROR)
	{
		sprintf(szString,"bind() failed: %d\n", WSAGetLastError());
		MessageBox(NULL,szString,"Remote Server",MB_OK);
		return 1;
	}

	// Disable send buffering on the socket.  Setting SO_SNDBUF
	// to 0 causes winsock to stop bufferring sends and perform
	// sends directly from our buffers, thereby reducing CPU
	// usage.
	nZero = 0;
	setsockopt(Listen,SOL_SOCKET,SO_SNDBUF,(char *)&nZero,sizeof(nZero));

	// Set the Socket in a Listening State for the Maximum Connections Allowable
	listen(Listen,SOMAXCONN);

    // Wait for incoming clients. Once one is detected, 
	// Create a thread and pass the handle off to it.
	iAddrSize = sizeof(client);
	while (TRUE)
	{
		// Accept the Client
		Socket = accept(Listen,(struct sockaddr *)&client,&iAddrSize);
		if (Socket != INVALID_SOCKET)
		{
			// Set the Structure to Pass Information to Client Thread
			myStructure.Socket = Socket;
			myStructure.hWnd = hServerWnd;

			// Collect the IP Address of the Client
			memset(szClientIP,'\0',sizeof(szClientIP));
			sprintf(szClientIP,"%s",inet_ntoa(client.sin_addr));

			// Create the Thread
			hThread = CreateThread(NULL,0,ClientThread,(LPVOID)&myStructure,0,&dwThreadId);
			if (hThread)
			{
				// Close the Hande to the Thread
				CloseHandle(hThread);
			}
		}
		else
			return 1;
	}

	return 0;
}

//
// Function: ClientThread
//
// Description:
//    This function is called as a thread, and it handles a given
//    client connection.  The parameter passed in is the socket 
//    handle returned from an accept() call.
//
//    The Function wait for incomeing messages from the client program.
//    If the Message is "REFRESH" it sends the current desktop image
//    If the Message is "DISCONNECT" it ends the client connection
//
DWORD WINAPI ClientThread(LPVOID lpParam)
{
	// Sockets
	HWND	hWnd;
	SOCKET	MySocket;
	FD_SET	SocketSet;
	struct	timeval	timeout;
	char	szMessage[2049];
	DWORD	iRecv;
	struct	myStruct	*myStructure;
	DWORD	iLength;
	DWORD	iRet;
	int		iUpdates;

	// Parse the Passed Information
	myStructure = (struct myStruct *)lpParam;
	MySocket = myStructure->Socket;
	hWnd = myStructure->hWnd;

	// Set the Time Out Value
	timeout.tv_sec = 0;	// Seconds
	timeout.tv_usec = 0;	// Micro Seconds

	// Set the Socket Set
	SocketSet.fd_count = 1;
	SocketSet.fd_array[1] = MySocket;

	// Poll the Sockets while we are connected
	while(TRUE)
	{
		// Wait for the Timeout period for incoming data
		iRet = select(0,&SocketSet,NULL,NULL,&timeout);
		if (iRet != 0)
		{
 			// Initialize the Buffer
			memset(szMessage,'\0',sizeof(szMessage));

			// Perform a blocking recv() call
			iRecv = recv(MySocket,szMessage,2048,0);

			// Terminate the Retrieved String with a NULL
			szMessage[iRecv] = '\0';

			CHECK_MSG:
			// Check the Received Message for a Screen Refresh
			if (strncmp(szMessage,"REFRESH",7) == 0)
			{
				// Capture and Send the Updated Regions of the Desktop Display
				iUpdates = SendRegionDisplay(hServerWnd,MySocket);
			}

			// Check the Received Message for a Windows Command Message
			else if (strncmp(szMessage,"WM_",3) == 0)
			{
				// Dispatch the Windows Command from the Client
				DispatchWMMessage(szMessage);

				// See if there is still more commands
				iLength = strlen(szMessage);
				if (iLength > 0)
					goto CHECK_MSG;
			}

			// Check the Received Message for a Resolution Query
			else if (strncmp(szMessage,"RESOLUTION",10) == 0)
			{
				// Send the Resolution
				SendResolution(MySocket);
			}

			// Check the Received Message for a Client Disconnect
			else if (strncmp(szMessage,"DISCONNECT",10) == 0)
			{
				// Reset the Status
				fChange = FALSE;
				fDIBitmap = FALSE;

				// Free the Global Regional DIBs
				pGdiNode = GdiStart.pNext;
				while (pGdiNode)
				{
					// Free the Regional DIB
					free(pGdiNode->Gdi.pDIBitmap);
					free(pGdiNode->Gdi.pDIBChangeStart);
					pGdiNode->Gdi.fDIBitmap = FALSE;
					pGdiNode->Gdi.fChange = FALSE;

					// Move to the Next Element
					pGdiNode = pGdiNode->pNext;
				}

				// Stop Polling for Data
				break;
			}
		}
	}

	// Close the Client Socket
	closesocket(MySocket);

	// Return back to listening state
	return 0;
}

// Dispatch the Windows Message Passed from the Client Program
void DispatchWMMessage(char *szString)
{
	// Structure to Hold String Rep's of WM_MOUSE MESSAGES
	struct {char *szWMMouseMsg;} 
	WMMouseMsg[] = {"WM_MM","WM_LBD","WM_LBU","WM_LBK",
					"WM_MBD","WM_MBU","WM_MBK",
					"WM_RBD","WM_RBU","WM_RBK"};

	// Structure to Hold String Rep's of WM_KEY MESSAGES
	struct {char *szWMKeyBdMsg;}
	WMKeyBdMsg[] = {"WM_KD","WM_KU"};

	// Generic Messages
	struct {char *szMsg;}
	Msg[] = {"WM_COMP","WM_GRID","WM_CMOD"};

	int		nWMMouseMsg;
	int		nWMKeyBdMsg;
	int		nMsg;

	struct	CommandList	CommandStart;
	struct	CommandList	*pCommandNode;
	struct	CommandDS	Command;
	char	*pDest;
	int		iLoc,nChar;
	int		iLoop,iParms;
	char	szString2[2049];

	// Get the Number of Mouse Messages 
	nWMMouseMsg = (int)(sizeof(WMMouseMsg)/sizeof(WMMouseMsg[0]));

	// Get the Number of Keyboard Messages
	nWMKeyBdMsg = (int)(sizeof(WMKeyBdMsg)/sizeof(WMKeyBdMsg[0]));

	// Get the Number of Generic Messages
	nMsg = (int)(sizeof(Msg)/sizeof(Msg[0]));

	// Initialize the Command List
	CommandStart.pNext = NULL;
	pCommandNode = &CommandStart;

	// Parse the Command String
	iParms = 0;
	while (pDest = strchr(szString,';'))
	{
		// Parse the Command
		iLoc = pDest - szString;
		nChar = iLoc;
		memset(Command.szElement,'\0',sizeof(Command.szElement));
		strncpy(Command.szElement,szString,nChar);

		// Add the Command to the Command Stack
		pCommandNode = Add_Command(pCommandNode,Command);

		// Update the Command String by Removing Processed Parameter
		memset(szString2,'\0',sizeof(szString2));
		strcpy(szString2,&szString[iLoc + 1]);
		strcpy(szString,szString2);

		// Increment the Parameters Processed
		iParms++;
		if (iParms == 5) // 5 Parms Per Command
			break;
	}

	// Process the Command
	pCommandNode = CommandStart.pNext;
	if (pCommandNode)
	{
		// Mouse Messages
		UINT	keyFlags;
		int		iMessage;
		int		fWMMouseMsg;
		double	iScaleX,iScaleY,iX,iY;
		DWORD	dwX,dwY;

		// Key Board Messages
		int		fWMKeyBdMsg;
		UINT	vk;
		int		fDown;
		int		cRepeat;
		UINT	flags;

		// Process the Mouse Window Events
		fWMMouseMsg = FALSE;
		for (iLoop = 0;iLoop < nWMMouseMsg;iLoop++)
		{
			// Check for a Mouse Message
			if (strcmp(pCommandNode->Command.szElement,WMMouseMsg[iLoop].szWMMouseMsg) == 0)
			{
				// Set the Mouse Message Flag
				fWMMouseMsg = TRUE;

				// Set the Message to Post
				if (strcmp(WMMouseMsg[iLoop].szWMMouseMsg,"WM_MM\0") == 0)
					iMessage = 1;
				else if (strcmp(WMMouseMsg[iLoop].szWMMouseMsg,"WM_LBD\0") == 0)
					iMessage = 2;
				else if (strcmp(WMMouseMsg[iLoop].szWMMouseMsg,"WM_LBU\0") == 0)
					iMessage = 3;
				else if (strcmp(WMMouseMsg[iLoop].szWMMouseMsg,"WM_LBK\0") == 0)
					iMessage = 4;
				else if (strcmp(WMMouseMsg[iLoop].szWMMouseMsg,"WM_MBD\0") == 0)
					iMessage = 5;
				else if (strcmp(WMMouseMsg[iLoop].szWMMouseMsg,"WM_MBU\0") == 0)
					iMessage = 6;
				else if (strcmp(WMMouseMsg[iLoop].szWMMouseMsg,"WM_MBK\0") == 0)
					iMessage = 7;
				else if (strcmp(WMMouseMsg[iLoop].szWMMouseMsg,"WM_RBD\0") == 0)
					iMessage = 8;
				else if (strcmp(WMMouseMsg[iLoop].szWMMouseMsg,"WM_RBU\0") == 0)
					iMessage = 9;
				else if (strcmp(WMMouseMsg[iLoop].szWMMouseMsg,"WM_RBK\0") == 0)
					iMessage = 10;

				// Move to the X Coordinate Element for a Mouse Message
				pCommandNode = pCommandNode->pNext;

				// Get the X Coordinate
				iX = atof(pCommandNode->Command.szElement);

				// Move to the Y Coordinate Element for a Mouse Message
				pCommandNode = pCommandNode->pNext;

				// Get the Y Coordinate
				iY = atof(pCommandNode->Command.szElement);

				// Move to the KeyFlags Element for a Mouse Message
				pCommandNode = pCommandNode->pNext;

				// Get the KeyFlags
				keyFlags = atoi(pCommandNode->Command.szElement);

				// Break out of the Loop
				break;
			}
		}

		// Check for Dispatching a Mouse Message
		if (fWMMouseMsg)
		{
			// Get a Scale Factor for the Coordinates (in Mickey's)
			iScaleX = 65535.0 / (iWidth - 1);
			iScaleY = 65535.0 / (iHeight - 1);

			// Scale the Coordinates
			iX *= iScaleX;
			iY *= iScaleY;

			// Convert to DWORDS
			dwX = (DWORD)iX;
			dwY = (DWORD)iY;

			// Dispatch the Mouse Message
			if (iMessage == 1) // Mouse Move
			{
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE,dwX,dwY,0,0);
			}
			else if (iMessage == 2) // Left Button Down
			{
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN,dwX,dwY,0,0);
			}
			else if (iMessage == 3) // Left Button Up
			{
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP,dwX,dwY,0,0);
			}
			else if (iMessage == 4) // Left Button DoubleClick
			{
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN,dwX,dwY,0,0);
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP,dwX,dwY,0,0);
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN,dwX,dwY,0,0);
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP,dwX,dwY,0,0);
			}
			else if (iMessage == 5) // Middle Button Down
			{
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEDOWN,dwX,dwY,0,0);
			}
			else if (iMessage == 6) // Middle Button Up
			{
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEUP,dwX,dwY,0,0);
			}
			else if (iMessage == 7) // Middle Button DoubleClick
			{
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEDOWN,dwX,dwY,0,0);
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEUP,dwX,dwY,0,0);
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEDOWN,dwX,dwY,0,0);
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MIDDLEUP,dwX,dwY,0,0);
			}
			else if (iMessage == 8) // Right Button Down
			{
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN,dwX,dwY,0,0);
			}
			else if (iMessage == 9) // Right Button Up
			{
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP,dwX,dwY,0,0);
			}
			else if (iMessage == 10) // Right Button DoubleClick
			{
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN,dwX,dwY,0,0);
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP,dwX,dwY,0,0);
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN,dwX,dwY,0,0);
				mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP,dwX,dwY,0,0);
			}
		}
		else
		{
			// Process the KeyBoard Events
			fWMKeyBdMsg = FALSE;
			for (iLoop = 0;iLoop < nWMKeyBdMsg;iLoop++)
			{
				// Check for a KeyBoard Message
				if (strcmp(pCommandNode->Command.szElement,WMKeyBdMsg[iLoop].szWMKeyBdMsg) == 0)
				{
					// Set the KeyBoard Message Flag
					fWMKeyBdMsg = TRUE;

					// Set the Message to Post
					if (strcmp(WMKeyBdMsg[iLoop].szWMKeyBdMsg,"WM_KD\0") == 0)
						iMessage = 1;
					else if (strcmp(WMKeyBdMsg[iLoop].szWMKeyBdMsg,"WM_KU\0") == 0)
						iMessage = 2;

					// Move to the VK Element for a Key Board Message
					pCommandNode = pCommandNode->pNext;

					// Get the Virtual Key Code
					vk = atoi(pCommandNode->Command.szElement);

					// Move to the Down Flag for a Key Board Message
					pCommandNode = pCommandNode->pNext;

					// Get the Down Flag
					fDown = atoi(pCommandNode->Command.szElement);

					// Move to the Repeat Count for a Key Board Message
					pCommandNode = pCommandNode->pNext;

					// Get the Repeat Count
					cRepeat = atoi(pCommandNode->Command.szElement);

					// Move to the flags element for a Key Board Message
					pCommandNode = pCommandNode->pNext;

					// Get the Flags
					flags = atoi(pCommandNode->Command.szElement);

					// Break out of the Loop
					break;
				}
			}

			// Check for Dispatching a Key Board Message
			if (fWMKeyBdMsg)
			{
				// Dispatch the Key Board Message
				if (iMessage == 1) // Key Down
				{
					keybd_event((BYTE)vk,(BYTE)vk,0,0);
				}
				else if (iMessage == 2) // Key Up
				{
					keybd_event((BYTE)vk,(BYTE)vk,KEYEVENTF_KEYUP,0);
				}
			}
			else // Generic Message
			{
				// Set the New Compression Level
				for (iLoop = 0;iLoop < nMsg;iLoop++)
				{
					// Check for a Generic Message
					if (strcmp(pCommandNode->Command.szElement,Msg[iLoop].szMsg) == 0)
					{
						// Set the Message to Post
						if (strcmp(Msg[iLoop].szMsg,"WM_COMP\0") == 0)
						{
							// Move to the Compression Level Element
							pCommandNode = pCommandNode->pNext;

							// Get the New Compression Level
							iCompressionLevel = atoi(pCommandNode->Command.szElement);
						}
						else if (strcmp(Msg[iLoop].szMsg,"WM_GRID\0") == 0)
						{
							// Move to the X Grid Spacing
							pCommandNode = pCommandNode->pNext;

							// Get the X Grid Spacing
							nGridX = atoi(pCommandNode->Command.szElement);

							// Move to the Y Grid Spacing
							pCommandNode = pCommandNode->pNext;

							// Get the Y Grid Spacing
							nGridY = atoi(pCommandNode->Command.szElement);

							// Clear the Current Display Settings
							ClearDisplay(hServerWnd);

							// Initialize the New Display Settings
							InitDisplay(hServerWnd);
						}
						else if (strcmp(Msg[iLoop].szMsg,"WM_CMOD\0") == 0)
						{
							// Move to the Bits Per Pixel
							pCommandNode = pCommandNode->pNext;

							// Get the Bits Per Pixel
							bmBitsPixel = atoi(pCommandNode->Command.szElement);

							// Clear the Current Display Settings
							ClearDisplay(hServerWnd);

							// Initialize the New Display Settings
							InitDisplay(hServerWnd);
						}
					}
				}
			}
		}
	}

	// Clear the Command List
	Clear_Command(&CommandStart);
}

// Initialize the Display Variables
void InitDisplay(HWND hWnd)
{
	// Structure to Hold the Gdi Members
	struct	GdiDS	Gdi;

	// Grid Spacing
	int		iWidthX,iHeightY,nGrid;

	// Looping Variables
	int		iXGrid,iYGrid,iLoop;

	// Initialize the Gdi Linked List
	GdiStart.pNext = NULL;
	pGdiNode = &GdiStart;

	// Get the Device Context for the Entire Display
	hDDC = CreateDC("DISPLAY",NULL,NULL,NULL);

	// Get the Width and Height of the Screen
	iWidth = GetDeviceCaps(hDDC,HORZRES);
	iHeight = GetDeviceCaps(hDDC,VERTRES);

	// Divide the Screen into the X Grid Regions
	if (nGridX > 0)
		iWidthX = iWidth/nGridX;
	else
		iWidthX = iWidth;

	// Divide the Screen into the Y Grid Regions
	if (nGridY > 0)
		iHeightY = iHeight/nGridY;
	else
		iHeightY = iHeight;

	// Create the Regional Bitmap and Memory DC Information for the Grids
	if ((nGridX > 0) && (nGridY > 0))
	{
		for (iXGrid = 0;iXGrid < nGridX;iXGrid++)
		{
			for (iYGrid = 0;iYGrid < nGridY;iYGrid++)
			{
				// Initialize the Bitmap Status
				Gdi.fChange = FALSE;
				Gdi.fDIBitmap = FALSE;

				// Get the Grid Coordinates
				Gdi.iGridX = iXGrid;
				Gdi.iGridY = iYGrid;

				// Get the Rectangular Coordinates of the Region
				Gdi.iWidth1 = iXGrid * iWidthX;
				Gdi.iWidth2 = iXGrid * iWidthX + iWidthX;
				Gdi.iHeight1 = iYGrid * iHeightY;
				Gdi.iHeight2 = iYGrid * iHeightY + iHeightY;

				// Create a Regional Compatible Memory DCs for the DC
				Gdi.hMemDC = CreateCompatibleDC(hDDC);

				// Create a Regional Compatible Bitmaps for the DC
				Gdi.hDIBitmap = CreateCompatibleBitmap(hDDC,iWidthX,iHeightY);

				// Select the Regional Bitmap Associated with the Device Context into the Regional Memory DC
				SelectObject(Gdi.hMemDC,Gdi.hDIBitmap);

				// Add the Gdi Information to the Linked List
				pGdiNode = Add_Gdi(pGdiNode,Gdi);
			}
		}
	}
	else // One Grid Component Not Used
	{
		nGrid = max(nGridX,nGridY);
		for (iLoop = 0;iLoop < nGrid;iLoop++)
		{
			// Initialize the Bitmap Status
			Gdi.fChange = FALSE;
			Gdi.fDIBitmap = FALSE;

			// Get the Rectangular Coordinates of the X Region
			if (nGridX > 0)
			{
				Gdi.iGridX = iLoop;
				Gdi.iWidth1 = iLoop * iWidthX;
				Gdi.iWidth2 = iLoop * iWidthX + iWidthX;
			}
			else
			{
				Gdi.iGridX = 0;
				Gdi.iWidth1 = 0;
				Gdi.iWidth2 = iWidthX;
			}

			// Get the Rectangular Coordinates of the Y Region
			if (nGridY > 0)
			{
				Gdi.iGridY = iLoop;
				Gdi.iHeight1 = iLoop * iHeightY;
				Gdi.iHeight2 = iLoop * iHeightY + iHeightY;
			}
			else
			{
				Gdi.iGridY = 0;
				Gdi.iHeight1 = 0;
				Gdi.iHeight2 = iHeightY;
			}

			// Create a Regional Compatible Memory DCs for the DC
			Gdi.hMemDC = CreateCompatibleDC(hDDC);

			// Create a Regional Compatible Bitmaps for the DC
			Gdi.hDIBitmap = CreateCompatibleBitmap(hDDC,iWidthX,iHeightY);

			// Select the Regional Bitmap Associated with the Device Context into the Regional Memory DC
			SelectObject(Gdi.hMemDC,Gdi.hDIBitmap);

			// Add the Gdi Information to the Linked List
			pGdiNode = Add_Gdi(pGdiNode,Gdi);
		}
	}

	// Get a DC to Get the DIB From and Remap the System Palette
	hNullDC = GetDC(NULL);
}

// Clear the Display Variables
void ClearDisplay(HWND hWnd)
{
	// Delete the Created Device Context
	DeleteDC(hDDC);

	// Delete the Null DC
	DeleteDC(hNullDC);

	// Clear the Gdi Linked List
	Clear_Gdi(&GdiStart);
}

// Get the Display Bitmap for the Region
// 
// Portions of this code were retrieved off of CODEGURU site.
// The referred portion converts a DDB to DIB.  The code
// was written by Zafir Anjum in MFC.  I converted that code to C
// for my project.
int GetRegionDisplay(HWND hWnd)
{
	// Grid Variables
	int		iWidth1,iWidth2,iHeight1,iHeight2;

	// DIB Variables
	BOOL	bGotBits;
	DWORD	iLength;
	char	*pStartDIB;

	// Temporary Variables for Assembler Code
	DWORD	dwLen1;
	DWORD	dwBitMapHeader1;
	char	*pDIBitmap1;
	char	*pDIB1;
	int		fChange1;
	char	*pDIBChange1;

	// Get the Rectangular Coordinates of the Region
	iWidth1 = pGdiNode->Gdi.iWidth1;
	iWidth2 = pGdiNode->Gdi.iWidth2;
	iHeight1 = pGdiNode->Gdi.iHeight1;
	iHeight2 = pGdiNode->Gdi.iHeight2;

	// Blit the Screen in the Regional DC (DDB) to the Regional Memory DC
	BitBlt(pGdiNode->Gdi.hMemDC,0,0,iWidth2,iHeight2,hDDC,iWidth1,iHeight1,SRCCOPY);

	/* Step 2 : Convert the DDB to a DIB */

	// Get the Regional Bitmap Information
	GetObject(pGdiNode->Gdi.hDIBitmap,sizeof(BITMAP),&(pGdiNode->Gdi.DIBitmap));

	// Set the Color Mode
	pGdiNode->Gdi.DIBitmap.bmBitsPixel = bmBitsPixel;

	// Initialize the Bitmap Info Header
	pGdiNode->Gdi.BMIH.biSize = sizeof(BITMAPINFOHEADER);
	pGdiNode->Gdi.BMIH.biWidth = pGdiNode->Gdi.DIBitmap.bmWidth;
	pGdiNode->Gdi.BMIH.biHeight = pGdiNode->Gdi.DIBitmap.bmHeight;
	pGdiNode->Gdi.BMIH.biPlanes = 1;
	pGdiNode->Gdi.BMIH.biBitCount = (WORD)pGdiNode->Gdi.DIBitmap.bmPlanes * (WORD)pGdiNode->Gdi.DIBitmap.bmBitsPixel;
	pGdiNode->Gdi.BMIH.biCompression = BI_RGB;
	pGdiNode->Gdi.BMIH.biSizeImage = 0;
	pGdiNode->Gdi.BMIH.biXPelsPerMeter = 0;
	pGdiNode->Gdi.BMIH.biYPelsPerMeter = 0;
	pGdiNode->Gdi.BMIH.biClrUsed = 0;
	pGdiNode->Gdi.BMIH.biClrImportant = 0;

	// Set the Regional Number of Colors
	pGdiNode->Gdi.nColors = 1 << pGdiNode->Gdi.BMIH.biBitCount;
	if (pGdiNode->Gdi.nColors > 256)
		pGdiNode->Gdi.nColors = 0; // Palette Not Used

	// Set the Size of the Allocation to Hold the Bitmap Info Header and the Color Table
	pGdiNode->Gdi.dwLen = (DWORD)(sizeof(BITMAPINFOHEADER) + pGdiNode->Gdi.nColors * sizeof(RGBQUAD));

	// Allocate Memory to hold the Regional Bitmapinfoheader and Color Table
	if (!pGdiNode->Gdi.fDIBitmap)
	{
		pGdiNode->Gdi.pDIB = (char *)malloc(pGdiNode->Gdi.dwLen);
		pStartDIB = pGdiNode->Gdi.pDIB;
	}

	// Cast the Allocated Memory to a Bitmap Info Header for the Region
	pGdiNode->Gdi.lpBMIH = (LPBMIH)pGdiNode->Gdi.pDIB;

	// Set the Regional Bitmap Info Header to the Regional DIB
	*(pGdiNode->Gdi.lpBMIH) = pGdiNode->Gdi.BMIH;

	// Get the Regional DIB Size
	GetDIBits(hNullDC,pGdiNode->Gdi.hDIBitmap,0L,(DWORD)pGdiNode->Gdi.BMIH.biHeight,(LPBYTE)NULL,(LPBITMAPINFO)pGdiNode->Gdi.lpBMIH,DIB_RGB_COLORS);

	// Set the Regional Bitmap Info Header with the Calculated Size
	pGdiNode->Gdi.BMIH = *(pGdiNode->Gdi.lpBMIH);

	// Save the Size of the BitMap Header
	pGdiNode->Gdi.dwBitMapHeader = pGdiNode->Gdi.dwLen;

	// Calculate the New Size of the Regional DIB w/ the Size of the Image Added
	pGdiNode->Gdi.dwLen += (DWORD)(pGdiNode->Gdi.BMIH.biSizeImage);

	// ReAllocate the Memory to Hold the Entire Regional DIB
	if (!pGdiNode->Gdi.fDIBitmap)
	{
		pGdiNode->Gdi.pDIB = pStartDIB;
		pGdiNode->Gdi.pDIB = (char *)realloc(pGdiNode->Gdi.pDIB,pGdiNode->Gdi.dwLen);
	}

	// Cast the Storage for the Regional DIB Bits
	pGdiNode->Gdi.lpBMIH = (LPBMIH)pGdiNode->Gdi.pDIB;

	// Get the Regional DIB
	bGotBits = GetDIBits(hNullDC,pGdiNode->Gdi.hDIBitmap,0L,(DWORD)pGdiNode->Gdi.BMIH.biHeight,(LPBYTE)pGdiNode->Gdi.lpBMIH + (pGdiNode->Gdi.BMIH.biSize + pGdiNode->Gdi.nColors * sizeof(RGBQUAD)),(LPBITMAPINFO)pGdiNode->Gdi.lpBMIH,DIB_RGB_COLORS);

	// Compare the Contents of the Before and After Regional DIBS for a Change
	if (pGdiNode->Gdi.fDIBitmap)
	{
		dwLen1 = pGdiNode->Gdi.dwLen;
		dwBitMapHeader1 = pGdiNode->Gdi.dwBitMapHeader;
		pDIBitmap1 = pGdiNode->Gdi.pDIBitmap;
		pDIB1 = pGdiNode->Gdi.pDIB;
		fChange1 = pGdiNode->Gdi.fChange;

		// Compare the two Bitmaps for a Difference 4 bytes at a time.  
		// Skip the BitMapHeader
		__asm
		{
			MOV		ECX,dwLen1
			SUB		ECX,dwBitMapHeader1
			SHR		ECX,2 // Divide by 4 for 4 bytes at a time
			MOV		EDX,dwBitMapHeader1
			MOV		ESI,pDIBitmap1
			ADD		ESI,EDX
			MOV		EDI,pDIB1
			ADD		EDI,EDX
			REP		CMPSD
			JNZ		SetFlagRegion1
			MOV		fChange1,FALSE
			JMP		ExitRegion1
			SetFlagRegion1:
			MOV		fChange1,TRUE
			ExitRegion1:
		}

		// Set the Change Status
		pGdiNode->Gdi.fChange = fChange1;

		// Build a DIB of Differences between the two Regional DIBs
		if (pGdiNode->Gdi.fChange)
		{
			DWORD		iZeros = 0;

			// Set the Length of the Data to Allocate w/o the BitMapHeader
			iLength = (pGdiNode->Gdi.dwLen - pGdiNode->Gdi.dwBitMapHeader);

			// Allocate enough memory to hold the Regional DIB w/o the BitMapHeader
			pGdiNode->Gdi.pDIBChange = pGdiNode->Gdi.pDIBChangeStart;
			pDIBChange1 = pGdiNode->Gdi.pDIBChange;

			// Build the Delta of the Before and After Bitmaps
			__asm
			{
				MOV		ECX,iLength // Length of Loop
				SHR		ECX,2 // Divide by 4 for 4 bytes at a time
				MOV		EDI,pDIBChange1
				MOV		ESI,pDIB1
				ADD		ESI,dwBitMapHeader1
				MOV		EDX,pDIBitmap1
				ADD		EDX,dwBitMapHeader1
				SubtractRegion:
				LODSD
				SUB		EAX,[EDX]
				ADD		EDX,4
				STOSD
				DEC		ECX
				JNZ		SubtractRegion
			}

			// Copy to the Global Regional DIB
			memblast(pGdiNode->Gdi.pDIBitmap,pGdiNode->Gdi.pDIB,pGdiNode->Gdi.dwLen);

			// Set the Length to Compress
			pGdiNode->Gdi.dwCompress = pGdiNode->Gdi.dwLen - pGdiNode->Gdi.dwBitMapHeader;

			// Set the Starting Position of the Data
			pGdiNode->Gdi.iStartPos = pGdiNode->Gdi.dwBitMapHeader;
		}
	}
	else
	{
		// Set the Length of the Data to Allocate
		iLength = (pGdiNode->Gdi.dwLen);

		// Allocate the Memory for the Global Regional DIB
		pGdiNode->Gdi.pDIBitmap = (char *)malloc(iLength);

		// Allocate enough memory to hold the Regional DIB
		pGdiNode->Gdi.pDIBChange = (char *)malloc(iLength);
		pGdiNode->Gdi.pDIBChangeStart = pGdiNode->Gdi.pDIBChange;

		// Copy to the Global Regional DIB
		memblast(pGdiNode->Gdi.pDIBitmap,pGdiNode->Gdi.pDIB,pGdiNode->Gdi.dwLen);
		memblast(pGdiNode->Gdi.pDIBChange,pGdiNode->Gdi.pDIB,pGdiNode->Gdi.dwLen);

		// Don't ReAllocate the Memory
		pGdiNode->Gdi.fDIBitmap = TRUE;
		pGdiNode->Gdi.fChange = TRUE;

		// Set the Length to Compress
		pGdiNode->Gdi.dwCompress = pGdiNode->Gdi.dwLen;

		// Set the Starting Position of the Data
		pGdiNode->Gdi.iStartPos = 0;
	}

	// Default Send a Screen for the First Time
	return pGdiNode->Gdi.fChange;
}

// Send the Resolution to the Client
void SendResolution(SOCKET MySocket)
{
	char	szMessage[81];
	DWORD	iSent,iRecv;

	// Build the Screen Width
	memset(szMessage,'\0',sizeof(szMessage));
	sprintf(szMessage,"%d",iWidth);
	iSent = Transmit(MySocket,szMessage,strlen(szMessage));

	// Receive the Confirmation
	memset(szMessage,'\0',sizeof(szMessage));
	iRecv = recv(MySocket,szMessage,81,0);
	szMessage[iRecv] = '\0';

	// Build the Screen Height
	memset(szMessage,'\0',sizeof(szMessage));
	sprintf(szMessage,"%d",iHeight);
	iSent = Transmit(MySocket,szMessage,strlen(szMessage));

	// Receive the Confirmation
	memset(szMessage,'\0',sizeof(szMessage));
	iRecv = recv(MySocket,szMessage,81,0);
	szMessage[iRecv] = '\0';
}

// Send the Regional Display Bitmap through the Socket
int SendRegionDisplay(HWND hWnd,SOCKET MySocket)
{
	char	szMessage[81];
	DWORD	iSent,iRecv;
	int		fSend = FALSE;
	int		iUpdates;
	WORD	wTreeSize;
	DWORD	dwByteTree[768];
	DWORD	dwCodes[514];
	DWORD	dwCompLen,dwLastCompLen;
	BOOL	fTransmit;
	char	*pTempDIB;
	DWORD	dwMinCompress;

	// Point to the Beginning of the Gdi List
	iUpdates = 0;
	pGdiNode = GdiStart.pNext;
	while (pGdiNode)
	{
		// Get the Regional Display for each Grid
		fSend = GetRegionDisplay(hWnd);

		// Count How Many Updates There will be
		if (fSend)
			iUpdates++;

		// Move to the Next Element
		pGdiNode = pGdiNode->pNext;
	}

	// Send the Number of Updates to the Client
	memset(szMessage,'\0',sizeof(szMessage));
	sprintf(szMessage,"%d",iUpdates);

	// Send the Number of Updates
	iSent = Transmit(MySocket,szMessage,strlen(szMessage));

	// Receive the Confirmation
	memset(szMessage,'\0',sizeof(szMessage));
	iRecv = recv(MySocket,szMessage,81,0);
	szMessage[iRecv] = '\0';

	// Check for Updates to Send
	if (iUpdates > 0)
	{
		// Point to the Beginning of the Gdi List
		pGdiNode = GdiStart.pNext;
		while (pGdiNode)
		{
			// Send the DIB if the DeskTop has Changed
			if (pGdiNode->Gdi.fChange)
			{
				int		iCompressions = 1;

				if (iCompressionLevel == 0) // No Compression
				{
					// Allocate the Compression Space w/ Room for the Code Table
					pGdiNode->Gdi.pDIBCompress = (char *)malloc(pGdiNode->Gdi.dwCompress);

					// Copy the Changed Bitmap to the Bitmap to Send
					memblast(pGdiNode->Gdi.pDIBCompress,pGdiNode->Gdi.pDIBChange,pGdiNode->Gdi.dwCompress);
					dwSendLen = pGdiNode->Gdi.dwCompress;
				}
				if (iCompressionLevel == 10) // Single Pass Huffman Compress
				{
					// Allocate the Compression Space w/ Room for the Code Table
					pGdiNode->Gdi.pDIBCompress = (char *)malloc(pGdiNode->Gdi.dwCompress + 1536);

					// Generate the Huffman Byte Tree Dictionary
					wTreeSize = HuffmanDictionary(pGdiNode->Gdi.pDIBChange,pGdiNode->Gdi.dwCompress,&dwByteTree[0],&dwCodes[0]);

					// Compress the Image using the Huffman Compression Scheme
					dwSendLen = HuffmanCompress(pGdiNode->Gdi.pDIBChange,pGdiNode->Gdi.dwCompress,wTreeSize,&dwByteTree[0],&dwCodes[0],pGdiNode->Gdi.pDIBCompress);
				}
				else if (iCompressionLevel == 11) // Multi Pass Huffman Compression
				{
					// Minimum Space is the Normal Size plus Maximum Dictionary Size
					dwMinCompress = pGdiNode->Gdi.dwCompress + 1536;

					// Allocate the Compression Space w/ Room for the Code Table
					pGdiNode->Gdi.pDIBCompress = (char *)malloc(dwMinCompress);

					// Allocate Space for a Temporary DIB
					pTempDIB = (char *)malloc(pGdiNode->Gdi.dwCompress);

					// Copy the Changed DIB to the Temporary DIB
					memblast(pTempDIB,pGdiNode->Gdi.pDIBChange,pGdiNode->Gdi.dwCompress);

					// Loop Until Maximum Compression Reached
					iCompressions = 0;
					dwCompLen = pGdiNode->Gdi.dwCompress;
					dwLastCompLen = dwCompLen;
					for (;;)
					{
						// Generate the Huffman Byte Tree Dictionary
						wTreeSize = HuffmanDictionary(pTempDIB,pGdiNode->Gdi.dwCompress,&dwByteTree[0],&dwCodes[0]);

						// Count the Compression Length
						dwCompLen = HuffmanCountCompress(pTempDIB,dwCompLen,wTreeSize,&dwCodes[0]);

						// Check for Compression
						if (dwCompLen < dwMinCompress)
						{
							// Compress the Image using the Huffman Compression Scheme
							dwSendLen = HuffmanCompress(pTempDIB,dwLastCompLen,wTreeSize,&dwByteTree[0],&dwCodes[0],pGdiNode->Gdi.pDIBCompress);

							// Copy the Output to the Input
							memblast(pTempDIB,pGdiNode->Gdi.pDIBCompress,dwSendLen);

							// Update the Compression Count
							dwMinCompress = dwSendLen;
							dwLastCompLen = dwCompLen;

							// Update the Number of Compressions
							iCompressions++;
						}
						else
							break;
					}

					// Free the Temporary DIB
					free(pTempDIB);
				}
				else if (iCompressionLevel == 12) // Run Length Encoding
				{
					// Allocate the Compression Space for Worst Case Scenario
					pGdiNode->Gdi.pDIBCompress = (char *)malloc(pGdiNode->Gdi.dwCompress * 3 + 4);

					// Run Length Encode the Image
					dwSendLen = RunLengthEncode(pGdiNode->Gdi.pDIBChange,pGdiNode->Gdi.dwCompress,pGdiNode->Gdi.pDIBCompress);
				}
				else if (iCompressionLevel == 13) // Run Length Encoding with Huffman
				{
					// Allocate the Compression Space for Worst Case Scenario
					pTempDIB = (char *)malloc(pGdiNode->Gdi.dwCompress * 3 + 4);
					pGdiNode->Gdi.pDIBCompress = (char *)malloc(pGdiNode->Gdi.dwCompress * 3 + 4);

					// Run Length Encode the Image
					dwCompLen = RunLengthEncode(pGdiNode->Gdi.pDIBChange,pGdiNode->Gdi.dwCompress,pTempDIB);

					// Generate the Huffman Byte Tree Dictionary
					wTreeSize = HuffmanDictionary(pTempDIB,dwCompLen,&dwByteTree[0],&dwCodes[0]);

					// Compress the Run Lenght Encoded Image using the Huffman Compression Scheme
					dwSendLen = HuffmanCompress(pTempDIB,dwCompLen,wTreeSize,&dwByteTree[0],&dwCodes[0],pGdiNode->Gdi.pDIBCompress);

					// Free the Temp DIB
					free(pTempDIB);
				}

				// Build the Bitmap Control Message
				memset(szMessage,'\0',sizeof(szMessage));
				sprintf(szMessage,"%d;%d;%d;%ld;%ld;%ld;",
					iCompressions,
					pGdiNode->Gdi.iGridX,pGdiNode->Gdi.iGridY,
					pGdiNode->Gdi.iStartPos,
					pGdiNode->Gdi.dwCompress,dwSendLen);

				// Send the Control Message
				iSent = Transmit(MySocket,szMessage,strlen(szMessage));

				// Receive the Confirmation
				memset(szMessage,'\0',sizeof(szMessage));
				iRecv = recv(MySocket,szMessage,81,0);
				szMessage[iRecv] = '\0';

				// Send the Compressed DIB
				fTransmit = Transmit(MySocket,pGdiNode->Gdi.pDIBCompress,dwSendLen);

				// Free the Compressed DIB
				free(pGdiNode->Gdi.pDIBCompress);

				// Receive the Confirmation
				memset(szMessage,'\0',sizeof(szMessage));
				iRecv = recv(MySocket,szMessage,81,0);
				szMessage[iRecv] = '\0';

				/* Test all my Compression Methods for the Best Time and Size */
/*
				// Huffman Compression
				iStart = clock();

				// Set the Compressions
				iCompressions = 1;

				// Allocate the Compression Space w/ Room for the Code Table
				pGdiNode->Gdi.pDIBCompress = (char *)malloc(pGdiNode->Gdi.dwCompress + 1536);

				// Generate the Huffman Byte Tree Dictionary
				wTreeSize = HuffmanDictionary(pGdiNode->Gdi.pDIBChange,pGdiNode->Gdi.dwCompress,&dwByteTree[0],&dwCodes[0]);

				// Compress the Image using the Huffman Compression Scheme
				dwSendLen = HuffmanCompress(pGdiNode->Gdi.pDIBChange,pGdiNode->Gdi.dwCompress,wTreeSize,&dwByteTree[0],&dwCodes[0],pGdiNode->Gdi.pDIBCompress);

				// Free the Compressed DIB
				free(pGdiNode->Gdi.pDIBCompress);

				// Generate the Duration
				iFinish = clock();
				iDuration = (double)(iFinish - iStart) / CLOCKS_PER_SEC;

				// Output to the File
				fprintf(f1,"Huffman  : %5.2f %2d %2d %2d %8ld %8ld\n",
					iDuration,pGdiNode->Gdi.iGridX,pGdiNode->Gdi.iGridY,
					iCompressions,pGdiNode->Gdi.dwCompress,dwSendLen);

				// MultiPass Huffman
				iStart = clock();

				// Minimum Space is the Normal Size plus Maximum Dictionary Size
				dwMinCompress = pGdiNode->Gdi.dwCompress + 1536;

				// Allocate the Compression Space w/ Room for the Code Table
				pGdiNode->Gdi.pDIBCompress = (char *)malloc(dwMinCompress);

				// Allocate Space for a Temporary DIB
				pTempDIB = (char *)malloc(pGdiNode->Gdi.dwCompress);

				// Copy the Changed DIB to the Temporary DIB
				memblast(pTempDIB,pGdiNode->Gdi.pDIBChange,pGdiNode->Gdi.dwCompress);

				// Loop Until Maximum Compression Reached
				iCompressions = 0;
				dwCompLen = pGdiNode->Gdi.dwCompress;
				dwLastCompLen = dwCompLen;
				for (;;)
				{
					// Generate the Huffman Byte Tree Dictionary
					wTreeSize = HuffmanDictionary(pTempDIB,pGdiNode->Gdi.dwCompress,&dwByteTree[0],&dwCodes[0]);

					// Count the Compression Length
					dwCompLen = HuffmanCountCompress(pTempDIB,dwCompLen,wTreeSize,&dwCodes[0]);

					// Check for Compression
					if (dwCompLen < dwMinCompress)
					{
						// Compress the Image using the Huffman Compression Scheme
						dwSendLen = HuffmanCompress(pTempDIB,dwLastCompLen,wTreeSize,&dwByteTree[0],&dwCodes[0],pGdiNode->Gdi.pDIBCompress);

						// Copy the Output to the Input
						memblast(pTempDIB,pGdiNode->Gdi.pDIBCompress,dwSendLen);

						// Update the Compression Count
						dwMinCompress = dwSendLen;
						dwLastCompLen = dwCompLen;

						// Update the Number of Compressions
						iCompressions++;
					}
					else
						break;
				}

				// Free the Temporary DIB
				free(pTempDIB);

				// Free the Compressed DIB
				free(pGdiNode->Gdi.pDIBCompress);

				// Generate the Duration
				iFinish = clock();
				iDuration = (double)(iFinish - iStart) / CLOCKS_PER_SEC;

				// Output to the File
				fprintf(f1,"MHuffman : %5.2f %2d %2d %2d %8ld %8ld\n",
					iDuration,pGdiNode->Gdi.iGridX,pGdiNode->Gdi.iGridY,
					iCompressions,pGdiNode->Gdi.dwCompress,dwSendLen);

				// Run Length Encoding
				iStart = clock();
			
				// Set the Compressions
				iCompressions = 1;

				// Allocate the Compression Space for Worst Case Scenario
				pGdiNode->Gdi.pDIBCompress = (char *)malloc(pGdiNode->Gdi.dwCompress * 3 + 4);

				// Run Length Encode the Image
				dwSendLen = RunLengthEncode(pGdiNode->Gdi.pDIBChange,pGdiNode->Gdi.dwCompress,pGdiNode->Gdi.pDIBCompress);

				// Free the Compressed DIB
				free(pGdiNode->Gdi.pDIBCompress);

				// Generate the Duration
				iFinish = clock();
				iDuration = (double)(iFinish - iStart) / CLOCKS_PER_SEC;

				// Output to the File
				fprintf(f1,"RLE      : %5.2f %2d %2d %2d %8ld %8ld\n",
					iDuration,pGdiNode->Gdi.iGridX,pGdiNode->Gdi.iGridY,
					iCompressions,pGdiNode->Gdi.dwCompress,dwSendLen);

				// Run Length with Huffman
				iStart = clock();

				// Set the Compressions
				iCompressions = 1;

				// Allocate the Compression Space for Worst Case Scenario
				pTempDIB = (char *)malloc(pGdiNode->Gdi.dwCompress * 3 + 4);
				pGdiNode->Gdi.pDIBCompress = (char *)malloc(pGdiNode->Gdi.dwCompress * 3 + 4);

				// Run Length Encode the Image
				dwCompLen = RunLengthEncode(pGdiNode->Gdi.pDIBChange,pGdiNode->Gdi.dwCompress,pTempDIB);

				// Generate the Huffman Byte Tree Dictionary
				wTreeSize = HuffmanDictionary(pTempDIB,dwCompLen,&dwByteTree[0],&dwCodes[0]);

				// Compress the Run Lenght Encoded Image using the Huffman Compression Scheme
				dwSendLen = HuffmanCompress(pTempDIB,dwCompLen,wTreeSize,&dwByteTree[0],&dwCodes[0],pGdiNode->Gdi.pDIBCompress);

				// Free the Temp DIB
				free(pTempDIB);

				// Free the Compressed DIB
				free(pGdiNode->Gdi.pDIBCompress);

				// Generate the Duration
				iFinish = clock();
				iDuration = (double)(iFinish - iStart) / CLOCKS_PER_SEC;

				// Output to the File
				fprintf(f1,"RLE Huff : %5.2f %2d %2d %2d %8ld %8ld %8ld\n\n",
					iDuration,pGdiNode->Gdi.iGridX,pGdiNode->Gdi.iGridY,
					iCompressions,pGdiNode->Gdi.dwCompress,dwCompLen,dwSendLen);
				*/
			}

			// Move to the Next Element
			pGdiNode = pGdiNode->pNext;
		}
	}

	// Return the Number of Updates
	return iUpdates;
}

// This function was modified from a HTTP server code that sends data.  I modified
// it to send my DIB data
// Transmit Data
BOOL Transmit(SOCKET MySocket,char *pData,DWORD dwLength)
{
	// Overlapped Structure for Send
	WSAOVERLAPPED	olSend;

	// Event Handling
	WSAEVENT	gheventOlSock;
	WSAEVENT	eventArray[2];

	// WSABuf for WSASend
	WSABUF		buffSend;

	// WSASend Variables
	DWORD		dwRet,dwNumBytes,dwFlags;
	int			nWSAError;

	// Error Variables
	char		szError[81];

	// Create a Signaling Event for Send Completion
	gheventOlSock = WSACreateEvent();
	eventArray[0] = gheventOlSock;

	// Initialize the Overlapped Send Structure
	ZeroMemory(&olSend, sizeof(WSAOVERLAPPED));

	// Set the Signaling Event for the Send Overlapped Structure
	olSend.hEvent= gheventOlSock;

	// Set the Buffer Information
	buffSend.len = dwLength;
	buffSend.buf = pData;

	// Send in a Continuous until dwSendLen Bytes are Sent
	while (TRUE)  //we will send in a loop until nSendSize bytes are sent
	{
		if ((dwRet = WSASend(MySocket,&buffSend,1,&dwNumBytes,0,&olSend,NULL)) == SOCKET_ERROR)
		{
			// Expect IO Pending until all data is sent
			nWSAError= WSAGetLastError();
			if (nWSAError != ERROR_IO_PENDING)
			{
				sprintf(szError,"WSASend failed with error %d\n",nWSAError);
				MessageBox(NULL,szError,"Server",MB_OK);
			}
		}

		//
		//  eventArray contains gheventOlSock.
		//  gheventOlSock is set in olSend only when no completion function is used.
		//  When the overlapped send completes, gheventOlSock is going to  signal.
		//
		//  For overlapped send with completion function, gheventOlSock is not set in
		//  olSend. So gheventOlSock is not going to signal, however the last param
		//  of WSAWaitForMultipleEvents is going to put this thread into an alertable
		//  wait state. When overlapped Send completes and completion
		//  function gets called, this Wait returns.
		//
			
		if (WSAWaitForMultipleEvents(1,eventArray,FALSE,WSA_INFINITE,FALSE) == WSA_WAIT_FAILED)
		{
			sprintf(szError,"WSAWaitForMultipleEvents failed %d\n", WSAGetLastError());
			MessageBox(NULL,szError,"Server",MB_OK);
		} 

		//
		// Reset the gheventOlSock
		//
		WSAResetEvent(eventArray[0]);

		if (WSAGetOverlappedResult(MySocket,&olSend,&dwNumBytes,FALSE,&dwFlags) == FALSE)
		{
			sprintf(szError,"WSAGetOverlappedResult failed with error %d\n", WSAGetLastError());
			MessageBox(NULL,szError,"Server",MB_OK);
		}
			
		// An overlapped write completes doesn't necessary mean all the data to send are sent. 
		buffSend.len -= dwNumBytes;
		if (buffSend.len == 0) 
			break;
		else 
			buffSend.buf += dwNumBytes;
	}

	// Close the Signaling Event
	WSACloseEvent(gheventOlSock);

	return TRUE;
}

// This function was downloaded from some socket site on the internet
// Sorry but I can't remember the fellow's name.  If you recognize this as
// yours then put your name in it.
////////////////////////////////////////////////////////////
// int SelectProtocols(
//					   DWORD dwSetFlags,
//					   DWORD dwNotSetFlags,
//					   LPWSAPROTOCOL_INFO lpProtocolBuffer,
//					   LPDWORD lpdwBufferLength
//					   )
//
// Retrieves information about available transport protocols
// that meet the criteria indicated by dwSetFlags and 
// dwNotSetFlags
//
// PARAMETERS
//
// dwSetFlags			A bitmask of values to ensure
//						are set in the protocol's
//						WSAPROTOCOL_INFO.dwServiceFlags1 
//						field.
//
// dwNotSetFlags		A bitmask of values to ensure
//						are NOT set in the protocol's
//						WSAPROTOCOL_INFO.dwServiceFlags1 
//						field.
//
// lpProtocolBuffer		The buffer to be filled with
//						WSAPROTOCOL_INFO structures.
//
// lpdwBufferLength		On input, the size in bytes of 
//						the buffer pointed to by the
//						lpProtocolBuffer parameter.
//						On ouput, the minimum size the
//						buffer must be to retrieve all
//						of the requested information.
//
// REMARKS
//
// SelectProtocols() fills the supplied buffer with 
// WSAPROTOCOL_INFO structures for all protocols where the 
// flags specified in dwSetFlags are set and all flags in 
// dwNotSetFlags are NOT set.
//
// Example: To retrieve information about all installed 
// protocols that are connection-oriented and reliable,
// call SelectProtocols() like this:
//
// nRet = SelectProtocols(XP1_GUARANTEED_DELIVERY|XP1_GUARANTEED_ORDER,
//						  XP1_CONNECTIONLESS,
//						  lpProtocolBuffer,
//						  &dwBufLen);
//
// In this example, SelectProtocols() will return information
// about all installed protocols and protocol chains that
// have the XP1_GUARANTEED_DELIVERY and XP1_GUARANTEED_ORDER
// flags set and that also don't have XP1_CONNECTIONLESS set.
//
// RETURN VALUES
//
// If no error occurs, SelectProtocols() returns the number of
// WSAPROTOCOL_INFO structure copied to the supplied buffer.
// If an error occurs, it returns SOCKET_ERROR and a specific
// error code can be found with WSAGetLastError();
//
// Modified to select only the "MSAFD Tcpip [TCP/IP]" protocol
//
int SelectProtocols(DWORD dwSetFlags,DWORD dwNotSetFlags,LPWSAPROTOCOL_INFO lpProtocolBuffer,LPDWORD lpdwBufferLength,WSAPROTOCOL_INFO *pProtocol)
{
	LPBYTE				pBuf;
	LPWSAPROTOCOL_INFO	pInfo;
	DWORD				dwNeededLen;
	LPWSAPROTOCOL_INFO	pRetInfo;
	DWORD				dwRetLen;
	int					nCount;
	int					nMatchCount;
	int					nRet;

	// Determine needed buffer size
	dwNeededLen = 0;
	nRet = WSAEnumProtocols(NULL, NULL, &dwNeededLen);
	if (nRet == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAENOBUFS)
			return SOCKET_ERROR;
	}

	// Allocate the buffer
	pBuf = malloc(dwNeededLen);
	if (pBuf == NULL)
	{
		WSASetLastError(WSAENOBUFS);
		return SOCKET_ERROR;
	}

	// Make the "real" call
	nRet = WSAEnumProtocols(NULL,(LPWSAPROTOCOL_INFO)pBuf,&dwNeededLen);
	if (nRet == SOCKET_ERROR)
	{
		free(pBuf);
		return SOCKET_ERROR;
	}

	// Helper macros for selecting protocols
	#define REJECTSET(f) \
	    ((dwSetFlags & f) && !(pInfo->dwServiceFlags1 & f))
	#define REJECTNOTSET(f) \
	    ((dwNotSetFlags &f) && (pInfo->dwServiceFlags1 & f))
	#define REJECTEDBY(f) (REJECTSET(f) || REJECTNOTSET(f))

	// Loop through the protocols making selections
	pInfo = (LPWSAPROTOCOL_INFO)pBuf;	
	pRetInfo = lpProtocolBuffer;
	dwRetLen = 0;
	nMatchCount = 0;
	for(nCount = 0; nCount < nRet; nCount++)
	{
		// Check all of the requested flags
		while(1)
		{
			if (REJECTEDBY(XP1_CONNECTIONLESS))
				break;
			if (REJECTEDBY(XP1_GUARANTEED_DELIVERY))
				break;
			if (REJECTEDBY(XP1_GUARANTEED_ORDER))
				break;
			if (REJECTEDBY(XP1_MESSAGE_ORIENTED))
				break;
			if (REJECTEDBY(XP1_PSEUDO_STREAM))
				break;
			if (REJECTEDBY(XP1_GRACEFUL_CLOSE))
				break;
			if (REJECTEDBY(XP1_EXPEDITED_DATA))
				break;
			if (REJECTEDBY(XP1_CONNECT_DATA))
				break;
			if (REJECTEDBY(XP1_DISCONNECT_DATA))
				break;
			if (REJECTEDBY(XP1_SUPPORT_BROADCAST)) 
				break;
			if (REJECTEDBY(XP1_SUPPORT_MULTIPOINT))
				break;
			if (REJECTEDBY(XP1_MULTIPOINT_DATA_PLANE))
				break;
			if (REJECTEDBY(XP1_QOS_SUPPORTED))
				break;
			if (REJECTEDBY(XP1_UNI_SEND))
				break;
			if (REJECTEDBY(XP1_UNI_RECV))
				break;
			if (REJECTEDBY(XP1_IFS_HANDLES))
				break;
			if (REJECTEDBY(XP1_PARTIAL_MESSAGE))
				break;

			// If we made it here, the protocol meets all requirements
			dwRetLen += sizeof(WSAPROTOCOL_INFO);

			// Check if we are out of buffer space
			if (dwRetLen > *lpdwBufferLength)
			{
				// The supplied buffer is too small
				WSASetLastError(WSAENOBUFS);
				*lpdwBufferLength = dwNeededLen;
				free(pBuf);
				return SOCKET_ERROR;
			}
			nMatchCount++;

			// Copy this protocol to the caller's buffer
			memblast(pRetInfo,pInfo,sizeof(WSAPROTOCOL_INFO));

			// Check for the Proper Protocol
			if (strcmp(pInfo->szProtocol,"MSAFD Tcpip [TCP/IP]") == 0)
				memblast(pProtocol,pInfo,sizeof(WSAPROTOCOL_INFO));

			pRetInfo++;
			break;
		}
		pInfo++;
	}
	free(pBuf);
	*lpdwBufferLength = dwRetLen;
	return(nMatchCount);
}

// Copy memory range from one location to another
void memblast(void* dest,void* src,DWORD count)
{
	DWORD	iCount;

	__asm
	{
		// Align Count to a DWORD Boundary
		MOV		ECX,count
		SHR		ECX,2
		SHL		ECX,2
		MOV		iCount,ECX

		// Copy All the DWORDs (32 bits at a Time)
		MOV		ESI,src		// Copy the Source Address to the Register
		MOV		EDI,dest	// Copy the Destination to the Register
		MOV		ECX,iCount	// Copy the Count to the Register
		SHR		ECX,2		// Divide Count by 4 for DWORD Copy
		REP		MOVSD		// Move all the Source DWORDs to the Dest DWORDs

		// Get the Remaining Bytes to Copy
		MOV		ECX,count
		MOV		EAX,iCount
		SUB		ECX,EAX

		// Exit if All Bytes Copied
		JZ		Exit

		// Copy the Remaining BYTEs (8 bits at a Time)
		MOV		ESI,src		// Copy the Source Address to the Register
		ADD		ESI,EAX		// Set the Starting Point of the Copy
		MOV		EDI,dest	// Copy the Destination to the Register
		ADD		EDI,EAX		// Set the Destination Point of the Copy
		REP		MOVSB		// Move all the Source BYTEs to the Dest BYTEs
		Exit:
	}
}