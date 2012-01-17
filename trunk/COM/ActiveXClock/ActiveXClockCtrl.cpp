// ActiveXClockCtrl.cpp : CActiveXClockCtrl ActiveX �ؼ����ʵ�֡�

#include "stdafx.h"
#include "ActiveXClock.h"
#include "ActiveXClockCtrl.h"
#include "ActiveXClockPropPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CActiveXClockCtrl, COleControl)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CActiveXClockCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// ����ӳ��

BEGIN_DISPATCH_MAP(CActiveXClockCtrl, COleControl)
	DISP_FUNCTION_ID(CActiveXClockCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_STOCKPROP_BACKCOLOR()
	DISP_STOCKPROP_FORECOLOR()
	DISP_PROPERTY_NOTIFY_ID(CActiveXClockCtrl, "Interval", dispidInterval, m_Interval, OnIntervalChanged, VT_I2)
	DISP_FUNCTION_ID(CActiveXClockCtrl, "Hello", dispidHello, Hello, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()



// �¼�ӳ��

BEGIN_EVENT_MAP(CActiveXClockCtrl, COleControl)
END_EVENT_MAP()



// ����ҳ

// TODO: ����Ҫ��Ӹ�������ҳ�����ס���Ӽ���!
BEGIN_PROPPAGEIDS(CActiveXClockCtrl, 2)
	PROPPAGEID(CActiveXClockPropPage::guid)
	PROPPAGEID(CLSID_CColorPropPage)
END_PROPPAGEIDS(CActiveXClockCtrl)



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CActiveXClockCtrl, "ACTIVEXCLOCK.ActiveXClockCtrl.1",
	0x797ccf2a, 0xe994, 0x4eae, 0xb2, 0x40, 0xeb, 0xdf, 0x36, 0x77, 0xa4, 0x69)



// ����� ID �Ͱ汾

IMPLEMENT_OLETYPELIB(CActiveXClockCtrl, _tlid, _wVerMajor, _wVerMinor)



// �ӿ� ID

const IID BASED_CODE IID_DActiveXClock =
		{ 0x4B8D1E02, 0xDDBC, 0x439A, { 0xA9, 0x28, 0x4, 0x4D, 0x8, 0xF5, 0x8, 0xEE } };
const IID BASED_CODE IID_DActiveXClockEvents =
		{ 0xAA689136, 0x3C6, 0x421A, { 0x94, 0x21, 0xE6, 0x2A, 0xC4, 0xAF, 0xC2, 0xC7 } };



// �ؼ�������Ϣ

static const DWORD BASED_CODE _dwActiveXClockOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CActiveXClockCtrl, IDS_ACTIVEXCLOCK, _dwActiveXClockOleMisc)



// CActiveXClockCtrl::CActiveXClockCtrlFactory::UpdateRegistry -
// ��ӻ��Ƴ� CActiveXClockCtrl ��ϵͳע�����

BOOL CActiveXClockCtrl::CActiveXClockCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: ��֤���Ŀؼ��Ƿ���ϵ�Ԫģ���̴߳������
	// �йظ�����Ϣ����ο� MFC ����˵�� 64��
	// ������Ŀؼ������ϵ�Ԫģ�͹�����
	// �����޸����´��룬��������������
	// afxRegApartmentThreading ��Ϊ 0��

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



// CActiveXClockCtrl::CActiveXClockCtrl - ���캯��

CActiveXClockCtrl::CActiveXClockCtrl()
{
	InitializeIIDs(&IID_DActiveXClock, &IID_DActiveXClockEvents);
	// TODO: �ڴ˳�ʼ���ؼ���ʵ�����ݡ�
}



// CActiveXClockCtrl::~CActiveXClockCtrl - ��������

CActiveXClockCtrl::~CActiveXClockCtrl()
{
	// TODO: �ڴ�����ؼ���ʵ�����ݡ�
}



// CActiveXClockCtrl::OnDraw - ��ͼ����

void CActiveXClockCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: �����Լ��Ļ�ͼ�����滻����Ĵ��롣
	CBrush brush(TranslateColor(GetBackColor()));
	pdc->FillRect(rcBounds,&brush);
	pdc->SetTextColor(TranslateColor(GetForeColor()));
	CTime time = CTime::GetCurrentTime();
	pdc->TextOut(0,0,time.Format("%H:%M:%S"));
}



// CActiveXClockCtrl::DoPropExchange - �־���֧��

void CActiveXClockCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Ϊÿ���־õ��Զ������Ե��� PX_ ������
}



// CActiveXClockCtrl::OnResetState - ���ؼ�����ΪĬ��״̬

void CActiveXClockCtrl::OnResetState()
{
	COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

	// TODO: �ڴ��������������ؼ�״̬��
}



// CActiveXClockCtrl::AboutBox - ���û���ʾ�����ڡ���

void CActiveXClockCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_ACTIVEXCLOCK);
	dlgAbout.DoModal();
}



// CActiveXClockCtrl ��Ϣ�������

int CActiveXClockCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	SetTimer(1,1000,NULL);

	return 0;
}

void CActiveXClockCtrl::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//Invalidate();
	InvalidateControl();//ǿ�ƿؼ��ػ�����
	COleControl::OnTimer(nIDEvent);
}

void CActiveXClockCtrl::OnIntervalChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ�������Դ���������
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

	// TODO: �ڴ���ӵ��ȴ���������
	MessageBox(TEXT("Hello World!"));
}
