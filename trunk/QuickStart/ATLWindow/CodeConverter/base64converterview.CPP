#include "StdAfx.h"
#include "Base64ConverterView.h"
#include "atldlgs.h"

LRESULT CBase64ConverterView::OnBnClickedDecodetofile(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_BASE64,m_base64);
	TCHAR szFilters[]= _T("All Files (*.*)|*.*|");
	CAtlString pathName;
	CFileDialog fileDlg(FALSE,_T("txt"),NULL,OFN_HIDEREADONLY,szFilters);
	fileDlg.m_ofn.lpstrFile = pathName.GetBuffer(MAX_PATH);
	if(fileDlg.DoModal()==IDOK )
	{
		const TCHAR * base64Wide = m_base64.GetBuffer(m_base64.GetLength());
		DWORD dwMultiNum = WideCharToMultiByte (CP_ACP, 0, base64Wide, -1, NULL, 0,NULL,NULL);
		char * base64Ansi = new char[dwMultiNum];
		WideCharToMultiByte(CP_ACP,0,base64Wide,-1,base64Ansi,dwMultiNum,NULL,NULL);
		std::vector<char> sourceChars = base64.decode(std::string(base64Ansi));
		size_t sourceLen = sourceChars.size();
		char * sourceByte = new char[sourceLen];
		for (size_t i = 0;i<sourceLen ;i++ )
		{
			sourceByte[i] = sourceChars[i];
		}
		pathName.ReleaseBufferSetLength(MAX_PATH);
		DWORD writeNumber = 0;
		HANDLE hFile = CreateFile(pathName,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		WriteFile(hFile,sourceByte,sourceLen,&writeNumber,NULL);
		CloseHandle(hFile);
		delete[] sourceByte;
	}
	pathName.ReleaseBufferSetLength(MAX_PATH);
	return 0;
}

LRESULT CBase64ConverterView::OnBnClickedEncode(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here
	Encode();
	return 0;
}

LRESULT CBase64ConverterView::OnBnClickedDecode(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here
	Decode();
	return 0;
}

LRESULT CBase64ConverterView::OnBnClickedAnsi(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here
	m_codepage = 0;
	if (m_lastOperEncode)
		Encode();
	else
		Decode();
	return 0;
}

LRESULT CBase64ConverterView::OnBnClickedUtf8(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here
	m_codepage = 1;
	if (m_lastOperEncode)
		Encode();
	else
		Decode();
	return 0;
}

LRESULT CBase64ConverterView::OnBnClickedUnicode(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here
	m_codepage = 2;
	if (m_lastOperEncode)
		Encode();
	else
		Decode();
	return 0;
}

LRESULT CBase64ConverterView::OnBnClickedAutoconvert(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here
	DoDataExchange(TRUE);
	CButton * decode = (CButton *)&GetDlgItem(IDC_DECODE);
	ATLASSERT(decode!=NULL);
	decode->EnableWindow(!m_autoconvert);
	CButton * encode = (CButton *)&GetDlgItem(IDC_ENCODE);
	ATLASSERT(encode!=NULL);
	encode->EnableWindow(!m_autoconvert);
	return 0;
}

LRESULT CBase64ConverterView::OnEnChangeSource(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogImpl<CBase64ConverterView>::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	if (m_autoconvert)
	{
		Encode();
	}
	return 0;
}

LRESULT CBase64ConverterView::OnEnChangeBase64(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogImpl<CBase64ConverterView>::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	if (m_autoconvert)
	{
		Decode();
	}
	return 0;
}

LRESULT CBase64ConverterView::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// TODO: Add your message handler code here and/or call default
	LoadRegConfig();
	m_rSource = (CRichEditCtrl *)&GetDlgItem(IDC_SOURCE);
	ATLASSERT(m_rSource!=NULL);
	m_rBase64 = (CRichEditCtrl *)&GetDlgItem(IDC_BASE64);
	ATLASSERT(m_rBase64!=NULL);

	m_rSource->SetEventMask(m_rSource->GetEventMask() | ENM_CHANGE);
	m_rBase64->SetEventMask(m_rBase64->GetEventMask() | ENM_CHANGE);
	CButton * decode = (CButton *)&GetDlgItem(IDC_DECODE);
	ATLASSERT(decode!=NULL);
	decode->EnableWindow(!m_autoconvert);
	CButton * encode = (CButton *)&GetDlgItem(IDC_ENCODE);
	ATLASSERT(encode!=NULL);
	encode->EnableWindow(!m_autoconvert);

	HKEY hKey;
	DWORD dw;
	RegCreateKeyEx(HKEY_CURRENT_USER,TEXT("Software\\base64"),0,NULL,REG_OPTION_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&dw);
	DWORD dwType;
	DWORD dwSize=sizeof(DWORD);
	DWORD dwAutoConvert;
	DWORD dwCodePage;
	long lReturn=RegQueryValueEx(hKey,TEXT("AutoConvert"),NULL,&dwType,(BYTE *)&dwAutoConvert,&dwSize);
	if (lReturn == ERROR_SUCCESS)
	{
		m_autoconvert = (BOOL)dwAutoConvert;
	}
	lReturn=RegQueryValueEx(hKey,TEXT("CodePage"),NULL,&dwType,(BYTE *)&dwCodePage,&dwSize);
	if (lReturn == ERROR_SUCCESS)
	{
		m_codepage = (int)dwCodePage;
		if (m_codepage<0 || m_codepage >2)
		{
			m_codepage = 0;
		}
	}
	DoDataExchange();
	return FALSE;
}

