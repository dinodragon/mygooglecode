// userDDVDlg.h : ͷ�ļ�
//

#pragma once


// CuserDDVDlg �Ի���
class CuserDDVDlg : public CDialog
{
// ����
public:
	CuserDDVDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_USERDDV_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	void CuserDDVDlg::DDV_USER(CDataExchange* pDX, CString const& value);

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
	CString m_value;
	afx_msg void OnBnClickedOk();
};
