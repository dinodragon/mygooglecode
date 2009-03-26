// UpdataAHost.cpp : 实现文件
//

#include "stdafx.h"
#include "TEST_MyLogin.h"
#include "UpdateAHost.h"
#include "TEST_MyLoginDlg.h"
#include "upsock.h"


// CUpdateAHost

IMPLEMENT_DYNCREATE(CUpdateAHost, CWinThread)

CUpdateAHost::CUpdateAHost()
{
	TIMEOUT = 60;
	MAXFILEBUF = 4096;
	bResume = TRUE;
	bPasv = TRUE;
	updating = TRUE;
	iResumeFlag = ID_RESUME;
	updatesock = NULL;
	listensock = NULL;
	bProxyEnable = FALSE;
	LastPath[0] = '\x0';
	REMOTEPATH = "/";
	LOCALPATH = "C:\\";
}

CUpdateAHost::~CUpdateAHost()
{
	if(updatesock)
		DeleteCommandSocket();
	if(listensock)
		DeleteListenSocket();
		DeleteDataSocket();
}

BOOL CUpdateAHost::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化
	return TRUE;
}

int CUpdateAHost::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CUpdateAHost, CWinThread)

END_MESSAGE_MAP()


// CUpdateAHost 消息处理程序

void CUpdateAHost::SetProxy(CString sProxyHost,UINT uProxyPort)
{
	this->sProxyHost = sProxyHost;
	this->uProxyPort = uProxyPort;
	bProxyEnable = TRUE;
}

UINT CUpdateAHost::ConnectFTPControlSocket(CString lpszHost,UINT port,BOOL proxyenable)
{
	//	0 ok  1 error  2 userbreak   3 timeout  4 offline   5 ignore    6 can not create dir		

	if(updatesock && updatesock->bConnect)
	{
		return 0;
	}
	if(lpszHost == "")  //传入无效值
		return 1;
	if(port == 0)
		port = 21;


	LPHOSTENT lpHostEnt;
	SOCKADDR_IN sockAddr;
	short nProtocolPort = 0;
	UINT nReplyCode;
	DWORD dwIPAddr;
	//		char buf[MAXGETHOSTSTRUCT];
	TCHAR message[2048];

	//新定义
	short nFTPort = port;

	int updating = true;
//	char buf[128];
	hostent host;
	lpHostEnt = &host;

	if (!bProxyEnable)
		wsprintf(message,"正在连接 %s . . .",lpszHost);
	else
		wsprintf(message,"正在连接代理服务器 %s . . .",lpszHost);		
	AddMessage(message);

	//如果是域名地址
	if (isalphip(lpszHost)){
		//进行域名解析
		lpHostEnt= gethostbyname(lpszHost);;

		if(lpHostEnt == NULL)
		{
			AddMessage("无效的主机地址 !"); 
			return(1);
		}
		sockAddr.sin_addr = *((LPIN_ADDR)*lpHostEnt->h_addr_list);
		wsprintf(message,"正在连接 %s (%d.%d.%d.%d). . .",lpszHost,
			sockAddr.sin_addr.S_un.S_un_b.s_b1,
			sockAddr.sin_addr.S_un.S_un_b.s_b2,
			sockAddr.sin_addr.S_un.S_un_b.s_b3,
			sockAddr.sin_addr.S_un.S_un_b.s_b4);
		AddMessage(message); 
	}
	else
	{
		dwIPAddr=inet_addr(lpszHost);
		if (dwIPAddr==INADDR_NONE){
			AddMessage("无效的主机地址 !"); 
			return(1);
		}
		sockAddr.sin_addr.S_un.S_addr=dwIPAddr; 
	}

	updatesock = new Cupsock(); // command socket
	if (updatesock==NULL){
		AddMessage("Create Update sock error!");
		return 1;
	}

	if (!updatesock->Create()){
		AddMessage("updatesock->Create()错误");
		DeleteCommandSocket();
		return(1);
	}
	nProtocolPort=htons(nFTPort);
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = nProtocolPort;
	updatesock->Aflag=0;
	if(!(updatesock->Connect((LPSOCKADDR)&sockAddr,sizeof(sockAddr))))
	{
		//控制连接没有返回立即成功
		nReplyCode=updatesock->GetLastError();
		//不能立即完成
		if (nReplyCode==WSAEWOULDBLOCK)
		{
			if (nReplyCode=updatesock->waittingfor(CONNECTED,10))
			{
				DeleteCommandSocket();
				ShowError(nReplyCode);
			
				/*if(updating&&nReplyCode>10000)
					ShowError(nReplyCode);*/
				return(1);
			}
		}
		else
		{
			DeleteCommandSocket();
			ShowError(nReplyCode);
			return (1);
		}
	}

	AddMessage("Socket已经连接. 正在等待欢迎信息 ...");
	nReplyCode=updatesock->ReadReplyCode(10,this);
	if (nReplyCode==E_TIMEOUT){
		AddMessage("Connect TIMEOUT ...");
		DeleteCommandSocket();
		return(3);
	}
	if (nReplyCode<WSAEINTR)
	{
		AddMessage(updatesock->buf,RGB(0,128,0));
	}
	else
	{
		AddMessage(updatesock->buf,RGB(0,128,0));
		DeleteCommandSocket();
		if(nReplyCode==E_USERBREAK)
		{
			return(2);
		}
		else
		{
			ShowError(nReplyCode);
			return(1);
		}
	}
	updatesock->bConnect = TRUE;  //控制连接已经成功建立
	return (0);
}

