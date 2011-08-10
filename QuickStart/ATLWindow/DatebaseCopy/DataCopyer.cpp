#include "StdAfx.h"
#include "DataCopyer.h"
#include <time.h>
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
	m_sLocalpath  = LocalPath;
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

BOOL CDataCopyer::Backup()
{
	HRESULT hr = CoInitialize(NULL);
	assert(SUCCEEDED(hr));
	ADODB::_ConnectionPtr pConn(__uuidof(ADODB::Connection));
	CString conn;
	conn.Format(TEXT("Provider=SQLOLEDB.1;Data Source=%s;Initial Catalog=%s;Persist Security Info=True"),m_sServer,m_sDb);
	hr = pConn->Open(conn.AllocSysString(),m_sUser.AllocSysString(),m_sPwd.AllocSysString(),ADODB::adConnectUnspecified);
	assert(SUCCEEDED(hr));

	TCHAR tmp[64] = _T("aaaa"); 
	time_t t = time(0); 
	tm stm;
	localtime_s(&stm,&t);
	/*_tcsftime(tmp, sizeof(tmp),_T("%Y%m%d%H%M%S"),&stm);*/
	//很奇怪的现象，如果使用了上面的语句，则成员变量m_sLocalpath则无法访问。
	m_backupFileName.Format(_T("%s_%d%d%d%d%d%d.bak"),m_sDb,stm.tm_year,stm.tm_mon,stm.tm_mday,stm.tm_hour,stm.tm_min,stm.tm_sec);
	CString buckupSql;
	buckupSql.Format(_T("BACKUP DATABASE [%s] TO DISK = N'%s\\%s'\r\nWITH NOFORMAT,NOINIT,NAME = N'Full Database Backup',SKIP,NOREWIND,NOUNLOAD,STATS = 10"),m_sDb,m_sLocalpath,m_backupFileName);
	pConn->Execute(buckupSql.AllocSysString(),NULL,ADODB::adOptionUnspecified);
	hr = pConn->Close();
	assert(SUCCEEDED(hr));
	CoUninitialize();
	return FALSE;
}

BOOL CDataCopyer::CopyFile()
{
	CString sNetFile,dNetFile;
	sNetFile.Format(_T("%s\\%s"),m_sNetpath,m_backupFileName);
	dNetFile.Format(_T("%s\\%s"),m_dNetpath,m_backupFileName);
	::CopyFile(sNetFile,dNetFile,FALSE);
	return FALSE;
}

BOOL CDataCopyer::Restore()
{
	HRESULT hr = CoInitialize(NULL);
	assert(SUCCEEDED(hr));
	ADODB::_ConnectionPtr pConn(__uuidof(ADODB::Connection));
	CString conn;
	conn.Format(TEXT("Provider=SQLOLEDB.1;Data Source=%s;Initial Catalog=%s;Persist Security Info=True"),m_dServer,m_dDb);
	hr = pConn->Open(conn.AllocSysString(),m_dUser.AllocSysString(),m_dPwd.AllocSysString(),ADODB::adConnectUnspecified);
	assert(SUCCEEDED(hr));
	CString restoreSql;
	restoreSql.Format(_T("RESTORE DATABASE [%s] FROM  DISK = N'%s\\%s'"),m_dDb,m_dLocalpath,m_backupFileName);
	pConn->Execute(restoreSql.AllocSysString(),NULL,ADODB::adOptionUnspecified);
	hr = pConn->Close();
	assert(SUCCEEDED(hr));
	CoUninitialize();
	return TRUE;
}