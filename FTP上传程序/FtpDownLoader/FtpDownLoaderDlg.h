// FtpDownLoaderDlg.h : ͷ�ļ�
//

#pragma once


// CFtpDownLoaderDlg �Ի���
class CFtpDownLoaderDlg : public CDialog
{
// ����
public:
	CFtpDownLoaderDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FTPDOWNLOADER_DIALOG };

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
	afx_msg void OnBnClickedOk();
};