void CUpdateAHost::AddMessage(char * sString,COLORREF color)
{
	CTEST_MyLoginApp * pApp = (CTEST_MyLoginApp *)AfxGetApp();
	if(pApp == NULL) return;
	CTEST_MyLoginDlg * pDlg = (CTEST_MyLoginDlg*)pApp->m_pMainWnd;
	if(pDlg == NULL) return;
	
	CString temp;
	pDlg->GetDlgItemText(IDC_RICHEDIT2,temp);
	temp += sString;
	if(!strchr(sString,'\r') && !strchr(sString,'\n')) //如果字串里没有换行符
		temp += "\n";
	pDlg->SetDlgItemText(IDC_RICHEDIT2,temp);

	CRichEditCtrl * m_RichEditCtrl = (CRichEditCtrl *)pDlg->GetDlgItem(IDC_RICHEDIT2);
	m_RichEditCtrl->LineScroll(2,1);
}

UINT CUpdateAHost::isalphip(CString lpszHost)
{

	char chost[128];
	char * ch;
	strcpy_s(chost,sizeof(chost),lpszHost);
	ch=chost;
	do{
		if ((*ch<='9')&&(*ch>='0'))
			ch++;
		else{
			if (*ch=='.'){
				ch++;
			}else{
				return (TRUE);
			}
		}
	}while (*ch);
	return (FALSE);
}


void CUpdateAHost::DoIdleProcess()
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

//删除控制连接
void CUpdateAHost::DeleteCommandSocket()
{
	if (updatesock!=NULL)
	{
		if(updatesock->bConnect){
			SendFTPCmd("QUIT\r\n",TRUE);
		}
		updatesock->ShutDown(1);
		updatesock->ShutDown(0);
		updatesock->Close();
	}
	delete updatesock;
	updatesock = NULL;
}

UINT CUpdateAHost::SendFTPCmd(const LPSTR CMDbuf,BOOL bFastReturn)
{
	char passw[]="********************";
	TCHAR message[2048];
	UINT nReplyCode;
	char cmdbuf[128];	
	strcpy_s(cmdbuf,sizeof(cmdbuf),CMDbuf);
	cmdbuf[4]='\x0';
	if (strcmp(cmdbuf,"PASS")!=0)
		wsprintf(message, "命令:%s",CMDbuf);
	else{
		strcpy_s(message,sizeof(message),"PASS ");
		strcat_s(message,sizeof(message),&passw[27-strlen(CMDbuf)]);
	}
	AddMessage(message,RGB(0,0,255));
	//还没有连接;
	if(updatesock == NULL || updatesock->bConnect == FALSE) return 0;
	nReplyCode=updatesock->SendFTPCommand(CMDbuf,strlen(CMDbuf),this,bFastReturn);
	if (nReplyCode>10000){//即发生错误.小于一万的返回码一般表示正常.
		ShowError(nReplyCode);
		return nReplyCode;
	}
	AddMessage(updatesock->buf,RGB(0,128,0)); //将服务器返回的内容显示
	return nReplyCode;
}

void CUpdateAHost::ShowError(int iWinsockErr)
{				
	CString mErr;
	TCHAR message[2048];
	//if (iWinsockErr<E_TIMEOUT){
		//mErr.LoadString(iWinsockErr);
		//wsprintf(message,"%s",(LPCSTR)mErr);
		wsprintf(message,"错误码:%d",iWinsockErr);
		AddMessage(message);
	//}
}	

UINT CUpdateAHost::FTPLogIn(CString Uid,CString Password)
{
//返回 -1失败
	int nReplyCode;
	//如果控制连接没有建立
	if(updatesock == NULL || updatesock->bConnect == FALSE) return -1;
	if(updatesock->bLogin == TRUE) return 0;
	if(Uid == "") Uid = _T("Anonymous");
	if(Password=="") Password =_T("yangfei@founder.com");
	CString temp = "USER " + Uid +"\r\n";
	CString temp2 = "PASS " + Password + "\r\n";
	nReplyCode=SendFTPCmd(temp.GetBuffer());
	if(nReplyCode==PASSWORD_REQUEST)
		nReplyCode=SendFTPCmd(temp2.GetBuffer());
	if(nReplyCode == 230)
		updatesock->bLogin = TRUE;
	return (nReplyCode);
}


void CUpdateAHost::DeleteListenSocket()
{
	if (listensock!=NULL){
		listensock->ShutDown(1);
		listensock->ShutDown(0);
		listensock->Close();
		delete listensock;
		listensock=NULL;
	}
}

void CUpdateAHost::DeleteDataSocket()
{
	if (datasock.m_hSocket!=INVALID_SOCKET){
		int temp;
		temp=datasock.ShutDown(1); //当前SOCKET不再进行发送
		TRACE("datasock.ShutDown(1)返回 %d",temp);
		datasock.ShutDown(0);//不再进行接收
		datasock.Close();
		datasock.m_hSocket=INVALID_SOCKET;
	}
}


//创建监听连接,用于主动模式
UINT CUpdateAHost::CreateListenSocket()
{
	listensock=new CListenSocket();
//	if (!(listensock->Create(0 ,SOCK_STREAM,FD_ACCEPT|FD_CLOSE))){
	if (!listensock->Create()){
		ShowError(listensock->GetLastError());	
		return(FALSE);
	}			
	if (!listensock->Listen()){
		ShowError(listensock->GetLastError() );	
		return(FALSE);
	}
	// Ask the server to connect to the port monitored by the listener socket
	return (RequestDataConnection());
}

