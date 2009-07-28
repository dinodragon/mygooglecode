// DirWatchDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CDirWatchDlg �Ի���
class CDirWatchDlg : public CDialog
{
// ����
public:
	CDirWatchDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DIRWATCH_DIALOG };

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
public:
	CEdit m_edit;
public:
	int WaitCopyFinish(const wchar_t * filePath,const DWORD dwMilliseconds);
public:
	afx_msg void OnBnClickedCancel();
};