//Ã÷Âë×ªÎªBase64
void CBase64ConverterView::Encode( void )
{
	m_rSource = (CRichEditCtrl *)&GetDlgItem(IDC_SOURCE);
	ATLASSERT(m_rSource!=NULL);
	m_rBase64 = (CRichEditCtrl *)&GetDlgItem(IDC_BASE64);
	ATLASSERT(m_rBase64!=NULL);

	GetDlgItemText(IDC_SOURCE,m_source);
	m_lastOperEncode = TRUE;
	const TCHAR * sourceWide = m_source.GetBuffer(m_source.GetLength());
	DWORD dwMultiNum = WideCharToMultiByte (CP_ACP, 0, sourceWide, -1, NULL, 0,NULL,NULL);
	char * sourceAnsi = new char[dwMultiNum];
	WideCharToMultiByte(CP_ACP,0,sourceWide,-1,sourceAnsi,dwMultiNum,NULL,NULL);
	if (m_codepage == 0) //ANSI
	{
		m_base64 = CAtlString(base64.encode(sourceAnsi,strlen(sourceAnsi)).c_str());
	} 
	else if(m_codepage == 1) //UTF-8
	{
		DWORD dwUnicodeNum = MultiByteToWideChar (CP_ACP, 0, sourceAnsi, -1, NULL, 0);
		WCHAR * sourceUnich = new WCHAR[dwUnicodeNum];
		MultiByteToWideChar (CP_ACP, 0, sourceAnsi, -1, sourceUnich, dwUnicodeNum);

		DWORD dwUTF8Num = WideCharToMultiByte (CP_UTF8, 0, sourceUnich, -1, NULL, 0,NULL,NULL);
		CHAR * souceUTF8Char = new CHAR[dwUTF8Num];
		WideCharToMultiByte (CP_UTF8, 0, sourceUnich, -1, souceUTF8Char, dwUTF8Num,NULL,NULL);

		m_base64 = CAtlString(base64.encode(souceUTF8Char,strlen(souceUTF8Char)).c_str());
		delete[] sourceUnich;
		delete[] souceUTF8Char;
	}
	else if (m_codepage == 2) //Unicode
	{
		DWORD dwUnicodeNum = MultiByteToWideChar (CP_ACP, 0, sourceAnsi, -1, NULL, 0);
		WCHAR * sourceUnich = new WCHAR[dwUnicodeNum];
		MultiByteToWideChar (CP_ACP, 0, sourceAnsi, -1, sourceUnich, dwUnicodeNum);
		CHAR * sourceWchToChar = new CHAR[dwUnicodeNum<<1];
		for (DWORD i = 0 ;i<dwUnicodeNum;i++)
		{
			sourceWchToChar[i<<1] = (sourceUnich[i] >>8 );
			sourceWchToChar[(i<<1) + 1] = sourceUnich[i] & 0x00FF;
		}
		m_base64 = CAtlString(base64.encode(sourceWchToChar,(dwUnicodeNum-1)<<1).c_str());
		delete[] sourceUnich;
		delete[] sourceWchToChar;
	}
	m_source.ReleaseBuffer();

	m_rBase64->SetEventMask(m_rBase64->GetEventMask() ^ ENM_CHANGE);
	SetDlgItemText(IDC_BASE64,m_base64.GetBuffer(m_base64.GetLength()));
	m_rBase64->SetEventMask(m_rBase64->GetEventMask() | ENM_CHANGE);
	m_base64.ReleaseBuffer();
}

