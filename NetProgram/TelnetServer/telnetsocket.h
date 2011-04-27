///////////////////////////////////////////////////////////////////////
// Filename: telnetsocket.h
//
// Date    : 27-May-2001
// Author  : J.Hogendoorn ( jeroenhog@gmx.net )
//
// Note    : this code may be used anywhere as long
//         : as this comment remains. 
//
///////////////////////////////////////////////////////////////////////

#ifndef _TELNETSOCKET_H_
#define _TELNETSOCKET_H_

class CTelnetSocket  
{
public:
	CTelnetSocket();
	virtual ~CTelnetSocket();

	bool    initialize( DWORD dwPortNr );
	bool    waitForConnection();
	CString getLastError() const;
	CString getClientIp() const;
	bool    sendData( const CString& sData );
	bool    waitForData( CString& sData , bool bIsPassword = false );
	void    closeClientSocket();
	void    closeServerSocket();
private:
	CString     m_sLastError;
	int         m_iSock;
	int 	    m_iClientSock;
	CString     m_sClientIp;
	sockaddr_in m_siUs;
	sockaddr_in m_siThem;
};
//-------------------------------------------------------------------------
inline CString CTelnetSocket::getLastError() const
{
	return m_sLastError;
};
//-------------------------------------------------------------------------
inline CString CTelnetSocket::getClientIp() const
{
	return m_sClientIp;
};
//-------------------------------------------------------------------------
#endif 
