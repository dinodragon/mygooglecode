// CopyDelDirDlg.h : ͷ�ļ�
//

#pragma once


BOOL DeleteDirectory(LPCTSTR sDirName);
BOOL CopyDirectory(LPCTSTR strSrcPath, LPCTSTR strDestPath);

// CCopyDelDirDlg �Ի���
class CCopyDelDirDlg : public CDialog
{
// ����
public:
	CCopyDelDirDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_COPYDELDIR_DIALOG };

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
