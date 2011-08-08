// WTLDemoView.h : interface of the CWTLDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CWTLDemoView : public CWindowImpl<CWTLDemoView>
{
public:
	DECLARE_WND_CLASS(NULL)

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		pMsg;
		return FALSE;
	}

	BEGIN_MSG_MAP(CWTLDemoView)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CPaintDC dc(m_hWnd);
		RECT rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = 50;
		rect.bottom = 20;
		dc.DrawText(TEXT("aaaa"),-1,&rect,DT_CENTER);

		//TODO: Add your drawing code here

		return 0;
	}
};
