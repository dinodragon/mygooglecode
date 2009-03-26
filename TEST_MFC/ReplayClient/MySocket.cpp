// MySocket.cpp : 实现文件
//

#include "stdafx.h"
#include "ReplayClient.h"
#include "MySocket.h"
#include "ReplayClientDlg.h"


// CMySocket

// CMySocket 成员函数
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
	AddMessage(CString(m_szBuffer));

	memset(m_szBuffer,0,sizeof(m_szBuffer)); 
	CAsyncSocket::OnReceive(nErrorCode);
}

void CMySocket::OnSend(int nErrorCode) 
{
	memset(m_szBuffer,0,sizeof(m_szBuffer)); 
	//继续提请一个“读”的网络事件，接收Server消息
	AsyncSelect(FD_READ); 
	CAsyncSocket::OnSend(nErrorCode);
}

void CMySocket::OnConnect(int nErrorCode)
{ 
	if(nErrorCode==0)
	{
		m_bConnected=TRUE;
		AddMessage(_T("连接成功!"));
		AsyncSelect(FD_READ); 
	}
	else
	{
		showError(nErrorCode);
	}
	
	//提请一个“读”的网络事件，准备接收
	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnClose(int nErrorCode)
{
	if (nErrorCode==0)
	{
		m_bConnected = FALSE;
		AddMessage(_T("连接关闭!"));
	}
	CAsyncSocket::OnClose(nErrorCode);
} 

void CMySocket::OnAccept(int nErrorCode)
{
	//侦听到连接请求，调用Accept函数 
	if (nErrorCode==0)
	{
		if(Accept(*this))
		{ 
			AsyncSelect(FD_READ);
			AddMessage(_T("接收到一个连接\n"));
			AsyncSelect(FD_CLOSE);
		}
	}
	else
	{
		showError(nErrorCode);
	}
	CAsyncSocket::OnAccept(nErrorCode);
}




void CMySocket::AddMessage(CString str)
{
	CReplayClientApp * pApp = (CReplayClientApp *)AfxGetApp();
	CReplayClientDlg * pDlg = (CReplayClientDlg*)pApp->m_pMainWnd;
	CString temp;
	pDlg->GetDlgItemText(IDC_RICHEDIT21,temp);
	if( -1==str.Find(_T("\r")) && -1==str.Find(_T("\n")))
		str += _T("\n");
	temp += str;
	pDlg->SetDlgItemText(IDC_RICHEDIT21,temp);

	CRichEditCtrl * m_RichEditCtrl = (CRichEditCtrl *)pDlg->GetDlgItem(IDC_RICHEDIT21);
	m_RichEditCtrl->LineScroll(2,1);
}

void CMySocket::showError(int error)
{
	CString temp;
	temp.Format(_T("错误码:%d"),error);
	AddMessage(temp);
}