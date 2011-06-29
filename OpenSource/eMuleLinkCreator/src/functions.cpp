//this file is part of eMule
//Copyright (C)2004 Merkur ( merkur-@users.sourceforge.net / http://www.emule-project.net )
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "stdafx.h"
#include <Wininet.h>

#include "functions.h"
#include "FileHasher.h"
#include "SHAHashSet.h"

CString CreateED2kLink(const CKnownFile* f, const CString strAdditionalParameter, bool bAICH, bool bHashset)
{
	const CKnownFile* pFile = f;
	CString strLink;
	CString strAICH;
	CString strHS;

	if (bAICH && f->m_pAICHHashSet->GetStatus() == AICH_HASHSETCOMPLETE)
		strAICH = _T("h=")+f->m_pAICHHashSet->GetMasterHash().GetString()+_T("|");

	if (bHashset)
	{
		if (pFile->GetHashCount() > 0 && pFile->GetHashCount() == pFile->GetED2KPartHashCount())
		{
			strHS= _T("p=");
			for (int i = 0; i < pFile->GetHashCount(); i++)
			{
				if (i > 0)
					strHS += _T(':');
				strHS += EncodeBase16(pFile->GetPartHash(i), 16);
			}
			strHS += _T('|');
		}
	} else
		strHS=_T("");


	strLink.Format(_T("ed2k://|file|%s|%I64u|%s|%s%s%s/"),
		StripInvalidFilenameChars(f->GetFileName(), false),	// spaces to dots
		f->GetFileSize(),
		EncodeBase16(f->GetFileHash(),16),
		strHS,
		strAICH,
		strAdditionalParameter
		);

	return strLink;
}

CString EncodeBase16(const unsigned char* buffer, unsigned int bufLen)
{
	CString Base16Buff;

	for(unsigned int i = 0; i < bufLen; i++) {
		Base16Buff += base16Chars[buffer[i] >> 4];
		Base16Buff += base16Chars[buffer[i] & 0xf];
	}

    return Base16Buff;
}

CString CreateED2kHashsetLink(const CKnownFile* pFile, const CString strAdditionalParameter, bool bAICH)
{
	return CreateED2kLink(pFile,strAdditionalParameter,bAICH,true);
}

CString StripInvalidFilenameChars(CString strText, bool bKeepSpaces)
{
	LPTSTR pszBuffer = strText.GetBuffer();
	LPTSTR pszSource = pszBuffer;
	LPTSTR pszDest = pszBuffer;

	while (*pszSource != '\0')
	{
		if (!((*pszSource <= 31 && *pszSource >= 0)	|| // lots of invalid chars for filenames in windows :=)
			*pszSource == '\"' || *pszSource == '*' || *pszSource == '<'  || *pszSource == '>' ||
			*pszSource == '?'  || *pszSource == '|' || *pszSource == '\\' || *pszSource == '/' || 
			*pszSource == ':') )
		{
			if (!bKeepSpaces && *pszSource == ' ')
				*pszDest = '.';
			*pszDest = *pszSource;
			pszDest++;
		}
		pszSource++;
	}
	*pszDest = '\0';
	strText.ReleaseBuffer();
	return strText;
}

bool CopyTextToClipboard( CString strText )
{
	if (strText.IsEmpty())
		return false;

	//allocate global memory & lock it
	HGLOBAL hGlobal = GlobalAlloc(GHND | GMEM_SHARE, (strText.GetLength() + 1)*sizeof(TCHAR));
	if(hGlobal == NULL)
		return false;

	PTSTR pGlobal = static_cast<PTSTR>(GlobalLock(hGlobal));
	if( pGlobal == NULL ){
		GlobalFree(hGlobal);
		return false;
	}

	//copy the text
	_tcscpy(pGlobal, (LPCTSTR)strText);
	GlobalUnlock(hGlobal);

	//Open the Clipboard and insert the handle into the global memory
	bool bResult = false;
	if( OpenClipboard(NULL) )
	{
		if( EmptyClipboard() )
#ifdef _UNICODE
			bResult = (SetClipboardData(CF_UNICODETEXT,hGlobal) != NULL);
#else
			bResult = (SetClipboardData(CF_TEXT,hGlobal) != NULL);
#endif
		CloseClipboard();
	}
	GlobalFree(hGlobal);
	return bResult;
}
static byte base32Chars [33] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
CString EncodeBase32(const unsigned char* buffer, unsigned int bufLen)
{
	CString Base32Buff;

	unsigned int i, index;
	unsigned char word;

	for(i = 0, index = 0; i < bufLen;) {

		// Is the current word going to span a byte boundary?
		if (index > 3) {
			word = (buffer[i] & (0xFF >> index));
			index = (index + 5) % 8;
			word <<= index;
			if (i < bufLen - 1)
				word |= buffer[i + 1] >> (8 - index);

			i++;
		} else {
			word = (buffer[i] >> (8 - (index + 5))) & 0x1F;
			index = (index + 5) % 8;
			if (index == 0)
				i++;
		}

		Base32Buff += (char) base32Chars[word];
	}

	return Base32Buff;
}

