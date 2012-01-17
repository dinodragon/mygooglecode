// ThreadTESTDlg.h : 头文件
//
VOID add1(CString &str);
VOID add2(CString &str);

#pragma once

DWORD WINAPI Proc1(PVOID pParam);
DWORD WINAPI Proc2(PVOID pParam);


// CThreadTESTDlg 对话框
class CThreadTESTDlg : public CDialog
{
// 构造
public:
	CThreadTESTDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

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
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedButton2();
};
