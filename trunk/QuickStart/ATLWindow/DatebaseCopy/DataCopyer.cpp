#include "StdAfx.h"
#include "DataCopyer.h"
//#import "C:\Program Files\Common Files\System\ado\msado15.dll"
#import "libid:b691e011-1797-432e-907a-4d8c69339129" version("15.0")  rename("EOF","rsEOF")



CDataCopyer::CDataCopyer(void)
{
}

CDataCopyer::~CDataCopyer(void)
{
	if (m_Instance)
	{
		delete m_Instance;
		m_Instance = NULL;
	}
}

CDataCopyer * CDataCopyer::GetInstance()
{
	if (m_Instance != NULL)
	{
		return m_Instance;
	}
	else
	{
		m_Instance = new CDataCopyer();
		return m_Instance;
	}
}

void CDataCopyer::SetSource( CString Server,CString User,CString PWD,CString DB,CString LocalPath,CString NetPath )
{
	m_sServer = Server;
	m_sUser = User;
	m_sPwd = PWD;
	m_sDb = DB;
	m_sLocalpath = LocalPath;
	m_sNetpath = NetPath;
}

void CDataCopyer::SetDestination( CString Server,CString User,CString PWD,CString DB,CString LocalPath,CString NetPath )
{
	m_dServer = Server;
	m_dUser = User;
	m_dPwd = PWD;
	m_dDb = DB;
	m_dLocalpath = LocalPath;
	m_dNetpath = NetPath;
}