#if !defined(AFX_DATESOCKET_H__82C88382_F3EE_11D1_BB32_A8CEFC4C5E7C__INCLUDED_)
#define AFX_DATESOCKET_H__82C88382_F3EE_11D1_BB32_A8CEFC4C5E7C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DataSocket.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataSocket command target

class CDataSocket : public CAsyncSocket
{
// Attributes
public:
	UINT Aflag;

// Operations
public:
	CDataSocket();
	virtual ~CDataSocket();

	//等待某一事件发生
	int waittingfor(UINT evt,int TIMEOUT=9000);
	//空闲时间做界面更新
	void DoIdleProcess();
	//发送数据
	int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
	int canceled;
	int error;
// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CDataSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATESOCKET_H__82C88382_F3EE_11D1_BB32_A8CEFC4C5E7C__INCLUDED_)
