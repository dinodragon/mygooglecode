// Base64ConverterView.h : interface of the CCodeConverterView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "resource.h"
#include "atlctrls.h"
#include "Base64Helper.h"
#include <atlstr.h>
#include <atlddx.h>
#include <atlmisc.h>


class CBase64ConverterView : public CDialogImpl<CBase64ConverterView>
	,public CWinDataExchange<CBase64ConverterView>
{
public:
	enum { IDD = IDD_BASE64CONVERTER_FORM };

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		return CWindow::IsDialogMessage(pMsg);
	}
	
	CBase64ConverterView()
	{
		m_codepage = 0;
	}

	BEGIN_MSG_MAP(CBase64ConverterView)
		COMMAND_HANDLER(IDC_DECODETOFILE, BN_CLICKED, OnBnClickedDecodetofile)
		COMMAND_HANDLER(IDC_ENCODE, BN_CLICKED, OnBnClickedEncode)
		COMMAND_HANDLER(IDC_DECODE, BN_CLICKED, OnBnClickedDecode)
		COMMAND_HANDLER(IDC_ANSI, BN_CLICKED, OnBnClickedAnsi)
		COMMAND_HANDLER(IDC_UTF8, BN_CLICKED, OnBnClickedUtf8)
		COMMAND_HANDLER(IDC_Unicode, BN_CLICKED, OnBnClickedUnicode)
		COMMAND_HANDLER(IDC_AUTOCONVERT, BN_CLICKED, OnBnClickedAutoconvert)
		COMMAND_HANDLER(IDC_SOURCE, EN_CHANGE, OnEnChangeSource)
		COMMAND_HANDLER(IDC_BASE64, EN_CHANGE, OnEnChangeBase64)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
	END_MSG_MAP()

	BEGIN_DDX_MAP(CMainDlg)
		DDX_RADIO(IDC_ANSI, m_codepage)
	END_DDX_MAP()

	// Handler prototypes (uncomment arguments if needed):
	//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
	LRESULT OnBnClickedDecodetofile(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedEncode(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedDecode(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedAnsi(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedUtf8(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedUnicode(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedAutoconvert(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnEnChangeSource(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnEnChangeBase64(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	void Encode(void);
	void Decode(void);
private:
	CRichEditCtrl * m_rSource;
	CRichEditCtrl * m_rBase64;
	BOOL m_autoconvert;
	BOOL m_lastOperEncode; //最后一次转换是否为加密，这是为了在切换编码时也可自动进行编码或者解码。
	MUtils::Base64Helper base64;
	CAtlString m_source;
	CAtlString m_base64;
	int m_codepage;
public:
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};
