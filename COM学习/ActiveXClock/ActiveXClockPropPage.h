#pragma once

// ActiveXClockPropPage.h : CActiveXClockPropPage ����ҳ���������


// CActiveXClockPropPage : �й�ʵ�ֵ���Ϣ������� ActiveXClockPropPage.cpp��

class CActiveXClockPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CActiveXClockPropPage)
	DECLARE_OLECREATE_EX(CActiveXClockPropPage)

// ���캯��
public:
	CActiveXClockPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_ACTIVEXCLOCK };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	short m_updateInterval;
};

