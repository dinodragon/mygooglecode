// adslDlg.h : ͷ�ļ�
//

#pragma once


// CadslDlg �Ի���
class CadslDlg : public CDialog
{
// ����
public:
	CadslDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ADSL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
public:
	afx_msg void OnBnClickedButton2();
public:
	afx_msg void OnBnClickedButton3();
};