UINT CUpdateAHost::RequestDataConnection()
{
	//返回:TRUE成功 FALSE失败
	SOCKADDR_IN sockAddr;					// Socket address structure
	int iLength;							// Length of the address structure
	UINT nLocalPort;						// Local port for listening
	UINT nReplyCode;						// FTP server reply code
	char cmdbuf[128];
	// Get the address for the hListenSocket
	iLength = sizeof(sockAddr);
	if (!listensock->GetSockName((LPSOCKADDR)&sockAddr,&iLength)){
		ShowError(listensock->GetLastError());	
		return(FALSE);				
	}
	nLocalPort = sockAddr.sin_port;
	if (!updatesock->GetSockName((LPSOCKADDR)&sockAddr,&iLength)){
		showerror();
		return(FALSE);
	}
	wsprintf(cmdbuf, "PORT %d,%d,%d,%d,%d,%d\r\n", 
			sockAddr.sin_addr.S_un.S_un_b.s_b1, 
			sockAddr.sin_addr.S_un.S_un_b.s_b2,
			sockAddr.sin_addr.S_un.S_un_b.s_b3,
			sockAddr.sin_addr.S_un.S_un_b.s_b4,
			nLocalPort & 0xFF,	
			nLocalPort >> 8);				
	if (nReplyCode = SendFTPCmd(cmdbuf)!= 200){
		showerror();
		return(FALSE);
	}else{
		return(TRUE);
	}
}

UINT CUpdateAHost::AcceptDataConnection()
{
	int nErr;
	datasock.error=0;
	if (!listensock->Accept(datasock)){
		nErr=listensock->GetLastError();
		while(nErr==WSAEWOULDBLOCK){
			if (!listensock->waittingfor(ACCEPT,TIMEOUT)){
				if (!listensock->Accept(datasock)){
					nErr=listensock->GetLastError();
					DeleteDataSocket();
				}else{
					datasock.canceled=0;
					return (TRUE);
				}
			}else{
				DeleteDataSocket();
				ShowError(nErr);
				return(FALSE);
			}
		}
		DeleteDataSocket();
		ShowError(nErr);
		return(FALSE);	
	}else{
		/////////////////add by zzs 2001-2-21
//		LINGER ol={1,0};
//		datasock.SetSockOpt(SO_LINGER,&ol,sizeof(ol));
		/////////////////////////////////////////////

		datasock.canceled=0;
		return (TRUE);
	}
}

void CUpdateAHost::showerror()		
{				
	//CString mErr;
	TCHAR message[2048];
	int iWinsockErr = WSAGetLastError();
	//mErr.LoadString(iWinsockErr);
	wsprintf(message,"错误码:%d",iWinsockErr);	
	AddMessage(message);
}

void CUpdateAHost::Exit()		
{
	updating=FALSE;
	if (updatesock!=NULL)
		updatesock->canceled=1;
	if (listensock!=NULL)
		listensock->canceled=1;
	datasock.canceled=1;
}


