// hzcodeDlg.h : header file
//

#if !defined(AFX_HZCODEDLG_H__1405320F_2ED8_4BCD_9E64_88F19DDDFFDE__INCLUDED_)
#define AFX_HZCODEDLG_H__1405320F_2ED8_4BCD_9E64_88F19DDDFFDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHzcodeDlg dialog

class CHzcodeDlg : public CDialog
{
// Construction
public:
	CHzcodeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHzcodeDlg)
	enum { IDD = IDD_HZCODE_DIALOG };
	CString	m_input;
	CString	m_output;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHzcodeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHzcodeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeEdit1();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HZCODEDLG_H__1405320F_2ED8_4BCD_9E64_88F19DDDFFDE__INCLUDED_)
