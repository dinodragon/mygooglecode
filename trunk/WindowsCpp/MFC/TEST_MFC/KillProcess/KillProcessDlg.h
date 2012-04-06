// KillProcessDlg.h : ͷ�ļ�
//

#pragma once
#include "psapi.h"
#include <vector>

// CKillProcessDlg �Ի���
class CKillProcessDlg : public CDialog
{
// ����
public:
	CKillProcessDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_KILLPROCESS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	//�رս���
	BOOL CloseProcess(DWORD dwProcessId,BOOL bForce = TRUE);

	BOOL IsProcessContainModName(DWORD dwProcessId,LPCTSTR szModeName);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};