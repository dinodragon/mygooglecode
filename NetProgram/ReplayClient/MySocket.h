#pragma once
#include "DataSocket.h"

// CMySocket 命令目标

class CMySocket : public CAsyncSocket
{
public:
	BOOL m_bConnected; //是否连接
	UINT m_nLength; //消息长度 
	char m_szBuffer[4096]; //消息缓冲区

	CMySocket();
	virtual ~CMySocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnAccept(int nErrorCode);

	CDataSocket m_Socket;

	//显示消息
	void AddMessage(CString str);
	void showError(int error);
};
