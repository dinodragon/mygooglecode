// ReplayServerDlg.h : ͷ�ļ�
//
#include "MySocket.h"
#pragma once


// CReplayServerDlg �Ի���
class CReplayServerDlg : public CDialog
{
// ����
public:
	CReplayServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_REPLAYSERVER_DIALOG };

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
	afx_msg void OnBnClickedCrate();

	CMySocket m_mySocket;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void AddMessage(CString str);
	afx_msg void OnBnClickedStop();
};
