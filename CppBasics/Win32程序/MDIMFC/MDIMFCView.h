// MDIMFCView.h : CMDIMFCView ��Ľӿ�
//


#pragma once


class CMDIMFCView : public CView
{
protected: // �������л�����
	CMDIMFCView();
	DECLARE_DYNCREATE(CMDIMFCView)

// ����
public:
	CMDIMFCDoc* GetDocument() const;

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
	virtual ~CMDIMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MDIMFCView.cpp �еĵ��԰汾
inline CMDIMFCDoc* CMDIMFCView::GetDocument() const
   { return reinterpret_cast<CMDIMFCDoc*>(m_pDocument); }
#endif

