#pragma once
#include "afxwin.h"


// Ccountdown 对话框

class Ccountdown : public CDialog
{
	DECLARE_DYNAMIC(Ccountdown)

public:
	Ccountdown(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Ccountdown();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
public:
	CButton m_okbtn;
	afx_msg void OnBnClickedCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	int m_count;
};
