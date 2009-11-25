// Module Name: Client.c
//
// Description:
//    Receive the Desktop Screen from the Server
//
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include "client.h"
#include "command.h"
#include "gdi.h"
#include "HuffCompress.h"
#include "RLE.h"
#include "time.h"

#define DEFAULT_PORT        5150
#define REFRESH_MSG			"REFRESH"
#define SETFLAGS			XP1_GUARANTEED_DELIVERY|XP1_GUARANTEED_ORDER
#define NOTSETFLAGS			XP1_CONNECTIONLESS
#define	LPBMIH				LPBITMAPINFOHEADER

BOOL	bSendOnly = FALSE;			// Send data only; don't receive
BOOL	fSending = FALSE;
BOOL	fReceiving = FALSE;
DWORD	iLen;
char	*pDIBitmap;
int		iScreenWidth,iScreenHeight;
int		iWidth,iHeight,iWidthX,iHeightY;
int		iWidth1,iWidth2,iHeight1,iHeight2;
int		iCompressionLevel;
BOOL	fDIBitmap = FALSE;
LPBMIH	lpBitmapIH;
struct	sockaddr_in	server;
SOCKET	sClient;
BOOL	fRefreshing = FALSE;
BOOL	fConnected = FALSE;
int		nGridX = 8,nGridY = 4;
BOOL	fGridX = FALSE,fGridY = FALSE;
WORD	bmBitsPixel = 4;

// Hold the Pointers to the Regional Display DIBs
struct	GdiList		GdiStart;
struct	GdiList		*pGdiNode;

// Select the TCPIP Protocol with Guaranteed Delivery and Order
int SelectProtocols(DWORD dwSetFlags,DWORD dwNotSetFlags,LPWSAPROTOCOL_INFO lpProtocolBuffer,LPDWORD lpdwBufferLength,WSAPROTOCOL_INFO *Protocol);

// Initialize the Regional Bitmap Status
void InitGrids()
{
	int		iLoop,jLoop,nGrid;
	struct	GdiDS	Gdi;

	// Build the Regional Bitmap List and Set the Status to FALSE
	Gdi.fDIBitmap = FALSE;
	GdiStart.pNext = NULL;
	pGdiNode = &GdiStart;

	// Grid the Screen
	if ((nGridX > 0) && (nGridY > 0))
	{
		for (iLoop = 0;iLoop < nGridX;iLoop++)
		{
			for (jLoop = 0;jLoop < nGridY;jLoop++)
			{
				// Set the Grid Coordinates
				Gdi.iGridX = iLoop;
				Gdi.iGridY = jLoop;

				// Add the Gdi to the List
				pGdiNode = Add_Gdi(pGdiNode,Gdi);
			}
		}
	}
	else // One Grid Component not Used
	{
		nGrid = max(nGridX,nGridY);
		for (iLoop = 0;iLoop < nGrid;iLoop++)
		{
			// Set the X Grid Coordinates
			if (nGridX > 0)
				Gdi.iGridX = iLoop;
			else
				Gdi.iGridX = 0;

			// Set the Y Grid Coordinates
			if (nGridY > 0)
				Gdi.iGridY = iLoop;
			else
				Gdi.iGridY = 0;

			// Add the Gdi to the List
			pGdiNode = Add_Gdi(pGdiNode,Gdi);
		}
	}

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
}

