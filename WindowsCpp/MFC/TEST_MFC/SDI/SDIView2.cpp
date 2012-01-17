#include "StdAfx.h"
#include "SDIView2.h"

IMPLEMENT_DYNCREATE(CSDIView2, CView)

CSDIView2::CSDIView2(void)
{
}

CSDIView2::~CSDIView2(void)
{
}

void CSDIView2::OnDraw(CDC* pDC)
{
	// TODO: 在此添加专用代码和/或调用基类
	CSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CString temp;
	temp.Format(_T("X:%d,Y:%d"),pDoc->m_point.x,pDoc->m_point.y);
	pDC->TextOut(5,5,temp);
}

CSDIDoc* CSDIView2::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIDoc)));
	return (CSDIDoc*)m_pDocument;
}