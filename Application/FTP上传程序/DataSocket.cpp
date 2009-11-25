// DataSocket.cpp : implementation file
//

#include "stdafx.h"
//#include "update.h"
#include "DataSocket.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataSocket

CDataSocket::CDataSocket()
{
	canceled=0;
	error=0;
}

CDataSocket::~CDataSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CDataSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CDataSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CDataSocket member functions

void CDataSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (!nErrorCode)
		Aflag=Aflag|RECEIVED;	
	else
		error=nErrorCode;
	CAsyncSocket::OnReceive(nErrorCode);
}

void CDataSocket::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (!nErrorCode)
		Aflag=Aflag|SEND;	
	else
		error=nErrorCode;
	CAsyncSocket::OnSend(nErrorCode);
}
void CDataSocket:: DoIdleProcess()
{
	MSG msg;
	while(::PeekMessage(&msg,NULL,0,0,PM_REMOVE)){
		if (!AfxGetApp()->PreTranslateMessage(&msg)){
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
    AfxGetApp()->OnIdle(0);
	AfxGetApp()->OnIdle(1);
}
int  CDataSocket::waittingfor(UINT evt,int TIMEOUT)
{
	time_t start, finish;
	double elapsed_time;
	time( &start );
	for (;;){
		time( &finish);
		elapsed_time= difftime(finish, start);
		if (elapsed_time>TIMEOUT){
			return (E_TIMEOUT);
		}
		if ((Aflag&CLOSE)==CLOSE)
			return(4);         // offline
		if (canceled){
			return(2);         // user break
		}
		if (error)
			return(error);
		if ((Aflag&evt)==evt)
			return (0);        // ok
		DoIdleProcess();
	}
}

void CDataSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (!nErrorCode)
		Aflag=Aflag|CLOSE;		
	else
		error=nErrorCode;
	CAsyncSocket::OnClose(nErrorCode);
}

void CDataSocket::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (!nErrorCode)
		Aflag=Aflag|CONNECTED;	
	else
		error=nErrorCode;
	CAsyncSocket::OnConnect(nErrorCode);
}

int CDataSocket::Send(const void* lpBuf, int nBufLen, int nFlags)
{
	int nRet = CAsyncSocket::Send(lpBuf, nBufLen, nFlags);
	if (nRet < nBufLen)	// 如果传送的数据少了，那么直接设置Error为WSAEFAULT
	{
		WSASetLastError(WSAEFAULT);
		nRet = SOCKET_ERROR;
	}
	return nRet;
}