// Load Winsock and Connect to the Server
int LoadWinsock(HWND hWnd,char *szIP)
{
	WSADATA				wsd;
	DWORD				dwLen;
	int					nRet,nZero;
	LPBYTE				pBuf;
	WSAPROTOCOL_INFO	Protocol;
	char				szString[81];
	char				szMessage[81];

	// Load Winsock Ver 2.2
	if (WSAStartup(0x202,&wsd) != 0)
		return 1;

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

	// Free the buffer
	free(pBuf);

	// Create the socket, and attempt to connect to the server
//	sClient = WSASocket(AF_INET,SOCK_STREAM,IPPROTO_IP,&Protocol,0,WSA_FLAG_OVERLAPPED);
//	sClient = WSASocket(AF_INET,SOCK_STREAM,IPPROTO_IP,&Protocol,0,SOCK_STREAM);
	sClient = WSASocket(AF_INET,SOCK_STREAM,IPPROTO_IP,NULL,0,SOCK_STREAM);
	if (sClient == INVALID_SOCKET)
		return 1;

	// Disable Recv buffering on the socket.  Setting SO_RCVBUF
	// to 0 causes winsock to stop bufferring recv and perform
	// recv directly to our buffers, thereby reducing CPU
	// usage.
	nZero = 0;
	setsockopt(sClient,SOL_SOCKET,SO_RCVBUF,(char *)&nZero,sizeof(nZero));

	// Set the Server Information
	server.sin_family = AF_INET;
	server.sin_port = htons(DEFAULT_PORT);
	server.sin_addr.s_addr = inet_addr(szIP);

	// Connect to the Server
	if (connect(sClient,(struct sockaddr *)&server,sizeof(server)) == SOCKET_ERROR)
	{
		memset(szString,'\0',sizeof(szString));
		sprintf(szString,"Connect() failed: %d",WSAGetLastError());
		MessageBox(NULL,szString,"Client Socket Error",MB_OK);
		return 1;
	}

	// Get the Server Screen Resolution
	GetResolution();

	// Set the Number of Grids to Receive
	SetGrids(hWnd);

	// Set the Compression Level
	memset(szMessage,'\0',sizeof(szMessage));
	sprintf(szMessage,"WM_COMP;%d;0;0;0;\0",iCompressionLevel);
	SendCommand(hWnd,1,szMessage);

	// Get the Screen for the First Time
	UpdateRegionalScreen(hWnd,sClient,TRUE);

	return 0;
}

// Get the Server Grids Resolution
void SetGrids(HWND hWnd)
{
	char	szMessage[81];

	// Clear the Previous Grid Settings
	Clear_Gdi(&GdiStart);

	// Send the Message to Get the Resolution
	memset(szMessage,'\0',sizeof(szMessage));
	sprintf(szMessage,"WM_GRID;%d;%d;0;0;\0",nGridX,nGridY);
	SendCommand(hWnd,1,szMessage);

	// Initialize the Grids in the Gdi List
	InitGrids();
}

// Get the Server Resolution
void GetResolution()
{
	int		iSend,iRecv;
	char	szMessage[81];
	char	szRecv[81];

	// Send the Message to Get the Resolution
	memset(szMessage,'\0',sizeof(szMessage));
	sprintf(szMessage,"RESOLUTION\0");
	iSend = Send(sClient,szMessage);

	// Receive the Width
	iRecv = Recv(sClient,szRecv,80);
	iWidth = atoi(szRecv);

	// Send Confirmation
	memset(szMessage,'\0',sizeof(szMessage));
	sprintf(szMessage,"OK\0");
	iSend = Send(sClient,szMessage);

	// Receive the Height
	iRecv = Recv(sClient,szRecv,80);
	iHeight = atoi(szRecv);

	// Send Confirmation
	memset(szMessage,'\0',sizeof(szMessage));
	sprintf(szMessage,"OK\0");
	iSend = Send(sClient,szMessage);
}

// Send and Receive data from the Server
int SendCommand(HWND hWnd,int iParm,char *szWMMessage)
{
	int		iSent;

	// Check the Parameter for Handling Operations
	if (iParm == 0)
	{
		// Update the Screen
		UpdateRegionalScreen(hWnd,sClient,FALSE);
	}
	else if (iParm == 1)
	{
		// Send the Windows Command
		iSent = Send(sClient,szWMMessage);
	}

	return 0;
}

// Send Data to the Server
int Send(SOCKET Socket,char *szSend)
{
	int		iSent;

	// Set the Send Flag
	fSending = TRUE;

	// Send the Data
	iSent = send(Socket,szSend,strlen(szSend),0);

	// Set the Send Flag
	fSending = FALSE;

	// Return the Number of Characters Sent
	return iSent;
}

// Receive Data from the Server
int Recv(SOCKET Socket,char *szRecv,int iRecvLen)
{
	int		iRecv;

	// Set the Receiving Flag
	fReceiving = TRUE;

	// Receive the Data into the Buffer
	iRecv = recv(Socket,szRecv,iRecvLen,0);
	if (iRecv == SOCKET_ERROR || iRecv == 0)
		MessageBox(NULL,"NO DATA or SOCKET ERROR","Client",MB_OK);

	// Null Terminate the Buffer
	szRecv[iRecv] = '\0';

	// Set the Receiving Flag
	fReceiving = FALSE;

	// Return the Number of Characters Received
	return iRecv;
}

