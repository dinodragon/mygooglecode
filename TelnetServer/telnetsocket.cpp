///////////////////////////////////////////////////////////////////////
// Filename: telnetsocket.cpp
//
// Date    : 27-May-2001
// Author  : J.Hogendoorn ( jeroenhog@gmx.net )
//
// Note    : this code may be used anywhere as long
//         : as this comment remains. 
//
///////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "telnetsocket.h"

//////////////////////////////////////////////////////////////////////
// Method  : constructor
// In      : none
// Out     : none
// Purpose : initializes some member vars
// Note    : 
CTelnetSocket::CTelnetSocket()
{
	m_sLastError  = "";
	m_iSock       = 0;
	m_iClientSock = 0;
	m_sClientIp   = "";
}

//////////////////////////////////////////////////////////////////////
// Method  : destructor
// In      : none
// Out     : none
// Purpose : cleans up windows socket stuff
// Note    : 
CTelnetSocket::~CTelnetSocket()
{
	// cleanup windows sockets
	WSACleanup();  
}

//////////////////////////////////////////////////////////////////////
// Method  : closeClientSocket
// In      : none
// Out     : none
// Purpose : closes the client socket
// Note    : 
void CTelnetSocket::closeClientSocket()
{
	closesocket(m_iClientSock);
}

//////////////////////////////////////////////////////////////////////
// Method  : closeServerSocket
// In      : none
// Out     : none
// Purpose : closes the server socket
// Note    : 
void CTelnetSocket::closeServerSocket()
{
	closesocket(m_iSock);
}

//////////////////////////////////////////////////////////////////////
// Method  : initialize
// In      : port number to run on
// Out     : true if succeeded, false if not
// Purpose : initializes the connection
// Note    : 
bool CTelnetSocket::initialize( DWORD dwPortNr )
{
	// Windows socket initialization
	WORD    wVersionRequested; 
	WSADATA wsaData; 
	wVersionRequested = MAKEWORD(1, 1); 

	// Find winsock version
	if ( WSAStartup(wVersionRequested, &wsaData) )
	{
		m_sLastError = "Incorrect winsock version";
		return false;
	}

	// create socket
	m_iSock = socket(AF_INET, SOCK_STREAM, 0);
	if ( m_iSock == INVALID_SOCKET  )
	{
		m_sLastError = "Error while creating socket";
		return false;
	}

	int iOptval = 1;
	if ( setsockopt( m_iSock, SOL_SOCKET, SO_REUSEADDR, (char *) &iOptval, sizeof(int)) )
	{
		m_sLastError = "setsockopt failed";
		return false;
	}

	m_siUs.sin_family      = AF_INET;
	m_siUs.sin_port        = htons( USHORT(dwPortNr) );
	m_siUs.sin_addr.s_addr = INADDR_ANY;

	// Bind to the given port
	if ( bind( m_iSock, (struct sockaddr *) &m_siUs, sizeof(m_siUs) ) )
	{
		m_sLastError = "bind failed";
		return false;
	}

	// change to passive socket
	if ( listen( m_iSock , SOMAXCONN ) )
	{
		m_sLastError = "listen failed";
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
// Method  : waitForConnection
// In      : none
// Out     : true if succeeded, false if not
// Purpose : waits for a client to connect
// Note    : 
bool CTelnetSocket::waitForConnection()
{
	// wait for port
	int         iLen        = sizeof( sockaddr_in );
	int         iClientSock = 0;

	// fill with zero terms
	memset( &m_siThem , 0 , sizeof( m_siThem) );

	// wait for connetion
	m_iClientSock = accept( m_iSock, (struct sockaddr *)&(m_siThem) , &iLen );
	if ( m_iClientSock == INVALID_SOCKET )
	{
		m_sLastError = "accept failed";
		return false;
	}

	// get client ip address
	char szClientIp[255];
	strncpy( szClientIp, inet_ntoa(m_siThem.sin_addr), 128);
	m_sClientIp = szClientIp;

	return true;
}

//////////////////////////////////////////////////////////////////////
// Method  : sendData
// In      : data to send
// Out     : true if succeeded, false if not
// Purpose : sends data to the client
// Note    : 
bool CTelnetSocket::sendData( const CString& sData )
{
	if ( send( m_iClientSock , sData , sData.GetLength() , 0 ) != sData.GetLength() )
	{
		m_sLastError = "sending data to client failed";
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
// Method  : waitForData
// In      : is password ( echo's * in stead of types char )
// Out     : true if succeeded, false if not, and the data that was typed
// Purpose : waits for a user to type something followed by ENTER
// Note    : only backspace is implemented as a 'special' char
bool CTelnetSocket::waitForData( CString& sData , bool bIsPassword /*false*/ )
{
	// global would be faster....
	CString sValidChars = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890~`!@#$%^&*()-_=+{[}]\\|;:'\"<,>.?/";

	int  iSizeEchoBuf = 0;
	char szBuf[4];
	char szEchoBuf[4];

	// empty the buffers
	memset( szBuf     , 0 , 4 );
	memset( szEchoBuf , 0 , 4 );

	while ( szBuf[0] != 13 )
	{	
		// empty the buffers
		memset( szBuf     , 0 , 4 );
		memset( szEchoBuf , 0 , 4 );
		iSizeEchoBuf = 0;

		// receive max 3 bytes ( e.g. arrow up will be chr(27) + [ + A )
		int ierr = recv( m_iClientSock, szBuf , 4 , 0);
		if (ierr < 1 ) 
		{ 
			m_sLastError = "receiving data from client failed";
			return false;
		} 

		if (( szBuf[0]                     ==  13 ) ||	// enter pressed
		    ( szBuf[0]                     ==  8  ) ||	// backspace
			( sValidChars.Find( szBuf[0] ) != -1  ))	// 'ordinary' character
		{

			if ( szBuf[0] == 8 ) // backspace
			{
				// backspace pressed
				if ( sData.GetLength() > 0 )
				{
					// cut off one char
					sData        = sData.Mid( 0 , sData.GetLength() -1 );
					szEchoBuf[0] = 8;
					szEchoBuf[1] = 32;
					szEchoBuf[2] = 8;
					iSizeEchoBuf = 3;
				}
				else
				{
					continue;
				}
			} 
			// enter pressed
			else if ( szBuf[0] == 13 )
			{
				szEchoBuf[0] = 13;
				szEchoBuf[1] = 10;
				iSizeEchoBuf = 2;
			}
			else
			{
				// add to result buffer
				sData += szBuf[0];

				// ordinary char pressed
				if ( bIsPassword )
				{
					// echo a '*'
					strcpy( szEchoBuf , "*" );
					iSizeEchoBuf = 1;
				}
				else
				{
					// echo the pressed char
					memcpy( szEchoBuf , szBuf , 1 );
					iSizeEchoBuf = 1;
				}
			}

			// echo
			if ( send( m_iClientSock , szEchoBuf , iSizeEchoBuf , 0 ) != iSizeEchoBuf )
			{
				m_sLastError = "sending data to client failed";
				return false;
			}
		}
	}
	
	return true;
}
