// TEST_LISTDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CTEST_LISTDlg �Ի���
class CTEST_LISTDlg : public CDialog
{
// ����
public:
	CTEST_LISTDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TEST_LIST_DIALOG };

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
	CListCtrl m_listCtrl;
	afx_msg void OnBnClickedButton1();
	LVITEM item;
};
