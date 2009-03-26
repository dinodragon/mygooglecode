// MFCAppView.h : CMFCAppView ��Ľӿ�
//


#pragma once


class CMFCAppView : public CView
{
protected: // �������л�����
	CMFCAppView();
	DECLARE_DYNCREATE(CMFCAppView)

// ����
public:
	CMFCAppDoc* GetDocument() const;

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
	virtual ~CMFCAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MFCAppView.cpp �еĵ��԰汾
inline CMFCAppDoc* CMFCAppView::GetDocument() const
   { return reinterpret_cast<CMFCAppDoc*>(m_pDocument); }
#endif

