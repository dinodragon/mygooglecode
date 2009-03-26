// ReplayClientDlg.h : 头文件
//
#include "MySocket.h"
#pragma once


// CReplayClientDlg 对话框
class CReplayClientDlg : public CDialog
{
// 构造
public:
	CReplayClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_REPLAYCLIENT_DIALOG };

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

	CMySocket m_mySocket;
public:
	afx_msg void OnBnClickedSend();
};
