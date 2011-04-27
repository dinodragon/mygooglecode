// testView.h : CtestView ��Ľӿ�
//


#pragma once
#include "atltypes.h"


class CtestView : public CView
{
protected: // �������л�����
	CtestView();
	DECLARE_DYNCREATE(CtestView)

// ����
public:
	CtestDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CtestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
private:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

private:
	CPoint m_startPoint;
	CPoint m_endPoint;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // testView.cpp �еĵ��԰汾
inline CtestDoc* CtestView::GetDocument() const
   { return reinterpret_cast<CtestDoc*>(m_pDocument); }
#endif

