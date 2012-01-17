// XpButton.cpp : implementation file
//

#include "stdafx.h"
#include "DrawControl.h"
#include "XpButton.h"


// CXpButton

IMPLEMENT_DYNAMIC(CXpButton, CButton)

CXpButton::CXpButton()
{

}

CXpButton::~CXpButton()
{
}


BEGIN_MESSAGE_MAP(CXpButton, CButton)
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CXpButton message handlers



void CXpButton::DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/)
{

	// TODO:  Add your code to draw the specified item
}

void CXpButton::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0,BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}

void CXpButton::OnMouseLeave()
{
	// TODO: Add your message handler code here and/or call default

	CButton::OnMouseLeave();
}

void CXpButton::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CButton::OnMouseHover(nFlags, point);
}

void CXpButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 1;
		m_bTracking = _TrackMouseEvent(&tme);
	}
	CButton::OnMouseMove(nFlags, point);
}
