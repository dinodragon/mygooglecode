// flipTestView.h : CflipTestView ��Ľӿ�
//


#pragma once


class CflipTestView : public CView
{
protected: // �������л�����
	CflipTestView();
	DECLARE_DYNCREATE(CflipTestView)

// ����
public:
	CflipTestDoc* GetDocument() const;
private:
	POINT a,b,c; //���½�

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
	virtual ~CflipTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // flipTestView.cpp �еĵ��԰汾
inline CflipTestDoc* CflipTestView::GetDocument() const
   { return reinterpret_cast<CflipTestDoc*>(m_pDocument); }
#endif

