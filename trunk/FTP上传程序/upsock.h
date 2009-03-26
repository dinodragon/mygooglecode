#pragma once

#include "UpdateAHost.h"

// Cupsock ����Ŀ��
class CUpdateAHost;
class Cupsock : public CAsyncSocket
{
public:
	Cupsock();
	virtual ~Cupsock();
	UINT Aflag;
	char *buf;
	char replybuffer[2048];
	int canceled;
	int error;
	BOOL bConnect;  //�Ƿ��Ѿ�����
	BOOL bLogin;    //�Ƿ��Ѿ���½

	//��ȡ��������֮��ķ�����
	UINT ReadReplyCode(unsigned long TIMEOUT=90,CUpdateAHost * pHost=NULL,BOOL bFastReturn=FALSE);
	//����FTP����,����ֵ��ΪReadReplyCode�ķ�����.
	UINT SendFTPCommand(const char * CMDbuf, UINT CMDlen,CUpdateAHost * pHost=NULL,BOOL bFastReturn=FALSE);
	int IsAllNumber(char * ch,int n);
	BOOL Create();

	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);

	int waittingfor(UINT evt,int TIMEOUT=90);
	void DoIdleProcess();
	void SendQuit();
};
