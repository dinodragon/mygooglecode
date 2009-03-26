// ToolsDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"


// CToolsDlg 对话框
class CToolsDlg : public CDialog
{
// 构造
public:
	CToolsDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TOOLS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	HICON m_imgIcon[3];
	CImageList m_imgList;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strEdit;
public:
	afx_msg void OnBnClickedButton1();
public:
	afx_msg void OnBnClickedButton2();
public:
	afx_msg void OnBnClickedCheck1();
public:
	BOOL m_bInput;
public:
	CButton m_btInput;
public:
	afx_msg void OnBnClickedRadio1();
public:
	afx_msg void OnBnClickedRadio2();
public:
	CListCtrl m_list;
public:
	afx_msg void OnHdnItemclickList2(NMHDR *pNMHDR, LRESULT *pResult);
public:
	CComboBoxEx m_combo;
public:
	CString m_strEdit2;
public:
	CSliderCtrl m_slider;
public:
	afx_msg void OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
public:
	CProgressCtrl m_prograss;
public:
	afx_msg void OnBnClickedButton3();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnBnClickedButton4();
public:
	CMonthCalCtrl m_month;
public:
	afx_msg void OnBnClickedButton5();
public:
	afx_msg void OnMcnSelchangeMonthcalendar1(NMHDR *pNMHDR, LRESULT *pResult);
public:
	CListBox m_list0;
};
