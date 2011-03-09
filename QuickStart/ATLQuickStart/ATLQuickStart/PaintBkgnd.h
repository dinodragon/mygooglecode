#pragma once
#include "stdafx.h"
#include "resource.h"

//该类在收到WM_ERASEBKGND的消息时，将窗口的背景颜色绘制成蓝色
template <class T, COLORREF t_crBrushColor>
class CPaintBkgnd : public CMessageMap
{

protected:
	HBRUSH m_hbrBkgnd;

public:
	CPaintBkgnd() { m_hbrBkgnd = CreateSolidBrush(t_crBrushColor); }
	~CPaintBkgnd() { DeleteObject ( m_hbrBkgnd ); }

	BEGIN_MSG_MAP(CPaintBkgnd)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	END_MSG_MAP()

	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		HDC dc = (HDC)wParam;
		RECT rcClient;

		pT->GetClientRect(&rcClient );
		FillRect (dc,&rcClient,m_hbrBkgnd );
		return 1; // we painted the background
	}
};