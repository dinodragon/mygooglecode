// TEST_MFCDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CTEST_MFCDlg �Ի���
class CTEST_MFCDlg : public CDialog
{
// ����
public:
	CTEST_MFCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TEST_MFC_DIALOG };

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
	// �б��
	CListCtrl list;

public:
	afx_msg void OnBnClickedButton1();
public:
	afx_msg void OnBnClickedButton2();
public:
	int index;
public:
	afx_msg void OnBnClickedButton3();
public:
	afx_msg void OnBnClickedButton6();
public:
	afx_msg void OnBnClickedButton5();
public:
	afx_msg void OnBnClickedButton4();
};
