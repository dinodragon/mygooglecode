#include "StdAfx.h"
#include "MainDlg.h"



LRESULT CMainDlg::OnBnClickedOk(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_SSERVER,m_sServer.GetBuffer(80),80);
	m_sServer.ReleaseBuffer();
	MessageBox(m_sServer);
	return 0;
}
