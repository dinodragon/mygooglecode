#pragma once
#include "afxwin.h"


// Ccountdown �Ի���

class Ccountdown : public CDialog
{
	DECLARE_DYNAMIC(Ccountdown)

public:
	Ccountdown(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Ccountdown();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
public:
	CButton m_okbtn;
	afx_msg void OnBnClickedCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	int m_count;
};