// Send a Message to the Server for a Screen Refresh
void UpdateRegionalScreen(HWND hWnd,SOCKET sClient,BOOL fFirstTime)
{
	LPBMIH	lpBMIH;
	char	*pDIB;
	char	*pDIBCompress;
	char	*pStartDIB;
	DWORD	iSent,iRecv;
	DWORD	iCompLen,iNewLen,iRLELen,iStartPos;
	int		iGridX,iGridY;
	int		iUpdates,iLoop,iCompressions,jLoop;
	char	szMessage[81];

	// Command List Variables
	struct	CommandList	CommandStart;
	struct	CommandList	*pCommandNode;
	struct	CommandDS	Command;
	char				*pDest;
	int					iLoc1,iLoc2,nChar;

	// Temporary Pointer to DIB
	char				*pTempDIB;

	// Check for a Current Refresh
	if (!fRefreshing)
	{
		// Initialize the Command List
		CommandStart.pNext = NULL;

		// Set the Refresh Status
		fRefreshing = TRUE;

		// Copy the Default Message
		strcpy(szMessage,REFRESH_MSG);

		// Send the Message to the Server
		iSent = Send(sClient,szMessage);

		// Receive the Number of Updates
		memset(szMessage,'\0',sizeof(szMessage));
		iRecv = Recv(sClient,szMessage,80);
		if (iRecv == SOCKET_ERROR || iRecv == 0)
			MessageBox(NULL,"NO DATA or SOCKET ERROR","Client",MB_OK);
		iUpdates = atoi(szMessage);

		// Send the Confirmation Message
		strcpy(szMessage,"OK\0");
		iSent = Send(sClient,szMessage);

		// Loop Through the Grids and Receive the Update Status
		if (iUpdates > 0)
		{
			// Loop Through the Number of Updates
			pGdiNode = GdiStart.pNext;
			for (iLoop = 0;iLoop < iUpdates;iLoop++)
			{
				// Point to the Beginning of the Command List
				pCommandNode = &CommandStart;

				// Receive the Regional Bitmap Control Message
				memset(szMessage,'\0',sizeof(szMessage));
				iRecv = Recv(sClient,szMessage,80);
				if (iRecv == SOCKET_ERROR || iRecv == 0)
					MessageBox(NULL,"NO DATA or SOCKET ERROR","Client",MB_OK);

				// Parse the Command String
				iLoc1 = 0;
				while (pDest = strchr(szMessage,';'))
				{
					// Parse the Command
					iLoc2 = pDest - szMessage;
					nChar = iLoc2 - iLoc1;
					memset(Command.szElement,'\0',sizeof(Command.szElement));
					strncpy(Command.szElement,&szMessage[iLoc1],nChar);

					// Add the Command to the Command Stack
					pCommandNode = Add_Command(pCommandNode,Command);

					// Update String
					memset(&szMessage[iLoc2],':',1);

					// Update the Starting Position
					iLoc1 = iLoc2 + 1;
				}

				// Process the Command
				pCommandNode = CommandStart.pNext;
				if (pCommandNode)
				{
					// Get the Number of Compressions
					iCompressions = atoi(pCommandNode->Command.szElement);
					pCommandNode = pCommandNode->pNext;

					// Get the Grid Coordinates
					iGridX = atoi(pCommandNode->Command.szElement);
					pCommandNode = pCommandNode->pNext;
					iGridY = atoi(pCommandNode->Command.szElement);
					pCommandNode = pCommandNode->pNext;

					// Get the Starting Position of the Data
					iStartPos = atol(pCommandNode->Command.szElement);
					pCommandNode = pCommandNode->pNext;

					// Get the Number of UnCompressed Bytes
					iLen = atol(pCommandNode->Command.szElement);
					pCommandNode = pCommandNode->pNext;

					// Get the Number of Compressed Bytes
					iCompLen = atol(pCommandNode->Command.szElement);
					pCommandNode = pCommandNode->pNext;
				}

				// Allocate enough memory to hold the Compressed DIB
				if (iLen > iCompLen)
					pDIBCompress = (char *)malloc(iLen);
				else
					pDIBCompress = (char *)malloc(iCompLen);

				// Loop Throught the List
				while (pGdiNode)
				{
					// Look for a Grid Match
					if ((pGdiNode->Gdi.iGridX == iGridX) &&
						(pGdiNode->Gdi.iGridY == iGridY))
					{
						// Check for Receiving DIB for the First Time
						if (!pGdiNode->Gdi.fDIBitmap)
						{
							// Allocate the Memory for the Global DIB
							pGdiNode->Gdi.pDIBitmap = malloc(iLen);
							memset(pGdiNode->Gdi.pDIBitmap,0,iLen);

							// Cast the Allocated Memory to a Bitmap Info Header
							pGdiNode->Gdi.lpBitmapIH = (LPBMIH)pGdiNode->Gdi.pDIBitmap;

							// Get the Rectangular Coordinates of the Region
							pGdiNode->Gdi.iWidth1 = iGridX * iWidthX;
							pGdiNode->Gdi.iWidth2 = iGridX * iWidthX + iWidthX;
							pGdiNode->Gdi.iHeight1 = iGridY * iHeightY;
							pGdiNode->Gdi.iHeight2 = iGridY * iHeightY + iHeightY;

							// Set the Total Screen Width
							iScreenWidth = iWidth;
							iScreenHeight = iHeight;

							// Allocate enough memory to hold the DIB
							pGdiNode->Gdi.pDIB = (char *)malloc(iLen);
							pGdiNode->Gdi.pStartDIB = pGdiNode->Gdi.pDIB;
						}

						// Send the Confirmation Message
						strcpy(szMessage,"OK\0");
						iSent = Send(sClient,szMessage);

						// Receive the Compressed DIB
						pStartDIB = pDIBCompress;
						Receive(sClient,pDIBCompress,iCompLen);

						// Point back to the beginning of the Memory
						pDIBCompress = pStartDIB;
						pStartDIB = pGdiNode->Gdi.pStartDIB;

						if (iCompressionLevel == 0)
						{
							// No Compression
							memblast(pGdiNode->Gdi.pDIB,pDIBCompress,iLen);
							iNewLen = iLen;
						}
						else if (iCompressionLevel == 10)
						{
							// UnCompress the DIB using the Huffman UnCompress
							iNewLen = HuffmanUnCompress((BYTE *)pDIBCompress,(BYTE *)pGdiNode->Gdi.pDIB);
						}
						else if (iCompressionLevel == 11) // Multi Pass Huffman
						{
							// Loop for the Number of Compressions
							for (jLoop = 0;jLoop < iCompressions;jLoop++)
							{
								// UnCompress the DIB using the Huffman UnCompress
								iNewLen = HuffmanUnCompress((BYTE *)pDIBCompress,(BYTE *)pGdiNode->Gdi.pDIB);

								// Copy the Output to the Input
								if ((jLoop + 1) < iCompressions)
									memblast(pDIBCompress,pGdiNode->Gdi.pDIB,iNewLen);
							}
						}
						else if (iCompressionLevel == 12) // Run Length Decode
						{
							iNewLen = RunLengthDecode((BYTE *)pDIBCompress,(BYTE *)pGdiNode->Gdi.pDIB);
						}
						else if (iCompressionLevel == 13) // Run Length Decode plus Huffman
						{
							char	*pTempDIB;

							// Get the UnCompressed Size of the RLE
							iLen = HuffmanGetSize((BYTE *)pDIBCompress);

							// Allocate Space for the Temp DIB
							pTempDIB = (char *)malloc(iLen);

							// UnCompress the RLE using the Huffman UnCompress
							iRLELen = HuffmanUnCompress((BYTE *)pDIBCompress,(BYTE *)pTempDIB);

							// UnCompress the DIB using the Run Lenght Decoder
							iNewLen = RunLengthDecode((BYTE *)pTempDIB,(BYTE *)pGdiNode->Gdi.pDIB);

							// Free the Temp DIB
							free(pTempDIB);
						}

						// Cast the Allocated Memory to a Bitmap Info Header
						pGdiNode->Gdi.pDIB = pGdiNode->Gdi.pStartDIB;
						lpBMIH = (LPBMIH)pGdiNode->Gdi.pDIB;

						// Copy the Bitmap
						if (fFirstTime)
						{
							// Use for the Assembler Code
							pTempDIB = pGdiNode->Gdi.pDIBitmap;

							// Get the Bitmap
							memblast(&pGdiNode->Gdi.pDIBitmap[iStartPos],pGdiNode->Gdi.pDIB,iNewLen);

							// Don't ReAllocate the Memory
							pGdiNode->Gdi.fDIBitmap = TRUE;
						}
						else
						{
							// Use for the Assembler Code
							pTempDIB = pGdiNode->Gdi.pDIBitmap;
							pDIB = pGdiNode->Gdi.pDIB;

							// Get the Delta of the Before and After Bitmaps
							__asm
							{
								MOV		ECX,iNewLen // Length of Loop
								SHR		ECX,2 // Divide by 4 for 4 bytes at a time
								MOV		EDI,pTempDIB
								ADD		EDI,iStartPos
								MOV		ESI,pDIB
								Addition:
								LODSD
								ADD		[EDI],EAX
								ADD		EDI,4
								DEC		ECX
								JNZ		Addition
							}
						}

						// Clear the Command List
						Clear_Command(&CommandStart);

						// Send the Confirmation Message
						strcpy(szMessage,"OK\0");
						iSent = Send(sClient,szMessage);
						break;
					}

					// Move to the Next GDI Element
					pGdiNode = pGdiNode->pNext;
				}

				// Free the Compressed DIB Memory
				free(pDIBCompress);
			}

			// Set the Bitmap for the First Time
			if (fFirstTime)
				fDIBitmap = TRUE;

			// Cause a WM_PAINT
			InvalidateRect(hWnd,NULL,FALSE);
		}

		// Set the Refresh Status
		fRefreshing = FALSE;
	}
}

