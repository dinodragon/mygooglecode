// DataSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "ReplayClient.h"
#include "DataSocket.h"
#include "ReplayClientDlg.h"


// CDataSocket

CDataSocket::CDataSocket()
{
	m_nLength=0;
	memset(m_szBuffer,0,sizeof(m_szBuffer)); 
	m_bConnected=FALSE;
}

CDataSocket::~CDataSocket()
{
	if(m_hSocket!=INVALID_SOCKET) 
	Close();
	ShutDown();
}


// CDataSocket 成员函数
// CMySocket 成员函数


void CDataSocket::OnReceive(int nErrorCode)
{
	m_nLength=Receive(m_szBuffer,sizeof(m_szBuffer),0);
	AddMessage(CString(m_szBuffer));

	memset(m_szBuffer,0,sizeof(m_szBuffer)); 
	CAsyncSocket::OnReceive(nErrorCode);
}

void CDataSocket::OnSend(int nErrorCode) 
{
	memset(m_szBuffer,0,sizeof(m_szBuffer)); 
	//继续提请一个“读”的网络事件，接收Server消息
	AsyncSelect(FD_READ); 
	CAsyncSocket::OnSend(nErrorCode);
}

void CDataSocket::OnConnect(int nErrorCode)
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

void CDataSocket::OnClose(int nErrorCode)
{
	if (nErrorCode==0)
	{
		m_bConnected = FALSE;
		AddMessage(_T("连接关闭!"));
	}
	CAsyncSocket::OnClose(nErrorCode);
} 

void CDataSocket::AddMessage(CString str)
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

void CDataSocket::showError(int error)
{
	CString temp;
	temp.Format(_T("错误码:%d"),error);
	AddMessage(temp);
}