// 上传一个文件
UINT CUpdateAHost::UpdateAFileNow(LPSTR filename,char * fname,DWORD nFileLength,CString ltime,LPSTR szRealName)
//参数说明
//LPSTR filename,本地完整带路径的文件名
//char * fname //文件名
//DWORD nFileLength,文件大小,断点续传的时候会用来判断服务器上的文件是否比这个小.
//CString ltime,当弹出确认是否要进行断点续传对话框时,确定当前文件日期 暂时不用.
//LPSTR szRealName,//上传后对文件重命名
{
	//	0 ok  1 error  2 userbreak   3 timeout  4 offline   5 ignore    6 can not create dir
		UINT nReplyCode;			// FTP server reply code

		///////////////////////////
		////Add By zzs to test time
		char message[400];
		memset(message,0,sizeof(message));
		time_t ptimeNow;
		tm*    pTime;
		////////////////////////////

		char cmdbuf[128];
//		unsigned long int rsize;
//		char rdate[32];
		CString rtime;
		unsigned long int size = 0;  //标识在服务器上已经传送的文件大小
		CFile file;
		CFileException Ex;
		
		if(updatesock==NULL || !(updatesock->bConnect) || !(updatesock->bLogin)) return 1;
		
		TRY
		{
			if(!file.Open(filename,CFile::modeRead,&Ex))
			{
				wsprintf(message,"Open file %s error!", filename);
				AddMessage(message);
				return(1);
			}
		}
		CATCH(CException,e)
		{
			wsprintf(message,"Operate file %s error!", filename);
			AddMessage(message);
			file.Close();
			return(1);
		}
		END_CATCH
		nFileLength = file.GetLength();
		fname = file.GetFileName().GetBuffer();
		CString temp = file.GetFileName();
		fname = temp.GetBuffer();
		file.Close();

		size=0;              //8/22


		if (!REMOTEPATH.IsEmpty()){                  //98/8/17
			if (!ChRemoteDir(LastPath, filename)){
				return (6);                      // can not create dir
			}
		}
	
		time(&ptimeNow);		
		pTime=localtime(&ptimeNow);
		sprintf_s(message,sizeof(message),"%04d-%02d-%02d %02d:%02d:%02d开始上载文件%s",
			pTime->tm_year+1900,pTime->tm_mon+1,pTime->tm_mday,
			pTime->tm_hour,pTime->tm_min,pTime->tm_sec,fname);
		AddMessage(message,RGB(0,0,255));
		////////////
		

		//断点续传代码开始
		if (bResume)
		{
			if (iResumeFlag!=ID_OVERWRITEALL)
				size=GetRemoteFileSize(fname);
			if (!updating)
			{
				DeleteDataSocket();
				///////add by zzs to test time
				sprintf_s(message,sizeof(message),"userbreak,now bresume=1,updating=0 after call function GetRemoteFileSize,last file= %s",filename);
				AddMessage(message,RGB(0,0,255));
				/////end
				return (2);                   // userbreak
			}
/*
			if (size>0&&size<nFileLength&&iResumeFlag!=ID_OVERWRITEALL&&iResumeFlag!=ID_IGNOREALL&&iResumeFlag!=ID_RESUMEALL)
			{

				if (GetRemoteFileInfo(fname)>0){
					if (!updating){
						DeleteDataSocket();
						///////add by zzs to test time
						sprintf(message,"userbreak,now bresume=1,updating=0 after call function GetRemoteFileInfo,last file= %s",filename);
						AddMessage(message,RGB(0,0,255));
						/////end
						return (2);               // userbreak
					}
					rsize=atol(GetRminfo(ListReplyBuffer,4));
					strcpy(rdate,GetRminfo(ListReplyBuffer,5));
					rtime=GetRminfo(ListReplyBuffer,6);
					strcat(rdate," ");
					strcat(rdate,rtime);
					rtime=GetRminfo(ListReplyBuffer,7);
//					ResumeDlg rdlg(strHostName,fname,rsize,rtime,rdate,nFileLength,ltime,nRESUMETIMEOUT);
//					iResumeFlag=rdlg.DoModal();
					if (iResumeFlag==IDCANCEL)
						iResumeFlag=ID_IGNORE;
					//					if (iResumeFlag==ID_IGNORE||iResumeFlag==ID_IGNOREALL)
					//						return (4);
				}else{
					iResumeFlag=ID_IGNORE;
				}
			}

*/
			//::SendMessage(phWnd, WM_RESUMEFLAG,1,(LPARAM)"");
		}

		if (size&&size<nFileLength&&(iResumeFlag==ID_IGNORE||iResumeFlag==ID_IGNOREALL)){
			return (5);                         //ignore
		}
		//断点续传代码结束

		nReplyCode=isasciifile(fname);
		//nReplyCode=isasciifile(filename);
		//0  false  1 OK   2  BAK
		if (nReplyCode && (szRealName==NULL)){
			if(cCurrentType!='A'){
				nReplyCode=SendFTPCmd("TYPE A\r\n"); 
				cCurrentType='A';
			}else{
				nReplyCode=200;
			}
		}else{
			if (cCurrentType!='I'){
				nReplyCode=SendFTPCmd("TYPE I\r\n");
				cCurrentType='I';
			}else{
				nReplyCode=200;
			}
		}
		if (nReplyCode!=200){
			DeleteListenSocket();   //
			return(nReplyCode);
		}

		//如果是主动传输模式
		if (!bPasv)
		{
			if (CreateListenSocket()==FALSE)  //在CreateListenSocket过程中会发送PORT命令,让本地监听连接准备好.
			{
				DeleteListenSocket();
				return(1);
			}
			listensock->Aflag=0;
			listensock->AsyncSelect( FD_ACCEPT | FD_CLOSE );
		}
		else
		//被动模式
		{
			if (GetPasvSocketAddress()==FALSE) //取得地址,并且建立数据连接
			{
				return(1);
			}		
		}

		//AfxMessageBox(CString("1: ") + filename);
		/// Added by dyb end

		//如果不用断点续传
		if (iResumeFlag==ID_OVERWRITE||iResumeFlag==ID_OVERWRITEALL||!bResume||nFileLength<=size||size==0)
			wsprintf(cmdbuf,"STOR %s\r\n",fname);
		else
			if(iResumeFlag==ID_RESUME||iResumeFlag==ID_RESUMEALL)
			{
				wsprintf(cmdbuf,"APPE %s\r\n",fname);	
			}
		//上传没有成功
		if ((nReplyCode=SendFTPCmd(cmdbuf)) >= 400){
			DeleteListenSocket();
			return(nReplyCode);
		}

		//主动模式
		if (!bPasv){
			/*  Listen socket  */
			if (!(nReplyCode=listensock->waittingfor(ACCEPT,TIMEOUT)))
			{
				if (AcceptDataConnection()==FALSE)//将监听到的连接赋值给数据连接
				{
					return(1);//失败
				}
			}
			else
			{
				return (nReplyCode);//成功建立数据连接
			}
			DeleteListenSocket();
		}

		//if (bCanMsg){
		//	::SendMessage(phWnd, WM_STATUSLOG,1,(LPARAM)"");
		//}
		/******** start file transfer  ********/
		//strcpy(statusmsg1,"");	
		LPSTR pFileName;
		if(szRealName==NULL)
			pFileName = filename;
		else
			pFileName = szRealName;

		//要进行断点续传
		if (nFileLength>size&&(iResumeFlag==ID_RESUME||iResumeFlag==ID_RESUMEALL))
			nReplyCode=WriteDataChannel(pFileName,nFileLength,size);
		else
		//不进行断点续传
			nReplyCode=WriteDataChannel(pFileName,nFileLength,0);
		//nReplyCode
		//0 ok  1 error  2 userbreak   3 timeout  4 offline   5 ignore    6 can not create dir

		DeleteDataSocket();
		//上传结束

		//上传成功
		if (!nReplyCode){
			if (updating){                                         
				updatesock->Aflag=0;
				nReplyCode=updatesock->ReadReplyCode(TIMEOUT,this,true);
				AddMessage(updatesock->buf);
				if (nReplyCode>=400){
					return(nReplyCode);
				}
			}
			else
			{
				//add by zzs
				time(&ptimeNow);		
				pTime=localtime(&ptimeNow);
				sprintf_s(message,sizeof(message),"%04d-%02d-%02d %02d:%02d:%02d结束上载文件%s",
					pTime->tm_year+1900,pTime->tm_mon+1,pTime->tm_mday,
					pTime->tm_hour,pTime->tm_min,pTime->tm_sec,filename);
				AddMessage(message,RGB(0,0,255));
				//
				return (1);
			}
		}
		else
		{
			////////add by zzs
			time(&ptimeNow);		
			pTime=localtime(&ptimeNow);
			sprintf_s(message,sizeof(message),"%04d-%02d-%02d %02d:%02d:%02d 结束上载文件%s,replycode=%d",
				pTime->tm_year+1900,pTime->tm_mon+1,pTime->tm_mday,
				pTime->tm_hour,pTime->tm_min,pTime->tm_sec,filename,nReplyCode);
			AddMessage(message,RGB(0,0,255));
			////////////
			if (updating){   //  *****
				updatesock->Aflag=0;
				return (nReplyCode);
			}else{
				return (nReplyCode);
			}
		}
		////////add by zzs

		//成功进行了文件上传
		time(&ptimeNow);		
		pTime=localtime(&ptimeNow);
		sprintf_s(message,sizeof(message),"%04d-%02d-%02d %02d:%02d:%02d上载文件%s成功,返回状态0",
			pTime->tm_year+1900,pTime->tm_mon+1,pTime->tm_mday,
			pTime->tm_hour,pTime->tm_min,pTime->tm_sec,filename);
		AddMessage(message,RGB(0,0,255));
		////////////
		return (0);
} 


