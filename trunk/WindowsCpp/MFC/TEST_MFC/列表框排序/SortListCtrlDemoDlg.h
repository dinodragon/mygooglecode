// SortListCtrlDemoDlg.h : header file
//

#if !defined(AFX_SORTLISTCTRLDEMODLG_H__ACA3FA07_A489_11D5_AF7C_0000E8A3A8FB__INCLUDED_)
#define AFX_SORTLISTCTRLDEMODLG_H__ACA3FA07_A489_11D5_AF7C_0000E8A3A8FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SortListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CSortListCtrlDemoDlg dialog

class CSortListCtrlDemoDlg : public CDialog
{
// Construction
public:
	CSortListCtrlDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSortListCtrlDemoDlg)
	enum { IDD = IDD_SORTLISTCTRLDEMO_DIALOG };
	CSortListCtrl	m_ctlList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSortListCtrlDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CImageList m_HeadIcon;
	// Generated message map functions
	//{{AFX_MSG(CSortListCtrlDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClickListctrl(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SORTLISTCTRLDEMODLG_H__ACA3FA07_A489_11D5_AF7C_0000E8A3A8FB__INCLUDED_)
