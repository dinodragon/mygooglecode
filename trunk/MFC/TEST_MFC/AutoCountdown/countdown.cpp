// countdown.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AutoCountdown.h"
#include "countdown.h"


// Ccountdown �Ի���

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

// Ccountdown ��Ϣ�������

void Ccountdown::OnTimer(UINT_PTR nIDEvent)
{
	if (m_count>0)
	{
		CString temp;
		temp.Format(_T("ȷ��(Y=%d)"),m_count--);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(_T("�˳���"),0,MB_YESNO|MB_ICONINFORMATION);
	OnCancel();
}

int Ccountdown::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	SetTimer(2,1000,NULL);
	return 0;
}
