// CallWordWithComDlg.h : ͷ�ļ�
//

#pragma once
#import   "C:\Program Files\Common Files\Microsoft Shared\OFFICE12\MSO.DLL"   
#import   "C:\Program Files\Common Files\Microsoft Shared\VBA\VBA6\VBE6EXT.OLB"   
#import   "D:\Program Files\Microsoft Office\Office12\msword.olb"  rename("FindText","_FindText"), rename("ExitWindows","_ExitWindows")   
using namespace Word;

// CCallWordWithComDlg �Ի���
class CCallWordWithComDlg : public CDialog
{
// ����
public:
	CCallWordWithComDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CCallWordWithComDlg();

// �Ի�������
	enum { IDD = IDD_CALLWORDWITHCOM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	static _ApplicationPtr m_app;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	static DWORD WINAPI Proc1(PVOID pParam);
	afx_msg void OnBnClickedCancel();
};
