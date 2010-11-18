static char *version_id = 
	"@(#)Copyright (C) H.Shirouzu 2010   version.cpp	Ver2.11";
/* ========================================================================
	Project  Name			: IP Messenger for Win32
	Module Name				: Version
	Create					: 2010-05-23(Sun)
	Update					: 2010-09-18(Sat)
	Copyright				: H.Shirouzu
	Reference				: 
	======================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	Version•¶Žš—ñ
*/
char *GetVersionStr()
{
	return	strstr(version_id, "Ver") + 3;
}


