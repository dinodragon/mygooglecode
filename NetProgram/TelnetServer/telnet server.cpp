#include "stdafx.h"
#include "telnet.h"

// prototypes of callback functions
CString displayHelp( const CString& sArg );
CString trace(       const CString& sArg );
CString stop(        const CString& sArg );
CString nomatch(     const CString& sArg );

// a critical section is needed, bcause
// bStoppping and iCounter are used by the main- and the telnetThread
CRITICAL_SECTION critSection;

bool bStopping = false;
int  iCounter  = 0;
bool bStop     = false;

int main(int argc, char* argv[])
{
	InitializeCriticalSection( &critSection );

	CTelnet telnet( "Welcome at my telnetserver\r\n"		// intro screen
		          , "scott"									// userid
				  , "Enter userid:"							// userid prompt
				  , "tiger"									// userid
				  , "Enter password: "						// password prompt
				  , "Command >"								// prompt to use
				  , 23 );									// port to run on

	// register callback functions
	telnet.registerFunction( trace       , "trace" );		// gets called when user typed 'trace'
	telnet.registerFunction( displayHelp , "help"  );		// gets called when user typed 'help'
	telnet.registerFunction( stop        , "stop"  );		// gets called when user typed 'stop'
	telnet.registerFunction( nomatch     , ""      );		// gets called when user typed ENTER

	// start the server
	if ( !telnet.start() )
	{
		printf( "error occured %s \n", telnet.getLastError() );
		return 0;
	}
	

	// very simple..... just increment counter and sleep for one second
	while( !bStopping )
	{

		iCounter ++;
		Sleep(1000);

		// 30 seconds passed, change prompt
		EnterCriticalSection( &critSection );
		if ( iCounter == 30 )
		{
			telnet.write( "\r\n30 seconds passed, changing prompt!\r\n" );
			telnet.setPrompt( "New prompt >" );
		}
		bStopping = bStop;
		LeaveCriticalSection( &critSection );
	}

	telnet.stop();

	return 0;
}

///////////////////////////////////////////////////////////////////
// gets called when user presses ENTER
CString nomatch( const CString& sArg )
{
	return "Type help for help\r\n";
}

//////////////////////////////////////////////////////////////////
// gets called when user issued 'help'
CString displayHelp( const CString& sArg )
{
	CString sHlp;

	sHlp  = "\r\nCommands currently supported:\r\n\r\n";
	sHlp += "trace           displays current value of the counter\r\n";
	sHlp += "stop            quits the program\r\n";
	sHlp += "stop 10         quits the program over 10 seconds\r\n\r\n";

	return sHlp;
}

//////////////////////////////////////////////////////////////////
// gets called when user issued 'trace'
CString trace( const CString& sArg )
{
	CString sValBack;

	EnterCriticalSection( &critSection );
	sValBack.Format( "\r\nCurrent value of iCounter=%i\r\n", iCounter );
	LeaveCriticalSection( &critSection );

	return sValBack;
}

//////////////////////////////////////////////////////////////////
// gets called when user issued 'stop'
CString stop( const CString& sArg )
{
	if ( sArg == " 10" )
	{
		Sleep(10000);
	}

	EnterCriticalSection( &critSection );
	bStop = true;
	LeaveCriticalSection( &critSection );

	return "Stopping the program\r\n";
}
