#pragma once

// CDataSocket 命令目标

class CDataSocket : public CAsyncSocket
{
public:

	BOOL m_bConnected; //是否连接
	UINT m_nLength; //消息长度 
	char m_szBuffer[4096]; //消息缓冲区

	CDataSocket();
	virtual ~CDataSocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	void AddMessage(CString str);
	void showError(int error);
};


