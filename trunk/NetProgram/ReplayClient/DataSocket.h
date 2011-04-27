#pragma once

// CDataSocket ����Ŀ��

class CDataSocket : public CAsyncSocket
{
public:

	BOOL m_bConnected; //�Ƿ�����
	UINT m_nLength; //��Ϣ���� 
	char m_szBuffer[4096]; //��Ϣ������

	CDataSocket();
	virtual ~CDataSocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	void AddMessage(CString str);
	void showError(int error);
};


