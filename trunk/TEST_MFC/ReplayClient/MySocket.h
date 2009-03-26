#pragma once

// CMySocket ����Ŀ��

class CMySocket : public CAsyncSocket
{
public:
	BOOL m_bConnected; //�Ƿ�����
	UINT m_nLength; //��Ϣ���� 
	char m_szBuffer[4096]; //��Ϣ������

	CMySocket();
	virtual ~CMySocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnAccept(int nErrorCode);

	//��ʾ��Ϣ
	void AddMessage(CString str);
	void showError(int error);
};
