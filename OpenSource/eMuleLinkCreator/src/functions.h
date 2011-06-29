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

#pragma once
class CAbstractFile;
class CKnownFile;
class CAICHHash;

CString CreateED2kLink(const CKnownFile* f, const CString strAdditionalParameter, bool bAICH = true, bool bHashset = false);
CString StripInvalidFilenameChars(CString strText, bool bKeepSpaces);
CString EncodeBase16(const unsigned char* buffer, unsigned int bufLen);
CString CreateED2kHashsetLink(const CKnownFile* pFile, const CString strAdditionalParameter, bool bAICH = true);
bool	CopyTextToClipboard( CString strText );
CString EncodeBase32(const unsigned char* buffer, unsigned int bufLen);
uint32 DecodeBase32(LPCTSTR pszInput, uchar* paucOutput, uint32 nBufferLen);
uint32 DecodeBase32(LPCTSTR pszInput, CAICHHash& Hash);

static byte base16Chars[17] = "0123456789ABCDEF";

__inline int md4cmp(const void* hash1, const void* hash2) {
	return !(((uint32*)hash1)[0] == ((uint32*)hash2)[0] &&
		     ((uint32*)hash1)[1] == ((uint32*)hash2)[1] &&
		     ((uint32*)hash1)[2] == ((uint32*)hash2)[2] &&
		     ((uint32*)hash1)[3] == ((uint32*)hash2)[3]);
}

__inline int isnulmd4(const void* hash) {
	return  (((uint32*)hash)[0] == 0 &&
		     ((uint32*)hash)[1] == 0 &&
		     ((uint32*)hash)[2] == 0 &&
		     ((uint32*)hash)[3] == 0);
}

// md4clr -- replacement for memset(hash,0,16)
__inline void md4clr(const void* hash) {
	((uint32*)hash)[0] = ((uint32*)hash)[1] = ((uint32*)hash)[2] = ((uint32*)hash)[3] = 0;
}

// md4cpy -- replacement for memcpy(dst,src,16)
__inline void md4cpy(void* dst, const void* src) {
	((uint32*)dst)[0] = ((uint32*)src)[0];
	((uint32*)dst)[1] = ((uint32*)src)[1];
	((uint32*)dst)[2] = ((uint32*)src)[2];
	((uint32*)dst)[3] = ((uint32*)src)[3];
}


#define WNDEXSTYLE	(WS_EX_RTLREADING | WS_EX_RIGHT | WS_EX_LTRREADING | WS_EX_LEFT)
CString GetResString(UINT uStringID, WORD wLangID);
CString GetResString(UINT uStringID);
CString GetLangName(LANGID lid);
bool IsLangSupported(LANGID lid);
DWORD GetWndExStyle();
void MakeLangSelection(CComboBox& combo);

// Internet
UINT64 GetHTTPRequestDataSize(CString strSource);


