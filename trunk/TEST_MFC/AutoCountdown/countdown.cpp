// countdown.cpp : 实现文件
//

#include "stdafx.h"
#include "AutoCountdown.h"
#include "countdown.h"


// Ccountdown 对话框

IMPLEMENT_DYNAMIC(Ccountdown, CDialog)

Ccountdown::Ccountdown(CWnd* pParent /*=NULL*/)
	: CDialog(Ccountdown::IDD, pParent)
	, m_count(10)
{
	SetTimer(2,1,NULL);
}

Ccountdown::~Ccountdown()
{
}

void Ccountdown::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_okbtn);
}


BEGIN_MESSAGE_MAP(Ccountdown, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &Ccountdown::OnBnClickedCancel)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// Ccountdown 消息处理程序

void Ccountdown::OnTimer(UINT_PTR nIDEvent)
{
	if (m_count>0)
	{
		CString temp;
		temp.Format(_T("确定(Y=%d)"),m_count--);
		m_okbtn.SetWindowText(temp);
	}
	else
	{
		KillTimer(2);
		OnOK();
	}
}
void Ccountdown::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("退出吗？"),0,MB_YESNO|MB_ICONINFORMATION);
	OnCancel();
}

int Ccountdown::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetTimer(2,1000,NULL);
	return 0;
}
