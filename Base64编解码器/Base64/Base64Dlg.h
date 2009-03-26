// Base64Dlg.h : ͷ�ļ�
//
#include "Base64Helper.h"
#pragma once


// CBase64Dlg �Ի���
class CBase64Dlg : public CDialog
{
// ����
public:
	CBase64Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BASE64_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	// �Զ�ת��
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
	BOOL m_lastOperEncode; //���һ��ת���Ƿ�Ϊ���ܣ�����Ϊ�����л�����ʱҲ���Զ����б�����߽��롣
};
