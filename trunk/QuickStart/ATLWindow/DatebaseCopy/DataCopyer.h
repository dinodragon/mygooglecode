#pragma once
#ifndef _DATACOPYER
#define _DATACOPYER


#include <atlstr.h>

class CDataCopyer
{
public:
	static CDataCopyer * GetInstance();
	void SetSource(CString Server,CString User,CString PWD,CString DB,CString LocalPath,CString NetPath);
	void SetDestination(CString Server,CString User,CString PWD,CString DB,CString LocalPath,CString NetPath);
	BOOL Backup();
	BOOL CopyFile();
	BOOL Restore();

private:
	static CDataCopyer * m_Instance;
	CDataCopyer(void);
	~CDataCopyer(void);


	CString m_sServer;
	CString m_sUser;
	CString m_sPwd;
	CString m_sDb;
	CString m_sLocalpath;
	CString m_sNetpath;

	CString m_dServer;
	CString m_dUser;
	CString m_dPwd;
	CString m_dDb;
	CString m_dLocalpath;
	CString m_dNetpath;

	CString m_backupFileName;
};

__declspec(selectany) CDataCopyer * CDataCopyer::m_Instance = NULL;

#endif