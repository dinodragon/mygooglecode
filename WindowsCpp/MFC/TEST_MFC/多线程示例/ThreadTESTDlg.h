// ThreadTESTDlg.h : ͷ�ļ�
//
VOID add1(CString &str);
VOID add2(CString &str);

#pragma once

DWORD WINAPI Proc1(PVOID pParam);
DWORD WINAPI Proc2(PVOID pParam);


// CThreadTESTDlg �Ի���
class CThreadTESTDlg : public CDialog
{
// ����
public:
	CThreadTESTDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

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
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedButton2();
};
