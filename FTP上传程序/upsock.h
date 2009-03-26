#pragma once

#include "UpdateAHost.h"

// Cupsock 命令目标
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
	BOOL bConnect;  //是否已经连接
	BOOL bLogin;    //是否已经登陆

	//读取发送命令之后的返回码
	UINT ReadReplyCode(unsigned long TIMEOUT=90,CUpdateAHost * pHost=NULL,BOOL bFastReturn=FALSE);
	//发送FTP命令,返回值即为ReadReplyCode的返回码.
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
