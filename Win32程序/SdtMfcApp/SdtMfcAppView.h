// SdtMfcAppView.h : CSdtMfcAppView 类的接口
//


#pragma once
#include "mybutton.h"


class CSdtMfcAppView : public CView
{
protected: // 仅从序列化创建
	CSdtMfcAppView();
	DECLARE_DYNCREATE(CSdtMfcAppView)

// 属性
public:
	CSdtMfcAppDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CSdtMfcAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	CMyButton m_mybtn;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // SdtMfcAppView.cpp 中的调试版本
inline CSdtMfcAppDoc* CSdtMfcAppView::GetDocument() const
   { return reinterpret_cast<CSdtMfcAppDoc*>(m_pDocument); }
#endif

