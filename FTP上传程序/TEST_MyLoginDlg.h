// TEST_MyLoginDlg.h : 头文件
//


#pragma once
#include "UpdateAHost.h"

// CTEST_MyLoginDlg 对话框
class CTEST_MyLoginDlg : public CDialog
{
// 构造
public:
	CTEST_MyLoginDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TEST_MYLOGIN_DIALOG };

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

	CUpdateAHost uphost;
public:
	afx_msg void OnBnClickedButton1();

	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedUp();
	afx_msg void OnBnClickedQuit();
};
