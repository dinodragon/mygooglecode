#pragma once

// ActiveXClockCtrl.h : CActiveXClockCtrl ActiveX 控件类的声明。


// CActiveXClockCtrl : 有关实现的信息，请参阅 ActiveXClockCtrl.cpp。

class CActiveXClockCtrl : public COleControl
{
	DECLARE_DYNCREATE(CActiveXClockCtrl)

// 构造函数
public:
	CActiveXClockCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CActiveXClockCtrl();

	DECLARE_OLECREATE_EX(CActiveXClockCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CActiveXClockCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CActiveXClockCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CActiveXClockCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
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

