#include "StdAfx.h"
#include "Base64ConverterView.h"

LRESULT CBase64ConverterView::OnBnClickedDecodetofile(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here

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

	return 0;
}

LRESULT CBase64ConverterView::OnBnClickedUtf8(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here

	return 0;
}

LRESULT CBase64ConverterView::OnBnClickedUnicode(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here

	return 0;
}

LRESULT CBase64ConverterView::OnBnClickedAutoconvert(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here

	return 0;
}

LRESULT CBase64ConverterView::OnEnChangeSource(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogImpl<CBase64ConverterView>::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	return 0;
}

LRESULT CBase64ConverterView::OnEnChangeBase64(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogImpl<CBase64ConverterView>::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	return 0;
}

LRESULT CBase64ConverterView::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// TODO: Add your message handler code here and/or call default
	m_rSource = (CRichEditCtrl *)&GetDlgItem(IDC_SOURCE);
	ATLASSERT(m_rSource!=NULL);
	m_rBase64 = (CRichEditCtrl *)&GetDlgItem(IDC_BASE64);
	ATLASSERT(m_rBase64!=NULL);

	m_rSource->SetEventMask(m_rSource->GetEventMask() | ENM_CHANGE);
	m_rBase64->SetEventMask(m_rBase64->GetEventMask() | ENM_CHANGE);
	m_autoconvert = FALSE;
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

}
LRESULT CBase64ConverterView::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default

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
	return 0;
}
