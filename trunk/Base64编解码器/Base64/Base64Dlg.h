// Base64Dlg.h : 头文件
//
#include "Base64Helper.h"
#pragma once


// CBase64Dlg 对话框
class CBase64Dlg : public CDialog
{
// 构造
public:
	CBase64Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BASE64_DIALOG };

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
	MUtils::Base64Helper base64;
	CString m_source;
	CString m_base64;
	afx_msg void OnEnChangeSource();
	afx_msg void OnEnChangeBase64();
	afx_msg void OnBnClickedHelp();
public:
	afx_msg void OnBnClickedAutoconvert();
public:
	// 自动转换
	BOOL m_autoconvert;
public:
	void Encode(void);
	void Decode(void);
	afx_msg void OnBnClickedEncode();
	afx_msg void OnBnClickedDecode();
public:
	int m_codepage;
public:
	afx_msg void OnBnClickedAnsi();
public:
	afx_msg void OnBnClickedUtf8();
public:
	afx_msg void OnBnClickedUnicode();
public:
	afx_msg void OnClose();
	BOOL m_lastOperEncode; //最后一次转换是否为加密，这是为了在切换编码时也可自动进行编码或者解码。
};
