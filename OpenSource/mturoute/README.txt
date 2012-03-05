mturoute.exe
============

From Eli:
=========
Fixes:

2008-01-18:
* Fixed up some buffer size related bugs, hopefully squashing any mysterious crashes that people may
  have been having.  In particular, if large packet sizes crashed for you before (in theory) they
  should be working now.
* added a "-v" option to output version information so I don't get confused.  Since I had previously
  dubbed Ivan's version "v2", I am unceremoniously dubbing this version "v2.1".  Incremental fixes
  will be v2.2, v2.3 etc.  Huge changes, if ever, might make a v3.
* Speed fixes for dealing with unresponsive hosts.  Rather than ticking down from the base test
  value all the way to the minimum MTU, mturoute will now throw out a minimum sized packet before
  it begins.  If this minimum packet times out, we skip all the larger packets.  Under the default
  settings this should result in an approx 3 second wait for non-responsive hosts.
* Fixed some embarrassing spelling errors and cleaned up a bit of output.  Non-responsive hosts will
  no longer report things like "------------------ host: blah max: 120 bytes", rather a message about
  them being non-responsive will be issued.



From Ivan:
==========
Fixed and improved a few things:

2007-09-30:
* Fixed the error where the "Fragmentation needed but DF set" ICMP reply would be 
  interpreted as successful ping;
* Fixed the handling of "ICMP Destination network unreachable" ICMP reply caused 
  by access lists. They are handled as successful pings (at least we're measuring 
  the path MTU until the filtering point, as the DF-related ICMP would be sent by a 
  previous hop).
* Added the "-r" option to specify the number of retries on timeouts.

2007-10-03:
* Recompiled without shared Visual C++ runtime.
* Added the '-d' flag to display in-depth ICMP status
* Added the link to 'IOS hints' blog in the 'usage' printout

The source is compiled from the Eli Fulkerson's distribution with the Visual C++ 2005 Express Edition. 
The ICMP library is no longer needed, the image is using the Windows XP helper API, which provides 
updated functionality with the same API. The exe file requires (to the best of my knowledge) no other
external libraries.

Ivan Pepelnjak
http://ioshints.blogspot.com

=============================================
The original README form Eli Fulkerson
=============================================
To compile, the following must be present:

icmp_dev-0.1.2 in the parent directory
cl, nmake from Microsofts Visual Studio or standalone compiler.

If everything is present, "make.bat" should compile everything.  

This application is based on ping_src-0.1.4.zip, which is available at
http://fgouget.free.fr/bing/index-en.shtml.  icmp_dev-0.1.2 is available
there too.


The original license on ping_src-0.1.4.zip was available under the following
guidelines:

"All the applications are free (BSD, GNU, or even no license) and come with 
the source. Don't hesitate to modify them, tweak them, enhance them. I will 
appreciate it if you send me your suggestions, source modifications, .. "


My modifications, as far as I'm concerned, are available under the same guidelines.

My version of this application lives at: http://www.elifulkerson.com