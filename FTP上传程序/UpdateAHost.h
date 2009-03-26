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
	CUpdateAHost();           // 动态创建所使用的受保护的构造函数
	CUpdateAHost::CUpdateAHost(HWND hwnd);
	virtual ~CUpdateAHost();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//连接到FTP服务器
	UINT ConnectFTPControlSocket(CString lpszHost,UINT port,BOOL proxyenable);
	//将消息添加到界面上的显示窗口
	void AddMessage(char * sString,COLORREF color=RGB(255,0,0));
	//判断是否主机地址是用IP表示
	UINT isalphip(CString lpszHost);
	//空闲时间做介面更新
	void DoIdleProcess();
	//删除控制连接,控制连接用于向服务器端发送控制命令.
	void DeleteCommandSocket();
	//删除监听连接,监听连接用于主动模式时在客户端等待服务端的连接
	void DeleteListenSocket();
	//删除数据连接,数据连接用于上传文件时发送文件数据.
	void DeleteDataSocket();
	//发送FTP协议命令
	UINT SendFTPCmd(const LPSTR CMDbuf,BOOL bFastReturn = FALSE);
	//显示错误代码
	void ShowError(int iWinsockErr);
	//执行登陆操作
	UINT FTPLogIn(const CString Uid,const CString Password);
	//创建监听连接,仅用于主动模式
	UINT CreateListenSocket();
	//在主动模式时,使用数据连接等待服务器的连接
	UINT RequestDataConnection();
	//接收一个数据连接
	UINT AcceptDataConnection();
	UINT TIMEOUT;
	char cCurrentType;//当前使用的传输模式,A还是I
	BOOL bPasv;//是否使用了被动模式
	BOOL bResume;//是否进行断点续传的标识
	UINT iResumeFlag;//断点续传的标识;
	CString sProxyHost;//代理服务器地址;
	UINT uProxyPort;//代理服务器端口;
	BOOL bProxyEnable;
	int updating;
	UINT MAXFILEBUF;//文件缓冲区大小
	void showerror(); //调用getlasterror来取得错误码,显示出来
	void Exit();//将命令,监听,数据的连接的cancel置为1
	//上传一个文件
	UINT UpdateAFileNow(LPSTR filename,char * fname,DWORD nFileLength,CString ltime,LPSTR szRealName);
	//上传数据文件
	UINT WriteDataChannel(LPSTR lpszFileName,long int nFileLength,unsigned long int lhead);
	int isasciifile(char * fname);
	//获取被动模式时FTP服务器端给出的地址
	int GetPasvSocketAddress();
	void GetAddressFromSz(char * szbuf,SOCKADDR_IN * pSockAddr,int *iHPort,int *iLPort);
	unsigned long int GetRemoteFileSize(char * filename);
	int GetRemoteFileInfo(char * filename);
	int GetRemotePath(char * rpath);
	char * GetRminfo(char * rBuf,int num);
	void SetProxy(CString ,UINT);
	void Quit();
	UINT ChRemoteDir(char * LastPath,const char *currpath);
	//将带路径的文件地址,去掉文件名,保留地址.
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


