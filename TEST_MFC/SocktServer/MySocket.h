#pragma once


class CMySocket : public CAsyncSocket
{
public:
	BOOL m_bConnected; //是否连接
	UINT m_nLength; //消息长度 
	char m_szBuffer[4096]; //消息缓冲区

	CMySocket(void);
	~CMySocket(void);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);

	CMySocket * m_pSocket;
};
