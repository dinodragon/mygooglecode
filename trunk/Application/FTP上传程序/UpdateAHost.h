#pragma once

#include "stdafx.h"
#include "upsock.h"
#include "DataSocket.h"
#include "ListenSocket.h"

class Cupsock;
class CDataSocket;
class CListenSocket;
// CUpdateAHost

class CUpdateAHost : public CWinThread
{
	DECLARE_DYNCREATE(CUpdateAHost)

public:
	CUpdateAHost();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	CUpdateAHost::CUpdateAHost(HWND hwnd);
	virtual ~CUpdateAHost();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//���ӵ�FTP������
	UINT ConnectFTPControlSocket(CString lpszHost,UINT port,BOOL proxyenable);
	//����Ϣ��ӵ������ϵ���ʾ����
	void AddMessage(char * sString,COLORREF color=RGB(255,0,0));
	//�ж��Ƿ�������ַ����IP��ʾ
	UINT isalphip(CString lpszHost);
	//����ʱ�����������
	void DoIdleProcess();
	//ɾ����������,��������������������˷��Ϳ�������.
	void DeleteCommandSocket();
	//ɾ����������,����������������ģʽʱ�ڿͻ��˵ȴ�����˵�����
	void DeleteListenSocket();
	//ɾ����������,�������������ϴ��ļ�ʱ�����ļ�����.
	void DeleteDataSocket();
	//����FTPЭ������
	UINT SendFTPCmd(const LPSTR CMDbuf,BOOL bFastReturn = FALSE);
	//��ʾ�������
	void ShowError(int iWinsockErr);
	//ִ�е�½����
	UINT FTPLogIn(const CString Uid,const CString Password);
	//������������,����������ģʽ
	UINT CreateListenSocket();
	//������ģʽʱ,ʹ���������ӵȴ�������������
	UINT RequestDataConnection();
	//����һ����������
	UINT AcceptDataConnection();
	UINT TIMEOUT;
	char cCurrentType;//��ǰʹ�õĴ���ģʽ,A����I
	BOOL bPasv;//�Ƿ�ʹ���˱���ģʽ
	BOOL bResume;//�Ƿ���жϵ������ı�ʶ
	UINT iResumeFlag;//�ϵ������ı�ʶ;
	CString sProxyHost;//�����������ַ;
	UINT uProxyPort;//����������˿�;
	BOOL bProxyEnable;
	int updating;
	UINT MAXFILEBUF;//�ļ���������С
	void showerror(); //����getlasterror��ȡ�ô�����,��ʾ����
	void Exit();//������,����,���ݵ����ӵ�cancel��Ϊ1
	//�ϴ�һ���ļ�
	UINT UpdateAFileNow(LPSTR filename,char * fname,DWORD nFileLength,CString ltime,LPSTR szRealName);
	//�ϴ������ļ�
	UINT WriteDataChannel(LPSTR lpszFileName,long int nFileLength,unsigned long int lhead);
	int isasciifile(char * fname);
	//��ȡ����ģʽʱFTP�������˸����ĵ�ַ
	int GetPasvSocketAddress();
	void GetAddressFromSz(char * szbuf,SOCKADDR_IN * pSockAddr,int *iHPort,int *iLPort);
	unsigned long int GetRemoteFileSize(char * filename);
	int GetRemoteFileInfo(char * filename);
	int GetRemotePath(char * rpath);
	char * GetRminfo(char * rBuf,int num);
	void SetProxy(CString ,UINT);
	void Quit();
	UINT ChRemoteDir(char * LastPath,const char *currpath);
	//����·�����ļ���ַ,ȥ���ļ���,������ַ.
	char *removefilename(const char * path,char * outpath);
	void GetLocalCurrentPath(char * pathname);
	CString REMOTEPATH;
	CString LOCALPATH;
	char LastPath[MAX_PATH];

protected:
	DECLARE_MESSAGE_MAP()

public:

	Cupsock * updatesock;
	CListenSocket * listensock;
	CDataSocket datasock;
	TCHAR ListReplyBuffer[1024];
};


