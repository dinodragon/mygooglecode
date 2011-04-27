// testView.cpp : CtestView 类的实现
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

// CtestView 构造/析构

CtestView::CtestView()
: m_startPoint(0)
, m_endPoint(0)
{
	// TODO: 在此处添加构造代码

}

CtestView::~CtestView()
{
}

BOOL CtestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CtestView 绘制

void CtestView::OnDraw(CDC* /*pDC*/)
{
	CtestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CtestView 诊断

#ifdef _DEBUG
void CtestView::AssertValid() const
{
	CView::AssertValid();
}

void CtestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CtestDoc* CtestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtestDoc)));
	return (CtestDoc*)m_pDocument;
}
#endif //_DEBUG


// CtestView 消息处理程序

void CtestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//MessageBox(TEXT("View click!"));
	m_startPoint = point;
	CView::OnLButtonDown(nFlags, point);
}

void CtestView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
