// testView.cpp : CtestView ���ʵ��
//

#include "stdafx.h"
#include "test.h"

#include "testDoc.h"
#include "testView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestView

IMPLEMENT_DYNCREATE(CtestView, CView)

BEGIN_MESSAGE_MAP(CtestView, CView)
	
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CtestView ����/����

CtestView::CtestView()
: m_startPoint(0)
, m_endPoint(0)
{
	// TODO: �ڴ˴���ӹ������

}

CtestView::~CtestView()
{
}

BOOL CtestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CtestView ����

void CtestView::OnDraw(CDC* /*pDC*/)
{
	CtestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CtestView ���

#ifdef _DEBUG
void CtestView::AssertValid() const
{
	CView::AssertValid();
}

void CtestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CtestDoc* CtestView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtestDoc)));
	return (CtestDoc*)m_pDocument;
}
#endif //_DEBUG


// CtestView ��Ϣ�������

void CtestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//MessageBox(TEXT("View click!"));
	m_startPoint = point;
	CView::OnLButtonDown(nFlags, point);
}

void CtestView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_endPoint = point;
	//CClientDC dc(GetParent());
	CClientDC dc(this);
	//CWindowDC dc(this);
	//CWindowDC dc(GetParent());
	//CWindowDC dc(GetDesktopWindow());
	//CPen cPen(PS_SOLID,10,RGB(200,10,10));
	//dc.SelectObject(&cPen);
	
	CRect *pRect = &CRect(m_startPoint,point);
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP1);
	CBrush cBrush(&bitmap);
	dc.FillRect(pRect,&cBrush);

	dc.MoveTo(point);
	dc.LineTo(m_startPoint);

	CView::OnLButtonUp(nFlags, point);
}
