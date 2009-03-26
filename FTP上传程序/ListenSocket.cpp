// ListenSocket.cpp : implementation file
//

#include "stdafx.h"
//#include "update.h"
#include "ListenSocket.h"
#include "Resource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListenSocket

CListenSocket::CListenSocket()
{
	canceled=0;
	error=0;
}

CListenSocket::~CListenSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CListenSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CListenSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CListenSocket member functions

int  CListenSocket::waittingfor(UINT evt,unsigned long TIMEOUT)
{
	time_t start, finish;
	double elapsed_time;
	time( &start );
	for (;;){
		time( &finish );
		elapsed_time= difftime(finish, start);
		if (elapsed_time>TIMEOUT){
			return (E_TIMEOUT);
		}
		if ((Aflag&CLOSE)==CLOSE)
			return (4);          // offline
		if (canceled)
			return (2);          // userbreak
		if (error)
			return(error);
		if ((Aflag&evt)==evt)
			return (0);
		DoIdleProcess();	
	}
}
void CListenSocket:: DoIdleProcess()
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

void CListenSocket::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(!nErrorCode)
		Aflag=Aflag|ACCEPT;		
	else
		error=nErrorCode;
	CAsyncSocket::OnAccept(nErrorCode);
}

void CListenSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(!nErrorCode)
		Aflag=Aflag|CLOSE;		
	else
		error=nErrorCode;
	CAsyncSocket::OnClose(nErrorCode);
}
