#pragma once

// ActiveXClockPropPage.h : CActiveXClockPropPage 属性页类的声明。


// CActiveXClockPropPage : 有关实现的信息，请参阅 ActiveXClockPropPage.cpp。

class CActiveXClockPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CActiveXClockPropPage)
	DECLARE_OLECREATE_EX(CActiveXClockPropPage)

// 构造函数
public:
	CActiveXClockPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_ACTIVEXCLOCK };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
public:
	short m_updateInterval;
};

