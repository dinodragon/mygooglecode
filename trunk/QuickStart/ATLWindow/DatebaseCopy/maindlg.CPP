#include "StdAfx.h"
#include "MainDlg.h"
#include "DataCopyer.h"

LRESULT CMainDlg::OnBnClickedOk(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//MessageBox(m_sServer);
	CDataCopyer *pCdc = CDataCopyer::GetInstance();
	pCdc->SetSource(m_sServer,m_sUser,m_sPwd,m_sDb,m_sLocalpath,m_sNetpath);
	//CDataCopyer.GetInstance()->SetDestination(m_dServer,m_dUser,m_dPwd,m_dDb,m_dLocalpath,m_dNetpath);
	return 0;
}


