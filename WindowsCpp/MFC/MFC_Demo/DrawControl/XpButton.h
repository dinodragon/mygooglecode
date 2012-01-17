#pragma once


// CXpButton

class CXpButton : public CButton
{
	DECLARE_DYNAMIC(CXpButton)

public:
	CXpButton();
	virtual ~CXpButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bTracking;
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
protected:
	virtual void PreSubclassWindow();
public:
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


