///////////////////////////////////////////////////////////////////////
// Filename: telnet.h
//
// Date    : 27-May-2001
// Author  : J.Hogendoorn ( jeroenhog@gmx.net )
//
// Note    : this code may be used anywhere as long
//         : as this comment remains. 
//
///////////////////////////////////////////////////////////////////////

#ifndef _TELNET_H_
#define _TELNET_H_

#include "telnetsocket.h"

void TelnetThread(void* telnet);

using namespace std;

// type definition for callback functions
typedef CString (*callback) (const CString&);

typedef struct
{
	CString  sCommand;		// the command
	callback function;		// the function
} callBackFunction;

// vector with callbackfunctions
typedef vector<callBackFunction> callbackVector;

class CTelnet  
{

public:
	CTelnet( const CString& sIntroScreen
		   , const CString& sPassword
		   , const CString& sPasswordPrompt
		   , const CString& sUserId
		   , const CString& sUserIdPrompt
		   , const CString& sPrompt
		   , DWORD          dwPortNumber
		   );

	virtual ~CTelnet();

	bool           start();
	void           stop();
	bool           registerFunction( CString (*func)(const CString&) , const CString& sCommand );
	bool           write( const CString& sData );
	void           setLastError( const CString& slastError );
	CString        getLastError() const;
	HANDLE		   getThreadStartupSucceededEvent() const;
	HANDLE         getThreadStartupFailedEvent() const;
	CString        getIntroScreen() const;
	CString        getUserId() const;
	CString        getPassword() const;
	CString        getUserIdPrompt() const;
	CString        getPasswordPrompt() const;
	DWORD          getPortNumber() const;
	CString        getPrompt() const;
	void           setPrompt(const CString& sPrompt );
	CTelnetSocket* getTelnetSocket() const;
	void           setLoggedOn();
	void           setNotLoggedOn();
	bool           getLoggedOn() ;
	callback       matchFunction( const CString& sCommand , CString& sArgs );

private:
	void             cleanUp();
	bool             m_bIsRunning;
	bool             m_bLoggedOn;
	CString          m_sLastError;
	CString          m_sIntroScreen;
	CString          m_sUserId;
	CString          m_sPassword;
	CString          m_sUserIdPrompt;
	CString          m_sPasswordPrompt;
	DWORD            m_dwPortNumber;
	CString          m_sCommand;
	CString          m_sPrompt;
	callback         m_function;
	HANDLE           m_hThread;
	CTelnetSocket*   m_telnetSock;
	HANDLE           m_threadStartupSuccceeded;
	HANDLE           m_threadStartupFailed;
	CRITICAL_SECTION m_critSection;
	callbackVector   m_callBackList;

};
//-------------------------------------------------------------------------
inline HANDLE CTelnet::getThreadStartupSucceededEvent() const
{
	return m_threadStartupSuccceeded;
}
//-------------------------------------------------------------------------
inline HANDLE CTelnet::getThreadStartupFailedEvent() const
{
	return m_threadStartupFailed;
}
//-------------------------------------------------------------------------
inline void CTelnet::setLastError( const CString& slastError ) 
{
	m_sLastError = slastError;
}
//-------------------------------------------------------------------------
inline CString CTelnet::getLastError() const
{
	return m_sLastError;
}
//-------------------------------------------------------------------------
inline CTelnetSocket* CTelnet::getTelnetSocket() const
{
	return m_telnetSock;
}
//-------------------------------------------------------------------------
inline CString CTelnet::getIntroScreen() const
{
	return m_sIntroScreen;
}
//-------------------------------------------------------------------------
inline CString CTelnet::getUserId() const
{
	return m_sUserId;
}
//-------------------------------------------------------------------------
inline CString CTelnet::getPassword() const
{
	return m_sPassword;
}
//-------------------------------------------------------------------------
inline CString CTelnet::getUserIdPrompt() const
{
	return m_sUserIdPrompt;
}
//-------------------------------------------------------------------------
inline CString CTelnet::getPasswordPrompt() const
{
	return m_sPasswordPrompt;
}
//-------------------------------------------------------------------------
inline DWORD CTelnet::getPortNumber() const
{
	return m_dwPortNumber;
}
//-------------------------------------------------------------------------
inline CString CTelnet::getPrompt() const 
{
	return m_sPrompt;
}
//-------------------------------------------------------------------------
#endif 
