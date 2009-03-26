// ToolsDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"


// CToolsDlg �Ի���
class CToolsDlg : public CDialog
{
// ����
public:
	CToolsDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TOOLS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	HICON m_imgIcon[3];
	CImageList m_imgList;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
