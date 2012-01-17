// TEST_MFCDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CTEST_MFCDlg 对话框
class CTEST_MFCDlg : public CDialog
{
// 构造
public:
	CTEST_MFCDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TEST_MFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


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
	// 列表框
	CListCtrl list;

public:
	afx_msg void OnBnClickedButton1();
public:
	afx_msg void OnBnClickedButton2();
public:
	int index;
public:
	afx_msg void OnBnClickedButton3();
public:
	afx_msg void OnBnClickedButton6();
public:
	afx_msg void OnBnClickedButton5();
public:
	afx_msg void OnBnClickedButton4();
};