void CBase64ConverterView::Decode( void )
{
	m_rSource = (CRichEditCtrl *)&GetDlgItem(IDC_SOURCE);
	ATLASSERT(m_rSource!=NULL);
	m_rBase64 = (CRichEditCtrl *)&GetDlgItem(IDC_BASE64);
	ATLASSERT(m_rBase64!=NULL);
	GetDlgItemText(IDC_BASE64,m_base64);
	m_lastOperEncode = FALSE;
	
	const TCHAR * base64Wide = m_base64.GetBuffer(m_base64.GetLength());
	DWORD dwMultiNum = WideCharToMultiByte (CP_ACP, 0, base64Wide, -1, NULL, 0,NULL,NULL);
	char * base64Ansi = new char[dwMultiNum];
	WideCharToMultiByte(CP_ACP,0,base64Wide,-1,base64Ansi,dwMultiNum,NULL,NULL);

	std::vector<char> sourceChars = base64.decode(std::string(base64Ansi));

	size_t sourceLen = sourceChars.size();
	char * sourceByte = new char[sourceLen+1];
	for (size_t i = 0;i<sourceLen ;i++ )
	{
		sourceByte[i] = sourceChars[i];
	}
	sourceByte[sourceLen] = 0;
	if (m_codepage == 0) //ANSI
	{
		m_source = CAtlString(sourceByte);
	} 
	else if(m_codepage == 1) //UTF-8
	{
		DWORD dwUnicodeNum = MultiByteToWideChar (CP_UTF8, 0, sourceByte, -1, NULL, 0);
		WCHAR * sourceUnich = new WCHAR[dwUnicodeNum];
		MultiByteToWideChar (CP_UTF8, 0, sourceByte, -1, sourceUnich, dwUnicodeNum);

		DWORD dwANSICharNum = WideCharToMultiByte (CP_ACP, 0, sourceUnich, -1, NULL, 0,NULL,NULL);
		CHAR * souceANSIChar = new CHAR[dwANSICharNum];
		WideCharToMultiByte (CP_ACP, 0, sourceUnich, -1, souceANSIChar, dwANSICharNum,NULL,NULL);

		m_source = CAtlString(souceANSIChar);
		delete[] sourceUnich;
		delete[] souceANSIChar;
	}
	else if (m_codepage == 2) //Unicode
	{
		WCHAR * WideChar = new WCHAR[sourceLen/2 + 1];
		for (DWORD i = 0 ;i<sourceLen/2;i++)
		{
			WideChar[i] = ((sourceByte[i<<1])<<8) | (sourceByte[(i<<1) + 1]&0x00FF) ;
		}
		WideChar[sourceLen/2] = 0;

		DWORD dwANSICharNum = WideCharToMultiByte (CP_ACP, 0, WideChar, -1, NULL, 0,NULL,NULL);
		CHAR * souceANSIChar = new CHAR[dwANSICharNum];
		WideCharToMultiByte (CP_ACP, 0, WideChar, -1, souceANSIChar, dwANSICharNum,NULL,NULL);

		m_source = CAtlString(souceANSIChar);
		delete[] WideChar;
		delete[] souceANSIChar;
	}
	delete[] sourceByte;
	m_rSource->SetEventMask(m_rSource->GetEventMask() ^ ENM_CHANGE);
	SetDlgItemText(IDC_SOURCE,m_source.GetBuffer());
	m_source.ReleaseBuffer();
	m_rSource->SetEventMask(m_rSource->GetEventMask() | ENM_CHANGE);

}

BOOL CBase64ConverterView::LoadRegConfig()
{
	HKEY hKey;
	DWORD dw;
	RegCreateKeyEx(HKEY_CURRENT_USER,TEXT("Software\\base64"),0,NULL,REG_OPTION_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&dw);
	DWORD dwType;
	DWORD dwSize=sizeof(DWORD);
	DWORD dwAutoConvert;
	DWORD dwCodePage;
	long lReturn=RegQueryValueEx(hKey,TEXT("AutoConvert"),NULL,&dwType,(BYTE *)&dwAutoConvert,&dwSize);
	if (lReturn == ERROR_SUCCESS)
	{
		m_autoconvert = (BOOL)dwAutoConvert;
	}
	lReturn=RegQueryValueEx(hKey,TEXT("CodePage"),NULL,&dwType,(BYTE *)&dwCodePage,&dwSize);
	if (lReturn == ERROR_SUCCESS)
	{
		m_codepage = (int)dwCodePage;
		if (m_codepage<0 || m_codepage >2)
		{
			m_codepage = 0;
		}
	}
	return TRUE;
}

BOOL CBase64ConverterView::WriteRegConfig()
{
	// TODO: Add your message handler code here and/or call default
	HKEY hKey;
	DWORD dw;
	RegCreateKeyEx(HKEY_CURRENT_USER,TEXT("Software\\base64"),0,NULL,REG_OPTION_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&dw);
	long lReturn=RegSetValueEx(hKey,TEXT("AutoConvert"),0L,REG_DWORD,(const BYTE *) &m_autoconvert,sizeof(DWORD));
	RegSetValueEx(hKey,TEXT("CodePage"),0L,REG_DWORD,(const BYTE *) &m_codepage,sizeof(DWORD));
	return TRUE;
}
LRESULT CBase64ConverterView::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	WriteRegConfig();
	return 0;
}

LRESULT CBase64ConverterView::OnBnClickedHelp(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here
	ShellExecute(NULL,TEXT("open"),TEXT("http://www.yangfei.org/post/base64.html?from=base64v1.6"),NULL,NULL,SW_SHOWNORMAL);
	return 0;
}
