// SdtMfcAppView.h : CSdtMfcAppView ��Ľӿ�
//


#pragma once
#include "mybutton.h"


class CSdtMfcAppView : public CView
{
protected: // �������л�����
	CSdtMfcAppView();
	DECLARE_DYNCREATE(CSdtMfcAppView)

// ����
public:
	CSdtMfcAppDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CSdtMfcAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	CMyButton m_mybtn;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // SdtMfcAppView.cpp �еĵ��԰汾
inline CSdtMfcAppDoc* CSdtMfcAppView::GetDocument() const
   { return reinterpret_cast<CSdtMfcAppDoc*>(m_pDocument); }
#endif

