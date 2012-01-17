// ActiveXClockCtrl.cpp : CActiveXClockCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "ActiveXClock.h"
#include "ActiveXClockCtrl.h"
#include "ActiveXClockPropPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CActiveXClockCtrl, COleControl)



// 消息映射

BEGIN_MESSAGE_MAP(CActiveXClockCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// 调度映射

BEGIN_DISPATCH_MAP(CActiveXClockCtrl, COleControl)
	DISP_FUNCTION_ID(CActiveXClockCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_STOCKPROP_BACKCOLOR()
	DISP_STOCKPROP_FORECOLOR()
	DISP_PROPERTY_NOTIFY_ID(CActiveXClockCtrl, "Interval", dispidInterval, m_Interval, OnIntervalChanged, VT_I2)
	DISP_FUNCTION_ID(CActiveXClockCtrl, "Hello", dispidHello, Hello, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()



// 事件映射

BEGIN_EVENT_MAP(CActiveXClockCtrl, COleControl)
END_EVENT_MAP()



// 属性页

// TODO: 按需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CActiveXClockCtrl, 2)
	PROPPAGEID(CActiveXClockPropPage::guid)
	PROPPAGEID(CLSID_CColorPropPage)
END_PROPPAGEIDS(CActiveXClockCtrl)



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CActiveXClockCtrl, "ACTIVEXCLOCK.ActiveXClockCtrl.1",
	0x797ccf2a, 0xe994, 0x4eae, 0xb2, 0x40, 0xeb, 0xdf, 0x36, 0x77, 0xa4, 0x69)



// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CActiveXClockCtrl, _tlid, _wVerMajor, _wVerMinor)



// 接口 ID

const IID BASED_CODE IID_DActiveXClock =
		{ 0x4B8D1E02, 0xDDBC, 0x439A, { 0xA9, 0x28, 0x4, 0x4D, 0x8, 0xF5, 0x8, 0xEE } };
const IID BASED_CODE IID_DActiveXClockEvents =
		{ 0xAA689136, 0x3C6, 0x421A, { 0x94, 0x21, 0xE6, 0x2A, 0xC4, 0xAF, 0xC2, 0xC7 } };



// 控件类型信息

static const DWORD BASED_CODE _dwActiveXClockOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CActiveXClockCtrl, IDS_ACTIVEXCLOCK, _dwActiveXClockOleMisc)



// CActiveXClockCtrl::CActiveXClockCtrlFactory::UpdateRegistry -
// 添加或移除 CActiveXClockCtrl 的系统注册表项

BOOL CActiveXClockCtrl::CActiveXClockCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: 验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_ACTIVEXCLOCK,
			IDB_ACTIVEXCLOCK,
			afxRegApartmentThreading,
			_dwActiveXClockOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CActiveXClockCtrl::CActiveXClockCtrl - 构造函数

CActiveXClockCtrl::CActiveXClockCtrl()
{
	InitializeIIDs(&IID_DActiveXClock, &IID_DActiveXClockEvents);
	// TODO: 在此初始化控件的实例数据。
}



// CActiveXClockCtrl::~CActiveXClockCtrl - 析构函数

CActiveXClockCtrl::~CActiveXClockCtrl()
{
	// TODO: 在此清理控件的实例数据。
}



// CActiveXClockCtrl::OnDraw - 绘图函数

void CActiveXClockCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: 用您自己的绘图代码替换下面的代码。
	CBrush brush(TranslateColor(GetBackColor()));
	pdc->FillRect(rcBounds,&brush);
	pdc->SetTextColor(TranslateColor(GetForeColor()));
	CTime time = CTime::GetCurrentTime();
	pdc->TextOut(0,0,time.Format("%H:%M:%S"));
}



// CActiveXClockCtrl::DoPropExchange - 持久性支持

void CActiveXClockCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}



// CActiveXClockCtrl::OnResetState - 将控件重置为默认状态

void CActiveXClockCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO: 在此重置任意其他控件状态。
}



// CActiveXClockCtrl::AboutBox - 向用户显示“关于”框

void CActiveXClockCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_ACTIVEXCLOCK);
	dlgAbout.DoModal();
}



// CActiveXClockCtrl 消息处理程序

int CActiveXClockCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetTimer(1,1000,NULL);

	return 0;
}

void CActiveXClockCtrl::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//Invalidate();
	InvalidateControl();//强制控件重绘自身
	COleControl::OnTimer(nIDEvent);
}

void CActiveXClockCtrl::OnIntervalChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	if(m_Interval < 0 || m_Interval>6000)
		m_Interval = 1000;
	else
	{	
		KillTimer(1);
		SetTimer(1,m_Interval,NULL);
	}
	SetModifiedFlag();
}

void CActiveXClockCtrl::Hello(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	MessageBox(TEXT("Hello World!"));
}
