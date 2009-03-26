// SocktServerDlg.h : 头文件
//

#pragma once
#include "mysocket.h"
#include "afxcmn.h"


// CSocktServerDlg 对话框
class CSocktServerDlg : public CDialog
{
// 构造
public:
	CSocktServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SOCKTSERVER_DIALOG };

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
	//创建服务器时的监听端口
	int m_port;
	//连接到服务器时的服务器地址和端口
	int m_ServerPort; //采用数据交换
	CString m_serverIP;

	afx_msg void OnBnClickedCreatserver();

	CMySocket m_Socket;
	afx_msg void OnBnClickedConnect();
	CString m_RichText;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonSend();
	// 显示对话内容的RichEdit2控件
	CRichEditCtrl m_RichEditCtrl;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedStoplisten();
};