//这是新版本的2008-03-03
// 上传数据、文件
UINT CUpdateAHost::WriteDataChannel(LPSTR lpszFileName,long int nFileLength,unsigned long int lhead)
{
//	0 ok  1 error  2 userbreak   3 timeout  4 offline   5 ignore    6 can not create dir
	unsigned long int nBytesSend;	// Bytes received from the data channel
	unsigned long int nBytesSent;	// Bytes received from the data channel
	unsigned int nBytesRead,nReplyCode;
	int nError = 0;
	DWORD start, finish, elapsed_time;
	TCHAR message[2048];
	unsigned int hour;
	unsigned int min;
	unsigned int sec;
	CFile file;
	CFileException Ex;
	char * sDataBuffer=NULL;

	//打开文件
	TRY
	{
		if(!file.Open(lpszFileName,CFile::modeRead,&Ex))
		{
			wsprintf(message,"Open file %s error!", lpszFileName);
			AddMessage(message);
			return(1);
		}
		nFileLength = file.GetLength();
		sDataBuffer = new char[MAXFILEBUF+1];
		if (sDataBuffer==NULL){
			wsprintf(message,"没有足够的内存 !");						
			AddMessage(message); 
			if((HANDLE)file.m_hFile!=INVALID_HANDLE_VALUE)
				file.Close();
			return (1);
		}
		file.Seek(lhead,CFile::begin);
		nFileLength=nFileLength-lhead;

		nBytesSent=0;
		wsprintf(message,"正在传送文件 %s ...",lpszFileName);
		AddMessage(message); 

		start=GetTickCount();

		bool bReSend = true;
		do
		{
			bReSend = true;
			nBytesRead=file.Read(sDataBuffer,MAXFILEBUF);
			sDataBuffer[nBytesRead]='\0';
			if (nBytesRead==HFILE_ERROR)
			{
				wsprintf(message,"读文件 %s 错误.", lpszFileName);
				AddMessage(message); 
				break;
			}

			if (updating==FALSE)
			{
                if(sDataBuffer)
					delete[] sDataBuffer;
				sDataBuffer=NULL;
				if((HANDLE)file.m_hFile!=INVALID_HANDLE_VALUE)
					file.Close();
				return 2;               // userbreak
			}
			datasock.Aflag=0;					
			datasock.AsyncSelect( FD_READ | FD_WRITE | FD_CLOSE );
			if (!(nReplyCode=datasock.waittingfor(SEND,TIMEOUT)))
			{
				datasock.Aflag=0;
				// 传送数据
				nBytesSend = datasock.Send(sDataBuffer, nBytesRead);
			}else
			{
				if((HANDLE)file.m_hFile!=INVALID_HANDLE_VALUE)
					file.Close();
				if(sDataBuffer)
					delete[] sDataBuffer;
				sDataBuffer=NULL;
				return (nReplyCode);
			}

			if (nBytesSend == SOCKET_ERROR)
			{	 
				nError=datasock.GetLastError();
				if (nError!=WSAEWOULDBLOCK)
				{
					wsprintf(message,"#%d ",nError);
					AddMessage(message);
					break;
				}
				else
				{  
					do
					{
						bReSend = true;
						if (!(nReplyCode=datasock.waittingfor(SEND,TIMEOUT)))
						{
							datasock.Aflag=0;					
							nBytesSend=datasock.Send(sDataBuffer, nBytesRead);
							// add by hyw
							if (nBytesSend == SOCKET_ERROR)
							{
								nError = datasock.GetLastError();
								if (nError != WSAEWOULDBLOCK)
								{
									bReSend = false;
								}
							}
						}
						else
						{
							if((HANDLE)file.m_hFile!=INVALID_HANDLE_VALUE)
								file.Close();
							if(sDataBuffer)
								delete[] sDataBuffer;
							sDataBuffer=NULL;
							return (nReplyCode);
						}
						if (updating==FALSE)
						{
							if((HANDLE)file.m_hFile!=INVALID_HANDLE_VALUE)
								file.Close();
							if(sDataBuffer)
								delete[] sDataBuffer;
							sDataBuffer=NULL;
							return(2);            // userbreak
						}
					}while(nBytesSend==SOCKET_ERROR && bReSend);
				}
			}//if (nBytesSend == SOCKET_ERROR)

			if (!bReSend)	// 重传也失败时
			{
				wsprintf(message,"#%d ",nError);
				AddMessage(message);
				break;
			}

			if (nBytesSend>0)
			{
//				::PostMessage(phWnd, WM_SENTBYTES,nHostNum*100+nThreadNum,(LPARAM)nBytesSend);
				nBytesSent+=nBytesSend;
				//if(pArrInfo==NULL)
				//{
				//	NewFileSend->SetAt(nFileNum,nBytesSent);
				//	::PostMessage(phWnd, WM_REFRESHRATIO,nHostNum*100+nThreadNum,(LPARAM)nFileNum);
				//}
				//else
				//{
				//	int nTotal = pArrInfo->GetSize();
				//	for(int i=0;i<nTotal;i++)
				//	{
				//		int nSent = MulDiv(nBytesSent,(*pArrInfo)[i].nSize,nFileLength);
				//		NewFileSend->SetAt((*pArrInfo)[i].nSerial,nSent);
				//		::PostMessage(phWnd, WM_REFRESHRATIO,nHostNum*100+nThreadNum,(*pArrInfo)[i].nSerial);
				//	}
				//}
				wsprintf(message,"正在传送文件 %s ... %d%% (%lu bytes)",lpszFileName,nBytesSent*100/nFileLength,nBytesSent);
				//if (bCanMsg)
				//{
				//	::SendMessage(phWnd, WM_STATUSLOG,0,(LPARAM)message);
				//}
//				strcpy(statusmsg0,message);				
				finish=GetTickCount();
				elapsed_time= finish-start;
				if (elapsed_time>1000)
				{
					wsprintf( message,"%u bytes/sec",(unsigned int)(nBytesSent*1000/elapsed_time));	
/*					if (bCanMsg)
					{
						::SendMessage(phWnd, WM_STATUSLOG,1,(LPARAM)message);
					}
					strcpy(statusmsg1,message);		*/		
					hour=elapsed_time/(1000*60*60);
					min=(elapsed_time-hour*(1000*60*60))/(60*1000);
					sec=(elapsed_time-min*60*1000)/1000;
					wsprintf( message,"%02u:%02u:%02u",hour,min,sec);	
					//if (bCanMsg)
					//{
					//	::SendMessage(phWnd, WM_STATUSLOG,2,(LPARAM)message);
					//}
					//strcpy(statusmsg2,message);
				}
			}//if (nBytesSend>0)
		}while (nBytesRead==MAXFILEBUF&&nBytesSent<nFileLength);

		if((HANDLE)file.m_hFile!=INVALID_HANDLE_VALUE)
			file.Close();
		if (nBytesSend==SOCKET_ERROR)
		{
			if (nError!=WSAEWOULDBLOCK)
			{ 
				showerror();
				if(sDataBuffer)
					delete[] sDataBuffer;
				sDataBuffer=NULL;
				return(1);
			}
		}else
		{
			if (updating)
			{
				wsprintf(message,"已经从文件 %s 传送了%lu个字节.",lpszFileName,nBytesSent);
				AddMessage( message); 
				//if(bCanMsg)
				//{
				//	::SendMessage(phWnd, WM_STATUSLOG,0,(LPARAM)message);
				//	::SendMessage(phWnd, WM_STATUSLOG,1,(LPARAM)"");
				//}
				//strcpy(statusmsg0,message);
				//strcpy(statusmsg1,"");
			}
		}
		if(sDataBuffer)
			delete[] sDataBuffer;
		sDataBuffer=NULL;
		return(0);

	}//try
	CATCH(CException,e)
	{
		wsprintf(message,"Operate file %s error!", lpszFileName);
		AddMessage(message);
		if((HANDLE)file.m_hFile!=INVALID_HANDLE_VALUE)
			file.Close();
		if(sDataBuffer)
			delete[]sDataBuffer;
		sDataBuffer=NULL;
		return(1);
	}
	END_CATCH
}


