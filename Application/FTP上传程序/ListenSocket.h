#if !defined(AFX_LISTENSOCKET_H__B2EE4422_F3D8_11D1_BB32_A8CEFC4C5E7C__INCLUDED_)
#define AFX_LISTENSOCKET_H__B2EE4422_F3D8_11D1_BB32_A8CEFC4C5E7C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ListenSocket.h : header file
//
#define CONNECTED 1
#define RECEIVED  2
#define ACCEPT    4
#define CLOSE    16
/////////////////////////////////////////////////////////////////////////////
// CListenSocket command target

class CListenSocket : public CAsyncSocket
{
// Attributes
public:
	UINT Aflag;
// Operations
public:
	CListenSocket();
	virtual ~CListenSocket();
	int waittingfor(UINT evt,unsigned long TIMEOUT=9000);
	void DoIdleProcess();
	int canceled;
	int error;
// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListenSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENSOCKET_H__B2EE4422_F3D8_11D1_BB32_A8CEFC4C5E7C__INCLUDED_)
