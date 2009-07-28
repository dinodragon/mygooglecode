// DirWatchDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CDirWatchDlg 对话框
class CDirWatchDlg : public CDialog
{
// 构造
public:
	CDirWatchDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DIRWATCH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
public:
	CEdit m_edit;
public:
	int WaitCopyFinish(const wchar_t * filePath,const DWORD dwMilliseconds);
public:
	afx_msg void OnBnClickedCancel();
};
