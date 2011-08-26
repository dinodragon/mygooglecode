#pragma once


// CListCtrlWithCustomDraw

class CListCtrlWithCustomDraw : public CListCtrl
{
	DECLARE_DYNAMIC(CListCtrlWithCustomDraw)

public:
	CListCtrlWithCustomDraw();
	virtual ~CListCtrlWithCustomDraw();

protected:
	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
};