int CUpdateAHost::isasciifile(char * fname)
{
	//	0 false  1 OK   2  BAK
	char filename[_MAX_FNAME];
	char asciifile[_MAX_FNAME];
	char * fnhead,*ch0,*ch1;
	/****************************************/
	strcpy_s(filename,sizeof(filename),fname);
	_strlwr_s(filename,sizeof(filename));
	fnhead=&filename[0];
	do{
		fnhead++;
	}while ((*fnhead)!='.'&&(*fnhead));
	if (!*fnhead)
		return (0);
	fnhead++;
	if (!strcmp(fnhead,"bak"))
		return 2;	
	/****************************************/
	//if (ASCIIFILE.IsEmpty())
		return 0;
	//strcpy(asciifile,ASCIIFILE);
	//_strlwr(asciifile);
	ch1=asciifile;
	do {
		ch0=ch1;
		while (*ch1&&*ch1!=' '){
			ch1++;
		}
		if (ch0==ch1)
			return 0;
		*ch1='\x0';
		if (!strcmp(fnhead,ch0))
			return 1;	
		ch1++;
	}while (*ch1);
	return 0;
}


//取得被动模式的地址及端口信息
int CUpdateAHost::GetPasvSocketAddress()
{
//	char szbuf[512];
//	int nPort;
	int nReplyCode;
	SOCKADDR_IN sockAddr;
	int iHPort,iLPort;
	if (SendFTPCmd("PASV\r\n")== 227){
		GetAddressFromSz(updatesock->buf,&sockAddr,&iHPort,&iLPort);
		sockAddr.sin_family = AF_INET;		
		sockAddr.sin_port = iHPort*256+iLPort;
		
		
		datasock.m_hSocket=INVALID_SOCKET;
		if (datasock.m_hSocket!=INVALID_SOCKET){
			TRACE("datasock.m_hSocket!=INVALID_SOCKET\n");
		}

		//if (datasock.Create(0, SOCK_STREAM,FD_READ|FD_WRITE|FD_CONNECT|FD_CLOSE))
		if(datasock.Create())
		{
			////////////////////////add by zzs 2001-02-21
//			LINGER ol={1,0};
//			datasock.SetSockOpt(SO_LINGER,&ol,sizeof(ol));
			////////////////////////end by zzs
			datasock.Aflag=0;
			datasock.error=0;
			if (!datasock.Connect((LPSOCKADDR)&sockAddr,sizeof(sockAddr))){
				nReplyCode=datasock.GetLastError();
				if (nReplyCode==WSAEWOULDBLOCK){
					if (nReplyCode=datasock.waittingfor(CONNECTED,2)){
						ShowError(nReplyCode);
						DeleteDataSocket();
						return false;
					}else
						return true;
				}else{
					 DeleteDataSocket();
					 ShowError(nReplyCode);
					 return false;
				}
			}else{
				return true;   //99/10/4
			}
		}else{
			AddMessage(_T("数据连接建立错误!"));
			DeleteDataSocket();
			showerror();
			return false;
		}
	}else{
		return false;
	}
}

void CUpdateAHost::GetAddressFromSz(char * szbuf,SOCKADDR_IN * pSockAddr,int *iHPort,int *iLPort)
{
	char * p0;
	p0 = strchr(szbuf, ',');
	if (p0==NULL){
		return;
	}
	p0--;
	while (*p0 == ' ') p0--;
	while (isdigit(*p0)) p0--;
	if (*p0 != '\0') p0++;
	sscanf(p0, "%d,%d,%d,%d,%d,%d", 
		&(pSockAddr->sin_addr.S_un.S_un_b.s_b1),
		&(pSockAddr->sin_addr.S_un.S_un_b.s_b2),
		&(pSockAddr->sin_addr.S_un.S_un_b.s_b3),	
		&(pSockAddr->sin_addr.S_un.S_un_b.s_b4),	
		iLPort,iHPort );

}


unsigned long int CUpdateAHost::GetRemoteFileSize(char * filename)
{
	unsigned long int size;
	char lpBuf[256];
	char * lpb;
	int nReplyCode;
	wsprintf(lpBuf,"SIZE %s\r\n",filename);
	nReplyCode=SendFTPCmd(lpBuf);
	if (nReplyCode==213){
		lpb=updatesock->buf;
		while (*lpb&&*lpb!=' ')
			lpb++;
		size=atol(lpb);
		return size;
	}else
		return (0);
}


int CUpdateAHost::GetRemoteFileInfo(char * filename)
{
	int nReplyCode;
	char lpBuf[256];
	int nRead;
	int nTatalRead;
	cCurrentType='A';
	nReplyCode=SendFTPCmd("TYPE A\r\n");
	nRead=0;
	nTatalRead=0;
	if (nReplyCode==200){
		if (!bPasv){
			if (CreateListenSocket()==FALSE){
				DeleteListenSocket();
				return(0);
			}
			wsprintf(lpBuf,"LIST %s\r\n",filename);
			listensock->Aflag=0;
			nReplyCode=SendFTPCmd(lpBuf);
			if (nReplyCode==150){
				if (AcceptDataConnection()==FALSE){
					DeleteListenSocket();
					DeleteDataSocket();
					return(0);
				}
				updatesock->Aflag=0;
				datasock.Aflag=0;
				datasock.canceled=0;
				datasock.AsyncSelect( FD_READ | FD_WRITE | FD_CLOSE );
				nReplyCode=99999;
				*ListReplyBuffer='\x0';
				while (!datasock.canceled&&(!(datasock.Aflag&16))){
					DoIdleProcess();
					if (!datasock.waittingfor(RECEIVED,TIMEOUT)){
						datasock.Aflag=0;				
						nRead=datasock.Receive(&ListReplyBuffer[nTatalRead],sizeof(ListReplyBuffer)-nTatalRead);
						nTatalRead=nTatalRead+nRead;
						if (nTatalRead-2>0)
							if (ListReplyBuffer[nTatalRead-2]='\x0d')
								break;
					}
				}
			}else{
				DeleteDataSocket();
				return(0);
			}
		}else{
			//Pasv mode
			if (GetPasvSocketAddress()==FALSE){
				return(0);
			}		
			wsprintf(lpBuf,"LIST %s\r\n",filename);
			nReplyCode=SendFTPCmd(lpBuf);
			if (nReplyCode==150){
				updatesock->Aflag=0;
				datasock.Aflag=0;
				datasock.canceled=0;
				datasock.AsyncSelect( FD_READ | FD_WRITE | FD_CLOSE );
				nReplyCode=99999;
				*ListReplyBuffer='\x0';
				while (!datasock.canceled&&(!(datasock.Aflag&16))){
					DoIdleProcess();
					if (!datasock.waittingfor(RECEIVED,TIMEOUT)){
						datasock.Aflag=0;				
						nRead=datasock.Receive(&ListReplyBuffer[nTatalRead],sizeof(ListReplyBuffer)-nTatalRead);
						nTatalRead=nTatalRead+nRead;
						if (nTatalRead-2>0)
							if (ListReplyBuffer[nTatalRead-2]='\x0d')
								break;
					}
				}
			}else{
				DeleteDataSocket();
				return(0);
			}
		}	
	}else{
		cCurrentType='O';
		DeleteDataSocket();
		return(0);
	}
	if (nTatalRead==0&&(datasock.Aflag&16)){
		while(nTatalRead==0){
			DoIdleProcess();
			nTatalRead=datasock.Receive(ListReplyBuffer,sizeof(ListReplyBuffer));		
		}
	}
	if (nTatalRead>0){
		ListReplyBuffer[nTatalRead]='\x0';
		AddMessage(ListReplyBuffer);
	}
	if ((updatesock->Aflag)&2){
		nReplyCode=updatesock->ReadReplyCode(TIMEOUT,this);
	}
	if (nReplyCode==99999)
		nReplyCode=updatesock->ReadReplyCode(TIMEOUT,this);
	DeleteDataSocket();
	if (nTatalRead>0)
		return 1;
	else
		return (0);
}


