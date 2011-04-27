#pragma once


class CMySocket : public CAsyncSocket
{
public:
	BOOL m_bConnected; //�Ƿ�����
	UINT m_nLength; //��Ϣ���� 
	char m_szBuffer[4096]; //��Ϣ������

	CMySocket(void);
	~CMySocket(void);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);

	CMySocket * m_pSocket;
};
