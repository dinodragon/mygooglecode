// TEST_dialogDlg.h : 头文件
//


#pragma once
#include "afxcmn.h"
#include "afxwin.h"

DWORD WINAPI Proc1(PVOID pParam);
DWORD WINAPI Proc2(PVOID pParam);



// CTEST_dialogDlg 对话框
class CTEST_dialogDlg : public CDialog
{
// 构造
public:
	CTEST_dialogDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TEST_DIALOG_DIALOG };

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
	int value;
	afx_msg void OnBnClickedYes();
	afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl list;
	CTreeCtrl tree;
	afx_msg void OnBnClickedButton1();
	BOOL boolv;
	CButton ccheck;
};
