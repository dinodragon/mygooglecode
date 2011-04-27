///////////////////////////////////////////////////////////////////////
// Filename: telnetthread.cpp
//
// Date    : 27-May-2001
// Author  : J.Hogendoorn ( jeroenhog@gmx.net )
//
// Note    : this code may be used anywhere as long
//         : as this comment remains. 
//
///////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "telnet.h"

//////////////////////////////////////////////////////////////////////
// Function: TelnetThread
// In      : pointer to CTelnet instance
// Out     : none
// Purpose : uses CTelnet and CTelnetSocket to implement a telnet service
// Note    : runs as a seperate thread
void TelnetThread(void* telnet)
{
	// get pointer to telnet class
	CTelnet* tel = (CTelnet*)telnet;

	// if initialize fails, we'd better stop
	if ( !tel->getTelnetSocket()->initialize( tel->getPortNumber() ) )
	{
		tel->setLastError( "starting telnet server failed: " + tel->getTelnetSocket()->getLastError() );

		// signal event ( makes main thread run )
		SetEvent( tel->getThreadStartupFailedEvent() );
		return;
	}

	// signal event ( makes main thread run )
	SetEvent( tel->getThreadStartupSucceededEvent() );

	// loop forever
	while(1)
	{
		// we are not logged on yet
		tel->setNotLoggedOn();

		if ( !tel->getTelnetSocket()->waitForConnection() )
		{
			continue;
		}

		////////////////////////////////////////////////////////////////////////////////
		// login sequence 
		////////////////////////////////////////////////////////////////////////////////

		// we got a connection now, send the intro screen
		if ( !tel->getTelnetSocket()->sendData( tel->getIntroScreen() ) )
		{
			tel->getTelnetSocket()->closeClientSocket();
			continue;
		}

		CString sUserId;
		if ( tel->getUserId().GetLength() != 0 )
		{
			// ask for userid (send)
			if ( !tel->getTelnetSocket()->sendData( tel->getUserIdPrompt() ) )
			{
				tel->getTelnetSocket()->closeClientSocket();
				continue;
			}

			// ask for userid (receive)
			if ( !tel->getTelnetSocket()->waitForData( sUserId ) )
			{
				tel->getTelnetSocket()->closeClientSocket();
				continue;
			}
		}

		CString sPasswd;
		if ( tel->getPassword().GetLength() != 0 )
		{
			// ask for password (send)
			if ( !tel->getTelnetSocket()->sendData( tel->getPasswordPrompt() ) )
			{
				tel->getTelnetSocket()->closeClientSocket();
				continue;
			}

			// ask for password (receive)
			if ( !tel->getTelnetSocket()->waitForData( sPasswd , true ) )
			{
				tel->getTelnetSocket()->closeClientSocket();
				continue;
			}

		}

		// check for correct password or userid
		if ( tel->getUserId().GetLength() != 0 )
		{
			if ( tel->getUserId() != sUserId )
			{
				// make brute force attack more difficult
				Sleep(5000);

				tel->getTelnetSocket()->closeClientSocket();
				continue;
			}
		}
		if ( tel->getPassword().GetLength() != 0 )
		{
			if ( tel->getPassword() != sPasswd )
			{
				// make brute force attack more difficult
				Sleep(5000);

				tel->getTelnetSocket()->closeClientSocket();
				continue;
			}
		}

		// logged on now
		tel->setLoggedOn();

		///////////////////////////////////////////////////////////////////////////
		// handle commands
		///////////////////////////////////////////////////////////////////////////
		while(1)
		{

			// send the prompt
			if ( !tel->getTelnetSocket()->sendData( tel->getPrompt() ) )
			{
				tel->getTelnetSocket()->closeClientSocket();
				continue;
			}

			// handle commands
			CString sCommand;
			if ( !tel->getTelnetSocket()->waitForData( sCommand ) )
			{
				tel->getTelnetSocket()->closeClientSocket();
				continue;
			}

			CString sArgs;
			callback fun = tel->matchFunction( sCommand , sArgs );
			if ( fun != NULL )
			{
				CString sDataBack = fun( sArgs );
				if ( !tel->getTelnetSocket()->sendData( sDataBack ) )
				{
					tel->getTelnetSocket()->closeClientSocket();
					continue;
				}
			}
		}
	}
};

