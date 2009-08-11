// ActiveXClockPropPage.cpp : CActiveXClockPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "ActiveXClock.h"
#include "ActiveXClockPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CActiveXClockPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CActiveXClockPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CActiveXClockPropPage, "ACTIVEXCLOCK.ActiveXClockPropPage.1",
	0x1d7890ca, 0xcca8, 0x41c8, 0x93, 0x8c, 0xee, 0xa5, 0x61, 0x4a, 0x47, 0x81)



// CActiveXClockPropPage::CActiveXClockPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CActiveXClockPropPage ��ϵͳע�����

BOOL CActiveXClockPropPage::CActiveXClockPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_ACTIVEXCLOCK_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CActiveXClockPropPage::CActiveXClockPropPage - ���캯��

CActiveXClockPropPage::CActiveXClockPropPage() :
	COlePropertyPage(IDD, IDS_ACTIVEXCLOCK_PPG_CAPTION)
		, m_updateInterval(0)
	{
}



// CActiveXClockPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CActiveXClockPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
	DDX_Text(pDX, IDC_INTERVALEDIT, m_updateInterval);
}



// CActiveXClockPropPage ��Ϣ�������
