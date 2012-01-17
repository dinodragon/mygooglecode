// ReplayServerDlg.h : 头文件
//
#include "MySocket.h"
#pragma once


// CReplayServerDlg 对话框
class CReplayServerDlg : public CDialog
{
// 构造
public:
	CReplayServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_REPLAYSERVER_DIALOG };

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
	afx_msg void OnBnClickedCrate();

	CMySocket m_mySocket;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void AddMessage(CString str);
	afx_msg void OnBnClickedStop();
};
