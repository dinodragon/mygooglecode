// SocktServerDlg.h : ͷ�ļ�
//

#pragma once
#include "mysocket.h"
#include "afxcmn.h"


// CSocktServerDlg �Ի���
class CSocktServerDlg : public CDialog
{
// ����
public:
	CSocktServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SOCKTSERVER_DIALOG };

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
	//����������ʱ�ļ����˿�
	int m_port;
	//���ӵ�������ʱ�ķ�������ַ�Ͷ˿�
	int m_ServerPort; //�������ݽ���
	CString m_serverIP;

	afx_msg void OnBnClickedCreatserver();

	CMySocket m_Socket;
	afx_msg void OnBnClickedConnect();
	CString m_RichText;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonSend();
	// ��ʾ�Ի����ݵ�RichEdit2�ؼ�
	CRichEditCtrl m_RichEditCtrl;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedStoplisten();
};
