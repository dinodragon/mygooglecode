static char *logmng_id = 
	"@(#)Copyright (C) H.Shirouzu 1996-2002   logmng.cpp	Ver2.00";
/* ========================================================================
	Project  Name			: IP Messenger for Win32
	Module Name				: Log Manager
	Create					: 1996-08-18(Sun)
	Update					: 2002-11-03(Sun)
	Copyright				: H.Shirouzu
	Reference				: 
	======================================================================== */

#include "tlib/tlib.h"
#include "resource.h"
#include "ipmsg.h"
#include <mbstring.h>

LogMng::LogMng(Cfg *_cfg)
{
	cfg = _cfg;
}

BOOL LogMng::WriteSendStart()
{
	return	WriteStart();
}

BOOL LogMng::WriteSendHead(LPCSTR head)
{
	char	buf[MAX_LISTBUF];

	wsprintf(buf, " To: %s\r\n", head);
	return	Write(buf);
}

BOOL LogMng::WriteSendMsg(LPCSTR msg, ULONG command, ShareInfo *shareInfo)
{
	return	WriteMsg(msg, command, shareInfo);
}

BOOL LogMng::WriteRecvMsg(MsgBuf *msg, THosts *hosts, ShareInfo *shareInfo)
{
	if (msg->command & IPMSG_NOLOGOPT)
		return	FALSE;

	WriteStart();
	char	buf[MAX_PATH_U8] = " From: ";

	MakeListString(cfg, &msg->hostSub, hosts, buf + strlen(buf));
	strcat(buf, "\r\n");
	Write(buf);

	return	WriteMsg(msg->msgBuf, msg->command, shareInfo);
}

BOOL LogMng::WriteStart(void)
{
	return	Write("=====================================\r\n");
}

BOOL LogMng::WriteMsg(LPCSTR msg, ULONG command, ShareInfo *shareInfo)
{
	char	buf[MAX_BUF * 2] = "  at ";

	strcat(buf, Ctime()); 
	strcat(buf, " ");

	if (command & IPMSG_BROADCASTOPT)
		strcat(buf, GetLoadStrU8(IDS_BROADCASTLOG));

	if (command & IPMSG_AUTORETOPT)
		strcat(buf, GetLoadStrU8(IDS_AUTORETLOG));

	if (command & IPMSG_MULTICASTOPT)
		strcat(buf, GetLoadStrU8(IDS_MULTICASTLOG));

	if (command & IPMSG_ENCRYPTOPT)
		strcat(buf, GetLoadStrU8(IDS_ENCRYPT));

	if (command & IPMSG_SECRETOPT)
	{
		if (command & IPMSG_PASSWORDOPT)
			strcat(buf, GetLoadStrU8(IDS_PASSWDLOG));
		else
			strcat(buf, GetLoadStrU8(IDS_SECRETLOG));
	}

	if (shareInfo && (command & IPMSG_FILEATTACHOPT))
	{
		strcat(buf, "\r\n  ");
		strcat(buf, GetLoadStrU8(IDS_FILEATTACH));
		strcat(buf, " ");
		char	fname[MAX_PATH_U8], *ptr = buf + strlen(buf);

		for (int cnt=0; cnt < shareInfo->fileCnt && ptr-buf < sizeof(buf)-MAX_PATH_U8; cnt++)
		{
			ForcePathToFname(shareInfo->fileInfo[cnt]->Fname(), fname);
			ptr += wsprintf(ptr, "%s%s", fname, cnt+1 == shareInfo->fileCnt ? "" : ", ");
		}
	}
	strcat(buf, "\r\n-------------------------------------\r\n");

	if (Write(buf) && Write(msg) && Write("\r\n\r\n"))
		return	TRUE;
	else
		return	FALSE;
}

inline int bit_cnt(unsigned char c)
{
	int bit;
	for (bit=0; c; c>>=1)
		if (c&1)
			bit++;
	return	bit;
}

inline char make_key(char *password)
{
	char	key = 0;

	while (*password)
		key += *password++;

	return	key;
}

BOOL LogMng::Write(LPCSTR str)
{
	BOOL	ret = FALSE;

	if (cfg->LogCheck == FALSE || *cfg->LogFile == 0)
		return	TRUE;

	HANDLE		fh;
	DWORD		size;

	if ((fh = CreateFileU8(cfg->LogFile, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0)) != INVALID_HANDLE_VALUE)
	{
		::SetFilePointer(fh, 0, 0, FILE_END);
		str = cfg->LogUTF8 ? str : U8toA(str);
		ret = ::WriteFile(fh, str, strlen(str), &size, NULL);
		::CloseHandle(fh);
	}

	return	ret;
}

void LogMng::StrictLogFile(char *logFile)
{
	if (strncmp(logFile, "\\\\", 2) == 0 || logFile[0] == 0 || logFile[1] == ':')
		return;

	char	orgPath[MAX_PATH_U8], buf[MAX_PATH_U8], *tmp=NULL;

	strcpy(orgPath, logFile);

	if (strchr(logFile, '\\') == NULL) {
		TRegistry	reg(HKEY_CURRENT_USER);
		if (reg.OpenKey(REGSTR_SHELLFOLDERS)) {
			if (reg.GetStr(REGSTR_MYDOCUMENT, buf, sizeof(buf))) {
				MakePath(logFile, buf, orgPath);
				return;
			}
		}
	}

	GetFullPathNameU8(orgPath, MAX_PATH_U8, logFile, &tmp);
	return;
}