uint32 DecodeBase32(LPCTSTR pszInput, uchar* paucOutput, uint32 nBufferLen)
{
	if (pszInput == NULL)
		return false;
	uint32 nDecodeLen = (_tcslen(pszInput)*5)/8;
	if ((_tcslen(pszInput)*5) % 8 > 0)
		nDecodeLen++;
	uint32 nInputLen = _tcslen( pszInput );
	if (paucOutput == NULL || nBufferLen == 0)
		return nDecodeLen;
	if (nDecodeLen > nBufferLen || paucOutput == NULL) 
		return 0;

	DWORD nBits	= 0;
	int nCount	= 0;

	for ( int nChars = nInputLen ; nChars-- ; pszInput++ )
	{
		if ( *pszInput >= 'A' && *pszInput <= 'Z' )
			nBits |= ( *pszInput - 'A' );
		else if ( *pszInput >= 'a' && *pszInput <= 'z' )
			nBits |= ( *pszInput - 'a' );
		else if ( *pszInput >= '2' && *pszInput <= '7' )
			nBits |= ( *pszInput - '2' + 26 );
		else
			return 0;

		nCount += 5;

		if ( nCount >= 8 )
		{
			*paucOutput++ = (BYTE)( nBits >> ( nCount - 8 ) );
			nCount -= 8;
		}

		nBits <<= 5;
	}

	return nDecodeLen;
}

uint32 DecodeBase32(LPCTSTR pszInput, CAICHHash& Hash){
	return DecodeBase32(pszInput, Hash.GetRawHash(), Hash.GetHashSize());
}

UINT64 GetHTTPRequestDataSize(CString strSource) 
{
	UINT64 dwFileSize=0;

	// prepare url components
	CString host,res;
	int port=0;

	if (strSource.Left(7).CompareNoCase("http://")==0)
		host=strSource.Mid(7);
	else 
		host=strSource;

	int pos=host.Find(':');
	int posr=host.Find('/');
	if (posr==-1)
		return 0;
	if (pos>-1 && posr>pos)
		port=atoi(host.Mid(pos+1,posr-pos-1));
	res=host.Mid(posr);
	host=host.Left( (pos>0)?pos: posr);


	// Initialize use of the WinINet functions
	HINTERNET hInternet=InternetOpen(
		"LinkCreatorAgent",
		INTERNET_OPEN_TYPE_PRECONFIG,
		NULL,
		NULL,
		0
		);

	if (hInternet==NULL)
		return 0;

	// Opens an HTTP session for the ressources host
	HINTERNET hConnect = ::InternetConnect(hInternet, host, (port)?port:INTERNET_DEFAULT_HTTP_PORT, "", "", INTERNET_SERVICE_HTTP, 0, 0);
	if (!hConnect) {
		InternetCloseHandle(hInternet);
		return 0;
	}

	// requests a ressource via http
	HINTERNET hHttpFile = ::HttpOpenRequest(hConnect, "GET", res, HTTP_VERSION, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
	if (!hHttpFile) {
		InternetCloseHandle(hConnect);
		InternetCloseHandle(hInternet);
		return 0;
	}

	// Get the size of the requested file
	BOOL bSendRequest = ::HttpSendRequest(hHttpFile, NULL, 0, 0, 0);
	char achQueryBuf[16];
	DWORD dwQueryBufLen = sizeof(achQueryBuf);

	BOOL bQuery = ::HttpQueryInfo(hHttpFile,HTTP_QUERY_CONTENT_LENGTH, achQueryBuf,&dwQueryBufLen, NULL);
	if (bQuery)
		dwFileSize = _atoi64 (achQueryBuf);


	// Close the HINTERNET handles.
	if (hHttpFile)
		InternetCloseHandle(hHttpFile);
	if (hConnect)
		InternetCloseHandle(hConnect);
	if (hInternet)
		InternetCloseHandle(hInternet);

	return dwFileSize;
}
