// ReplayClientDlg.h : ͷ�ļ�
//
#include "MySocket.h"
#pragma once


// CReplayClientDlg �Ի���
class CReplayClientDlg : public CDialog
{
// ����
public:
	CReplayClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_REPLAYCLIENT_DIALOG };

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

	CMySocket m_mySocket;
public:
	afx_msg void OnBnClickedSend();
};
