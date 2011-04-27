// MySocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ReplayServer.h"
#include "MySocket.h"
#include "ReplayServerDlg.h"


// CMySocket

// CMySocket ��Ա����
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
	if(m_nLength <= 0) Close();

	
	AddMessage(CString(m_szBuffer));
	if(CString(m_szBuffer).Find(_T("open")) >=0)
	{
		AddMessage(_T("��!"));
		WinExec("D:\\Program Files\\Symantec\\pcAnywhere\\awhost32.exe D:\\pcAnywhere\\replay.BHF",SW_SHOWDEFAULT);
	}
	strcat_s(m_szBuffer,sizeof(m_szBuffer),"From Reply");
	AddMessage(_T("����:")+CString(m_szBuffer));
	Send(m_szBuffer,strlen(m_szBuffer)+1,0);
	
	memset(m_szBuffer,0,sizeof(m_szBuffer)); 
	CAsyncSocket::OnReceive(nErrorCode);
}

void CMySocket::OnSend(int nErrorCode) 
{
	memset(m_szBuffer,0,sizeof(m_szBuffer)); 
	//��������һ���������������¼�������Server��Ϣ
	//AsyncSelect(FD_READ); 
	CAsyncSocket::OnSend(nErrorCode);
}

void CMySocket::OnConnect(int nErrorCode)
{ 
	if(nErrorCode==0)
	{
		m_bConnected=TRUE;
		AddMessage(_T("���ӳɹ�!"));
		AsyncSelect(); 
	}
	else
	{
		showError(nErrorCode);
	}
	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnClose(int nErrorCode)
{
	if(nErrorCode==0)
	{
		m_bConnected = FALSE;
		AddMessage(_T("���ӹر�!"));
	}
	else
	{
		showError(nErrorCode);
	}
	m_bConnected=FALSE;
	CAsyncSocket::OnClose(nErrorCode);
} 

void CMySocket::AddMessage(CString str)
{
	CReplayServerApp * pApp = (CReplayServerApp *)AfxGetApp();
	CReplayServerDlg * pDlg = (CReplayServerDlg*)pApp->m_pMainWnd;
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
	temp.Format(_T("������:%d"),error);
	AddMessage(temp);
}