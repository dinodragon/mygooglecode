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
	// TODO: �ڴ����ר�ô����/����û���
	CSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CString temp;
	temp.Format(_T("X:%d,Y:%d"),pDoc->m_point.x,pDoc->m_point.y);
	pDC->TextOut(5,5,temp);
}

CSDIDoc* CSDIView2::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIDoc)));
	return (CSDIDoc*)m_pDocument;
}