// Receive Data
DWORD Receive(SOCKET Socket,char *pData,DWORD iLength)
{
	// Overlapped Structure for Send
	WSAOVERLAPPED	olRecv;

	// Event Handling
	WSAEVENT	gheventOlSock;
	WSAEVENT	eventArray[2];

	// WSABuf for WSASend
	WSABUF		buffRecv;

	// WSASend Variables
	DWORD		dwRet,dwNumBytes,dwFlags;
	int			nWSAError;

	// Number of Bytes Received
	DWORD		iNumBytes = 0;

	// Error Variables
	char		szError[81];

	// Create a Signaling Event for Send Completion
	gheventOlSock = WSACreateEvent();
	eventArray[0] = gheventOlSock;

	// Initialize the Overlapped Send Structure
	ZeroMemory(&olRecv,sizeof(WSAOVERLAPPED));

	// Set the Signaling Event for the Send Overlapped Structure
	olRecv.hEvent= gheventOlSock;

	// Set the Buffer Information
	buffRecv.len = iLength;
	buffRecv.buf = pData;

	// Set the Receiving Flag
	fReceiving = TRUE;

	// Loop Until All Data Received
	while (TRUE)
	{
		dwFlags = 0;
		dwNumBytes = 0;

		if ((dwRet = WSARecv(Socket,&buffRecv,1,&dwNumBytes,&dwFlags,&olRecv,NULL)) == SOCKET_ERROR) 
		{
			nWSAError = WSAGetLastError();
			if (nWSAError != ERROR_IO_PENDING)
			{
				sprintf(szError,"WSARecv failed with error %d\n",nWSAError);
				MessageBox(NULL,szError,"Client",MB_OK);
				return SOCKET_ERROR;
			}
		}

		//  eventArray contains gheventOlSock. 
		//  gheventOlSock is set in olRecv only when no completion function is used. 
		//  When the overlapped recv completes, gheventOlSock is going to signal.
		//
		//  For overlapped recv with completion function, gheventOlSock is not set in 
		//  olSend. So gheventOlSock is not going to signal, however the last param of 
		//  WSAWaitForMultipleEvents is going to put this thread into an alertable wait state. 
		//  When overlapped Recv completes and completion
		//  function gets called, this Wait returns.

		if (WSAWaitForMultipleEvents(1,eventArray,FALSE,WSA_INFINITE,FALSE) == WSA_WAIT_FAILED) 
		{
			sprintf(szError,"WSAWaitForMultipleEvents failed %d\n", WSAGetLastError());
			MessageBox(NULL,szError,"Client",MB_OK);
		} 

		// Reset the gheventOlSock
		WSAResetEvent(eventArray[0]);

		// Get the Number of Bytes Received
		if (WSAGetOverlappedResult(Socket,&olRecv,&dwNumBytes,FALSE,&dwFlags) == TRUE)
		{
			if (dwNumBytes == 0)
				break;
		} 
		else 
		{
			sprintf(szError,"WSAGetOverlappedResult failed with error %d\n", WSAGetLastError());
			MessageBox(NULL,szError,"Client",MB_OK);
			return SOCKET_ERROR;
		}
		
		// An overlapped recv completes doesn't necessary mean all the data to recv are recv. 
		buffRecv.len -= dwNumBytes;
		iNumBytes = iNumBytes + dwNumBytes;
		if (buffRecv.len == 0) 
			break;
		else 
			buffRecv.buf += dwNumBytes;
	}

	// Set the Receiving Flag
	fReceiving = FALSE;

	// Return the Number of Bytes Received
	return iNumBytes;
}

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
				memblast(pProtocol,pInfo, sizeof(WSAPROTOCOL_INFO));

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
