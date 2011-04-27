Introduction
This article presents two classes: CTelnet and CTelnetSocket, and one global function: TelnetThread. Using the CTelnet class, you can access/control your application remotely using a Telnet client. The download contains the classes to use, and a program to demonstrate the use of the CTelnet class.

CTelnetSocket is a class that is used internally (using Winsock calls). The global TelnetThread function is started as a separate thread. This way your application can run and the TelnetThread does all the Telnet activity. You can register some callback functions which are called by the TelnetThread. Usage is very easy:

Instantiate the CTelnet class:

CTelnet telnet( "Welcome at my telnetserver\r\n"    // intro screen
          , "scott"                               // userid
          , "Enter userid:"                     // userid prompt
          , "tiger"                           // password
          , "Enter password: "              // password prompt
          , "Command >"                   // prompt to use
          , 23 );                       // port to run on
Say, you want a function to be called whenever a user types help. Create a help function like this:

CString help( const CString& sArg );        // help function prototype

// implementation of the help function
CString help( const CString& sArg )
{
    return "\r\nCurrently no commands are implemented\r\n";
}
So this function gets called whenever the user types help (Not case sensitive). It will send data to the client "Currently no commands are implemented". When the user types "help command", sArg will contain the value " command". The next step is to register this (callback) function:

telnet.registerFunction( help , "help" );
You can create as much callback functions as you like. It is also possible to write a callback function that is called whenever the user just presses "enter". Register the function, and leave the second argument empty ("").

The next step is to start the service.

telnet.start();
Now, a user can connect to your application, that's it... Please note that a separate thread is running your Telnet service. So your application can do whatever you want after the start method is called.

Stopping the Telnet server is done by the destructor, or by calling the method stop:

telnet.stop();
When the application is running, you have two methods available: write() and setPrompt(). With the write method, you can write data to the client connected. E.g. it can be used for sending trace data.

telnet.write( "this will be sent to the client connected" );
Please note that this method cannot be used by any of the callback functions (It is not needed anyway, see implementation of callback help function).

Another method that can be called when the Telnet server is running is: setPrompt, which sets the prompt which is presented to the client:

telnet.setPrompt( "Another prompt>" );
Please note that this method cannot be used by any of the callback functions.

Final remarks:

For every instantiation of the CTelnet class, only one client can connect, you can however instantiate as many instances of CTelnet as you like. 
When sharing data between the application and the callback functions (e.g. global variables), make sure you do that thread safe (e.g. using Critical Sections). The sample program which comes with the project files should give an idea on how to do this. 
Most methods give back a boolean, true means it succeeded, false means it did not succeed. Call getLastError() to get the error that occurred. 
The Telnet client connected should not do a local echo because the server does that itself. 
Only backspace is implemented as a text editor command. 
Have fun!

 
License
This article has no explicit license attached to it but may contain usage terms in the article text or the download files themselves. If in doubt please contact the author via the discussion board below.

A list of licenses authors might use can be found here

About the Author
J.Hogendoorn


 
Location:   Netherlands 
 

Other popular Internet / Network articles:
An Asynchronous Socket Server and Client
An asynchronous socket server and client with encryption and compression.
MyDownloader: A Multi-thread C# Segmented Download Manager
Sample application that manages multiple segmented downloads and supports HTTP, FTP and YouTube video downloads
Network Development Kit 2.0
Network Development Kit is a set of simple classes for a client-server architecture.
Developing Firewalls for Windows 2000/XP
An article about developing Firewalls for Windows 2000/XP
A simple IOCP Server/Client Class
This source code uses the advanced IOCP technology which can efficiently serve multiple clients. It also presents some solutions to practical problems that arise with the IOCP programming API, and provides a simple echo client/server with file transfer. 
