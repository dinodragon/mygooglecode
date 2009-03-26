// notepadView.h : CnotepadView ��Ľӿ�
//


#pragma once


class CnotepadView : public CEditView
{
protected: // �������л�����
	CnotepadView();
	DECLARE_DYNCREATE(CnotepadView)

// ����
public:
	CnotepadDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CnotepadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // notepadView.cpp �еĵ��԰汾
inline CnotepadDoc* CnotepadView::GetDocument() const
   { return reinterpret_cast<CnotepadDoc*>(m_pDocument); }
#endif

