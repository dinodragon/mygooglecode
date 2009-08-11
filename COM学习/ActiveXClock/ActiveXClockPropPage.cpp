// ActiveXClockPropPage.cpp : CActiveXClockPropPage 属性页类的实现。

#include "stdafx.h"
#include "ActiveXClock.h"
#include "ActiveXClockPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CActiveXClockPropPage, COlePropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(CActiveXClockPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CActiveXClockPropPage, "ACTIVEXCLOCK.ActiveXClockPropPage.1",
	0x1d7890ca, 0xcca8, 0x41c8, 0x93, 0x8c, 0xee, 0xa5, 0x61, 0x4a, 0x47, 0x81)



// CActiveXClockPropPage::CActiveXClockPropPageFactory::UpdateRegistry -
// 添加或移除 CActiveXClockPropPage 的系统注册表项

BOOL CActiveXClockPropPage::CActiveXClockPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_ACTIVEXCLOCK_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CActiveXClockPropPage::CActiveXClockPropPage - 构造函数

CActiveXClockPropPage::CActiveXClockPropPage() :
	COlePropertyPage(IDD, IDS_ACTIVEXCLOCK_PPG_CAPTION)
		, m_updateInterval(0)
	{
}



// CActiveXClockPropPage::DoDataExchange - 在页和属性间移动数据

void CActiveXClockPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
	DDX_Text(pDX, IDC_INTERVALEDIT, m_updateInterval);
}



// CActiveXClockPropPage 消息处理程序
