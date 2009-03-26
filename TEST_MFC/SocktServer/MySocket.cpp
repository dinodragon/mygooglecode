#include "StdAfx.h"
#include "MySocket.h"
#include "SocktServer.h"
#include "SocktServerDlg.h"


CMySocket::CMySocket(void)
{
	m_nLength=0;
	memset(m_szBuffer,0,sizeof(m_szBuffer)); 
	m_bConnected=FALSE;
}


CMySocket::~CMySocket(void)
{
	if(m_hSocket!=INVALID_SOCKET) 
	Close();
	ShutDown();
}

void CMySocket::OnReceive(int nErrorCode)
{
	m_nLength=Receive(m_szBuffer,sizeof(m_szBuffer),0); 
	//下面两行代码用来获取对话框指针
	CSocktServerApp * pApp = (CSocktServerApp *)AfxGetApp();
	CSocktServerDlg * pDlg = (CSocktServerDlg*)pApp->m_pMainWnd;
	CString temp;
	pDlg->GetDlgItemText(IDC_RICHEDIT21,temp);
	temp += m_szBuffer;
	pDlg->SetDlgItemText(IDC_RICHEDIT21,temp);
	memset(m_szBuffer,0,sizeof(m_szBuffer)); 
	CAsyncSocket::OnReceive(nErrorCode);
}

void CMySocket::OnSend(int nErrorCode) 
{ 
	Send(m_szBuffer,m_nLength,0);
	m_nLength=0; 
	memset(m_szBuffer,0,sizeof(m_szBuffer)); 
	//继续提请一个“读”的网络事件，接收Server消息
	AsyncSelect(FD_READ); 
	CAsyncSocket::OnSend(nErrorCode);
}

void CMySocket::OnConnect(int nErrorCode)
{ 
	if (nErrorCode==0) { 
		m_bConnected=TRUE; 
		//CCSockClientApp* pApp=(CCSockClientApp*)AfxGetApp(); 
		//CCSockClientDlg* pDlg=(CCSockClientDlg*)pApp- >m_pMainWnd; 
		//memcpy(m_szBuffer,"Connected to ",13); 
		//strncat(m_szBuffer,pDlg- >m_szServerAdr,sizeof(pDlg- >m_szServerAdr)); 
		//pDlg- >m_MSGS.InsertString(0,m_szBuffer);
		CSocktServerApp * pApp = (CSocktServerApp *)AfxGetApp();
		CSocktServerDlg * pDlg = (CSocktServerDlg*)pApp->m_pMainWnd;
		CString temp;
		pDlg->GetDlgItemText(IDC_RICHEDIT21,temp);
		temp += TEXT("连接成功\n");
		pDlg->SetDlgItemText(IDC_RICHEDIT21,temp);

		AsyncSelect(FD_READ); 
	}
		//提请一个“读”的网络事件，准备接收
		CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnAccept(int nErrorCode)
{
	//侦听到连接请求，调用Accept函数 
	if (nErrorCode==0)
	{
		CMySocket* pSocket = new CMySocket(); 
		if(Accept(*pSocket))
		{ 
			pSocket->AsyncSelect(FD_READ);
			m_pSocket=pSocket;
			CSocktServerApp * pApp = (CSocktServerApp *)AfxGetApp();
			CSocktServerDlg * pDlg = (CSocktServerDlg*)pApp->m_pMainWnd;
			CString temp;
			pDlg->GetDlgItemText(IDC_RICHEDIT21,temp);
			temp += TEXT("接收到一个连接\n");
			pDlg->SetDlgItemText(IDC_RICHEDIT21,temp);
			AsyncSelect(FD_CLOSE);
		}
		else
			delete pSocket;
	}
} 

void CMySocket::OnClose(int nErrorCode)
{
	if (nErrorCode==0)
	{
		CSocktServerApp * pApp = (CSocktServerApp *)AfxGetApp();
		CSocktServerDlg * pDlg = (CSocktServerDlg*)pApp->m_pMainWnd;
		CString temp;
		pDlg->GetDlgItemText(IDC_RICHEDIT21,temp);
		temp += TEXT("连接关闭\n");
		pDlg->SetDlgItemText(IDC_RICHEDIT21,temp);
	}
	CAsyncSocket::OnClose(nErrorCode);
} 