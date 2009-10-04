// CallWordWithComDlg.h : 头文件
//

#pragma once
#import   "C:\Program Files\Common Files\Microsoft Shared\OFFICE12\MSO.DLL"   
#import   "C:\Program Files\Common Files\Microsoft Shared\VBA\VBA6\VBE6EXT.OLB"   
#import   "D:\Program Files\Microsoft Office\Office12\msword.olb"  rename("FindText","_FindText"), rename("ExitWindows","_ExitWindows")   
using namespace Word;

// CCallWordWithComDlg 对话框
class CCallWordWithComDlg : public CDialog
{
// 构造
public:
	CCallWordWithComDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CCallWordWithComDlg();

// 对话框数据
	enum { IDD = IDD_CALLWORDWITHCOM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	static _ApplicationPtr m_app;

	// 生成的消息映射函数
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
