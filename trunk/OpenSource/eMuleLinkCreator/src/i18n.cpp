//this file is part of eMule
//Copyright (C)2002-2004 Merkur ( devs@emule-project.net / http://www.emule-project.net )
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "stdafx.h"
#include "LinkCreator.h"
#include "functions.h"
#include <locale.h>

#define LANGID_ZH_CN MAKELANGID(LANG_CHINESE,SUBLANG_CHINESE_SIMPLIFIED)
#define LANGID_ZH_TW MAKELANGID(LANG_CHINESE,SUBLANG_CHINESE_TRADITIONAL)
#define LANGID_CZ_CZ MAKELANGID(LANG_CZECH,SUBLANG_DEFAULT)
#define LANGID_DA_DK MAKELANGID(LANG_DANISH,SUBLANG_DEFAULT)
#define LANGID_EN_US MAKELANGID(LANG_ENGLISH,SUBLANG_DEFAULT)
#define LANGID_GL_ES MAKELANGID(LANG_GALICIAN,SUBLANG_DEFAULT)
#define LANGID_DE_DE MAKELANGID(LANG_GERMAN, SUBLANG_DEFAULT)
#define LANGID_HE_IL MAKELANGID(LANG_HEBREW,SUBLANG_DEFAULT)
#define LANGID_IT_IT MAKELANGID(LANG_ITALIAN,SUBLANG_DEFAULT)
#define LANGID_ES_ES MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH)
#define LANGID_PT_BR MAKELANGID(LANG_PORTUGUESE,SUBLANG_PORTUGUESE_BRAZILIAN)
#define LANGID_PT_PT MAKELANGID(LANG_PORTUGUESE,SUBLANG_PORTUGUESE)
#define LANGID_RO_RO MAKELANGID(LANG_ROMANIAN,SUBLANG_DEFAULT)
#define LANGID_RU_RU MAKELANGID(LANG_RUSSIAN,SUBLANG_DEFAULT)
#define LANGID_SV_SE MAKELANGID(LANG_SWEDISH,SUBLANG_DEFAULT)
#define LANGID_TR_TR MAKELANGID(LANG_TURKISH,SUBLANG_DEFAULT)
#define LANGID_FR_FR MAKELANGID(LANG_FRENCH,SUBLANG_DEFAULT)


typedef struct SLanguage {
	LANGID lid;
	LPCTSTR name;
} SLanguage;


static SLanguage _langs[]={
	{LANGID_EN_US,	_T("English")},
	{LANGID_HE_IL,	_T("Hebrew")},
	{LANGID_ES_ES,	_T("Spanish")},
	{LANGID_DE_DE,	_T("german")},
	{LANGID_IT_IT,	_T("italian")},
	{LANGID_CZ_CZ,	_T("czech")},
	{LANGID_DA_DK,	_T("italian")},
	{LANGID_GL_ES,	_T("")},
	{LANGID_PT_BR,	_T("ptb")},
	{LANGID_PT_PT,	_T("ptg")},
	{LANGID_TR_TR,	_T("turkish")},
	{LANGID_RO_RO,	_T("")},
	{LANGID_RU_RU,	_T("russian")},
	{LANGID_SV_SE,	_T("swedish")},
	{LANGID_ZH_CN,	_T("chs")},
	{LANGID_ZH_TW,	_T("cht")},
	{LANGID_FR_FR,	_T("french")},
	{0, NULL}
};

CString GetResString(UINT uStringID, WORD wLangID)
{
	CString resString;
	resString.LoadString(GetModuleHandle(NULL), uStringID, wLangID);
	if (resString.IsEmpty())
		resString.LoadString(GetModuleHandle(NULL), uStringID, LANGID_EN_US);
	return resString;
}

CString GetResString(UINT uStringID)
{
	return GetResString(uStringID,theApp.GetLang());
}

CString GetLangName(LANGID lid)
{
	TCHAR szLang[128];
	GetLocaleInfo(lid, LOCALE_SLANGUAGE, szLang, ARRSIZE(szLang));
	return CString(szLang);
}

bool IsLangSupported(LANGID lid)
{
	SLanguage* pLangs = _langs;
	while (pLangs->lid) {
		if (pLangs->lid == lid)
			return true;
		pLangs++;
	}
	return false;
}

DWORD GetWndExStyle()
{
	if (theApp.GetLang() == LANGID_HE_IL)
		return (WS_EX_RTLREADING | WS_EX_RIGHT); // rtl
	return (WS_EX_LTRREADING | WS_EX_LEFT); // ltr
}

void MakeLangSelection(CComboBox& combo)
{
	combo.ResetContent();
	SLanguage* pLangs = _langs;
	while (pLangs->lid) {
		int i = combo.AddString(GetLangName(pLangs->lid));
		combo.SetItemData(i,pLangs->lid);
		if (theApp.GetLang() == pLangs->lid)
			combo.SetCurSel(i);
		pLangs++;
	}
}

