// TEST_MyLoginDlg.h : ͷ�ļ�
//


#pragma once
#include "UpdateAHost.h"

// CTEST_MyLoginDlg �Ի���
class CTEST_MyLoginDlg : public CDialog
{
// ����
public:
	CTEST_MyLoginDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TEST_MYLOGIN_DIALOG };

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

	CUpdateAHost uphost;
public:
	afx_msg void OnBnClickedButton1();

	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedUp();
	afx_msg void OnBnClickedQuit();
};
