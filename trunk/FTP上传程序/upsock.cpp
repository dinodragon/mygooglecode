// upsock.cpp : 实现文件
//

#include "stdafx.h"
#include "TEST_MyLogin.h"
#include "upsock.h"
#include "TEST_MyLoginDlg.h"
#include <afxmt.h>

CMutex g_Mutex;
// Cupsock

Cupsock::Cupsock()
{
	canceled=0;
	error=0;
	buf=NULL;
	bConnect = FALSE;
	bLogin = FALSE;
}

Cupsock::~Cupsock()
{
	if (buf!=NULL)
		free(buf);
}


// Cupsock 成员函数

BOOL Cupsock::Create()
{
	g_Mutex.Lock();
	BOOL bRet=FALSE;
	TRY
	{
		bRet=CAsyncSocket::Create();
	}
	CATCH(CException, e)
	{
		bRet=FALSE;
	}
	END_CATCH

    g_Mutex.Unlock();

	return bRet;
}

void Cupsock::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (!nErrorCode)
		Aflag=Aflag|CLOSE;	
	else
		error=nErrorCode;
	bConnect = FALSE;
	bLogin = FALSE;
	CAsyncSocket::OnClose(nErrorCode);
}

void Cupsock::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (!nErrorCode)
		Aflag=Aflag|CONNECTED;	
	else
		error=nErrorCode;
	CAsyncSocket::OnConnect(nErrorCode);
}

void Cupsock::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (!nErrorCode)
		Aflag=Aflag|RECEIVED;
	else
		error=nErrorCode;
	CAsyncSocket::OnReceive(nErrorCode);
}

void Cupsock::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnSend(nErrorCode);
}
int Cupsock::waittingfor(UINT evt,int TIMEOUT)
{
	time_t start, finish;
	double elapsed_time;
	time( &start );
	for (;;){
		time( &finish);
		elapsed_time= difftime(finish, start);
		if (elapsed_time>TIMEOUT){
			return (E_TIMEOUT);
		}
		if ((Aflag&CLOSE)==CLOSE)
			return(4);         // offline
		if (canceled){
			return(2);         // user break
		}
		if (error)
			return error;
		if ((Aflag&evt)==evt)
			return (0);
		DoIdleProcess();		
	}
}
void Cupsock:: DoIdleProcess()
{
	MSG msg;
	while(::PeekMessage(&msg,NULL,0,0,PM_REMOVE)){
		if (!AfxGetApp()->PreTranslateMessage(&msg)){
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
    AfxGetApp()->OnIdle(0);
	AfxGetApp()->OnIdle(1);
}
UINT Cupsock:: ReadReplyCode(unsigned long TIMEOUT,CUpdateAHost* pHost,BOOL bFastReturn)
{		
	UINT nCode;										// Reply code as a number
	UINT nByte;
	UINT nBytes;
	size_t len;
	char * ch;
	time_t start, finish;
	double elapsed_time;
	nByte=0;
	nBytes=0;
//	rbuffer[0]='\x0';
	time( &start );
	if (buf!=NULL)
		free(buf);
	buf=(char *)malloc(1024);
	if (buf==NULL){
		AfxMessageBox(TEXT("No Enough Memeory!"));
	}
	/////modi fy by zzs
	//buf[0]='\x0';
	memset(buf,0,1024);
	//yf将BUF已经清空
	time_t nTime=start;
	///////////////////
	
	for (;;){
		if (canceled)			
			return (E_USERBREAK);
		if (error)			
			return (error);
		if ((Aflag&CLOSE)==CLOSE)
			return (E_OFFLINE);	
		time( &finish);
		elapsed_time= difftime(finish, start);
		if (elapsed_time>TIMEOUT){
			return (E_TIMEOUT);
		}
		if ((Aflag&RECEIVED)==RECEIVED){
			nByte=Receive(&replybuffer,sizeof(replybuffer));
			if (nByte!=SOCKET_ERROR){
				Aflag=0;
				nBytes=nBytes+nByte;
				*(replybuffer+nByte)='\x0';    //9/11  //yf在收到的信息末尾加上0结束各个符
				/**************************/
				len=strlen(buf);//第一次时值为0
				buf=(char *)realloc(buf,nBytes+1);//将buf重置为收到的大小
				if (buf==NULL){
					AfxMessageBox(TEXT("No Enough Memeory!"));
				}
				if (len>0)
					buf[len]='\x0';
				//strcat(buf,replybuffer);
				strcat(buf,replybuffer);
				buf[nBytes]='\x0';
				ch=buf+(nBytes-3);				
				/**************************/
				if (*(ch+1)=='\r'||*(ch+2)=='\n'){       //99/6/4 unremark
					while (*ch!='\r'&&*ch!='\n'&&ch>buf)
						ch--;
					if (*(ch+4)==' '&& (*ch=='\n'||*ch=='\r')){
						ch++;
						if (IsAllNumber(ch,3)==0)
							break;
					}
					if (*(ch+3)==' '&& (ch==buf)){
						if (IsAllNumber(ch,3)==0)
							break;
					}
				}
			}else
				return (E_RECEIVE);
		}else //if ((Aflag&RECEIVED)!=RECEIVED)
		{
			//////Add by zzs
			if(pHost&&(elapsed_time>=TIMEOUT/5))
			{	
				if(bFastReturn)
				{
					char message[100];
					wsprintf(message,"读返回码很慢,花了%f秒,提前返回",elapsed_time);
					pHost->AddMessage(message);
					return 500;
				}
				if(difftime(finish, nTime)>=(TIMEOUT/5))
				{
					nTime=finish;
					char message[100];										
					sprintf_s(message,sizeof(message),"读返回码很慢,花了%f秒,请耐心等待",elapsed_time);
					pHost->AddMessage(message);
					
				}

			}
			//end
			DoIdleProcess();
		}
	}	
	nCode=atoi(ch);
	return(nCode);
}
int Cupsock::IsAllNumber(char * ch,int n)
{
	int i;
	for (i=0;i<n;i++){
		if (*(ch+i)>0x39||*(ch+i)<0x30){
			return -1;
		}
	}
	return 0;
}
void Cupsock::SendQuit()
{
	Send("QUIT\r\n",6);
}

UINT Cupsock::SendFTPCommand(const char * CMDbuf, UINT CMDlen,CUpdateAHost* pHost,BOOL bFastReturn)
{
	if(bConnect == FALSE) return 0;
	int nReplyCode;
	if(Send(CMDbuf,CMDlen)!=SOCKET_ERROR){
	//if (Send("QUIT\r\n",6)!=SOCKET_ERROR){
		nReplyCode=ReadReplyCode(60,pHost,bFastReturn);
	}else{
		return(E_SEND);
	}
	return nReplyCode;
}