char * CUpdateAHost::GetRminfo(char * rBuf,int num)
{
	char rbuffer[1024];
	char * rHead,* buffer;
	strcpy_s(rbuffer,sizeof(rbuffer),rBuf);
	buffer=rbuffer;
	while (*buffer){
		if (*buffer==' '){
			while (*buffer==' ') buffer++;
			num--;
			if (num==0)
				break;
		}
		buffer++;
	}
	rHead=buffer;
	while (*buffer&&*buffer!=' ')
		buffer++;
	*buffer='\x0';
	return(rHead);
}

int CUpdateAHost::GetRemotePath(char * rpath)
{
	int nReplyCode;
	char *pch;
	char *phead;	
	nReplyCode=SendFTPCmd ("PWD\r\n");
	if (nReplyCode==PWDOK){
		pch=updatesock->buf;
		while(*pch!='"'&&*pch){
			pch++;
		}
		pch++;
		phead=pch;
		while(*pch&&*pch!='"'){
			pch++;
		}
		*pch='\x0';
		strcpy(rpath,phead);
		return 0;
	}else{
		*rpath='\x0';
		return nReplyCode;
	}
}

void CUpdateAHost::Quit()
{

}

UINT CUpdateAHost::ChRemoteDir(char * LastPath,const char *currpath)
{
	//旧的
	//char pathname1[_MAX_FNAME];
	//char pathname2[_MAX_FNAME];
	//char cmdbuf[128];

    //新的2008-03-03
	char pathname1[MAX_PATH];
	char pathname2[MAX_PATH];
	char cmdbuf[MAX_PATH];
	UINT nReplyCode;
	UINT nLen;
	UINT nOffset;
	char *chptr;
	AddMessage(LastPath);
	removefilename(LastPath,pathname1);

	removefilename(currpath,pathname2);

    if (!strcmp(pathname1,pathname2)){
		return TRUE;
	}else{
		GetLocalCurrentPath(pathname2);
//		if (REMOTEPATH!="/"){
		if (pathname2[0]!='\x0'||LastPath[0]!='\x0'){ // 1999/01/04
		wsprintf(cmdbuf,"CWD %s%s\r\n",(const char *)REMOTEPATH,pathname2);
		nReplyCode=SendFTPCmd(cmdbuf);			// CD remote path	
//		}else
//			nReplyCode=250;
		if (nReplyCode>10000)      //1999/1/5
			return FALSE;          //1999/1/5
		if (nReplyCode>=400){					// no path error
			wsprintf(cmdbuf,"MKD %s%s\r\n",(const char *)REMOTEPATH,pathname2);
			nReplyCode=SendFTPCmd(cmdbuf);		// MD remote path																
		}
		if (nReplyCode==257){
			wsprintf(cmdbuf,"CWD %s%s\r\n",(const char *)REMOTEPATH,pathname2);
			nReplyCode=SendFTPCmd(cmdbuf);		// MD remote path																
		}
		if (nReplyCode>=400){
			if (pathname2[0]=='/')
				strcpy_s(pathname1,sizeof(pathname1),&pathname2[1]);
			else
				strcpy_s(pathname1,sizeof(pathname1),pathname2);
			chptr=pathname1;
			nLen=strlen(pathname1);
			nOffset=0;
			wsprintf(cmdbuf,"CWD %s\r\n",(const char *)REMOTEPATH);
			nReplyCode=SendFTPCmd(cmdbuf);			// CD remote path
			while(nOffset<nLen){
				while (pathname1[nOffset]!='/'&&nOffset<nLen){
				   nOffset++;
				}
				pathname1[nOffset]='\x0';
				wsprintf(cmdbuf,"MKD %s\r\n",chptr);
				nReplyCode=SendFTPCmd(cmdbuf);		// MD remote path		
				wsprintf(cmdbuf,"CWD %s\r\n",chptr);
				nReplyCode=SendFTPCmd(cmdbuf);	// MD remote path		
				if (nReplyCode>=400){
					return FALSE;
				}
				if (nOffset<nLen){
					pathname1[nOffset]='/';
					nOffset++;
					chptr=&pathname1[nOffset];
				}
			}
			if (nReplyCode>=400)
				return FALSE;
			}
		}
	}
	return TRUE;
}

char * CUpdateAHost::removefilename(const char * path,char * outpath)
{
	char * ch;
	char * pch;
	ch=outpath;
	pch=outpath;
	while (*path){
		if (*path=='\\'||*path=='/')
			pch=ch;
		*ch++=*path++;			
	}
	*ch='\x0';
	*pch='\x0';
	return outpath;
}

void CUpdateAHost::GetLocalCurrentPath(char * pathname)
{
	UINT len;
	char path[_MAX_FNAME];
	char * ppath;
	len=LOCALPATH.GetLength();
	if (LOCALPATH.GetAt(len-1)=='\\')
		len--;
	ppath=path;
    while (*(pathname+len)){
		if (*(pathname+len)=='\\')
			*ppath='/';
		else
			*ppath=*(pathname+len);
		ppath++;
		len++;
	}
	*ppath='\x0';
	len=REMOTEPATH.GetLength();
	if (REMOTEPATH.GetAt(len-1)=='/'||REMOTEPATH.GetAt(len-1)=='\\'){
		if (path[0]=='/'||path[0]=='\\'){
			strcpy(pathname,&path[1]);
			return;
		}
	}
	strcpy(pathname,path);
}