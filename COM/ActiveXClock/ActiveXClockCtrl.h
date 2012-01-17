#pragma once

// ActiveXClockCtrl.h : CActiveXClockCtrl ActiveX �ؼ����������


// CActiveXClockCtrl : �й�ʵ�ֵ���Ϣ������� ActiveXClockCtrl.cpp��

class CActiveXClockCtrl : public COleControl
{
	DECLARE_DYNCREATE(CActiveXClockCtrl)

// ���캯��
public:
	CActiveXClockCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CActiveXClockCtrl();

	DECLARE_OLECREATE_EX(CActiveXClockCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CActiveXClockCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CActiveXClockCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CActiveXClockCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
public:
	enum {
		dispidHello = 2L,
		dispidInterval = 1
	};
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	void OnIntervalChanged(void);
	SHORT m_Interval;
	void Hello(void);
};

