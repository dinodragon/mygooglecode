// TEST_dialogDlg.h : ͷ�ļ�
//


#pragma once
#include "afxcmn.h"
#include "afxwin.h"

DWORD WINAPI Proc1(PVOID pParam);
DWORD WINAPI Proc2(PVOID pParam);



// CTEST_dialogDlg �Ի���
class CTEST_dialogDlg : public CDialog
{
// ����
public:
	CTEST_dialogDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TEST_DIALOG_DIALOG };

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
	int value;
	afx_msg void OnBnClickedYes();
	afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl list;
	CTreeCtrl tree;
	afx_msg void OnBnClickedButton1();
	BOOL boolv;
	CButton ccheck;
};
