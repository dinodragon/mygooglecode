// MySocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ReplayClient.h"
#include "MySocket.h"
#include "ReplayClientDlg.h"


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
	AddMessage(CString(m_szBuffer));

	memset(m_szBuffer,0,sizeof(m_szBuffer)); 
	CAsyncSocket::OnReceive(nErrorCode);
}

void CMySocket::OnSend(int nErrorCode) 
{
	memset(m_szBuffer,0,sizeof(m_szBuffer)); 
	//��������һ���������������¼�������Server��Ϣ
	AsyncSelect(FD_READ); 
	CAsyncSocket::OnSend(nErrorCode);
}

void CMySocket::OnConnect(int nErrorCode)
{ 
	if(nErrorCode==0)
	{
		m_bConnected=TRUE;
		AddMessage(_T("���ӳɹ�!"));
		AsyncSelect(FD_READ); 
	}
	else
	{
		showError(nErrorCode);
	}
	
	//����һ���������������¼���׼������
	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnClose(int nErrorCode)
{
	if (nErrorCode==0)
	{
		m_bConnected = FALSE;
		AddMessage(_T("���ӹر�!"));
	}
	CAsyncSocket::OnClose(nErrorCode);
} 

void CMySocket::OnAccept(int nErrorCode)
{
	//�������������󣬵���Accept���� 
	if (nErrorCode==0)
	{
		if(Accept(*this))
		{ 
			AsyncSelect(FD_READ);
			AddMessage(_T("���յ�һ������\n"));
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
	temp.Format(_T("������:%d"),error);
	AddMessage(temp);
}