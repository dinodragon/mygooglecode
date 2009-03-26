// flipTestView.cpp : CflipTestView ���ʵ��
//

#include "stdafx.h"
#include "flipTest.h"

#include "flipTestDoc.h"
#include "flipTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CflipTestView

IMPLEMENT_DYNCREATE(CflipTestView, CView)

BEGIN_MESSAGE_MAP(CflipTestView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CflipTestView ����/����

CflipTestView::CflipTestView()
{
	// TODO: �ڴ˴���ӹ������
	a.x = 0;
	a.y = 0;
	b.x = 600;
	b.y = 0;
	c.x = 600;
	c.y = 400;
}

CflipTestView::~CflipTestView()
{
}

BOOL CflipTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CflipTestView ����
#define mid(a,b) (((a)+(b))/(2.0f))

void CflipTestView::OnDraw(CDC* pDC)
{
	CflipTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���

	CClientDC dc(this);
	dc.SetViewportOrg(50,50);

	dc.Rectangle(a.x,a.y,c.x,c.y);

}


// CflipTestView ��ӡ

BOOL CflipTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CflipTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CflipTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CflipTestView ���

#ifdef _DEBUG
void CflipTestView::AssertValid() const
{
	CView::AssertValid();
}

void CflipTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CflipTestDoc* CflipTestView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CflipTestDoc)));
	return (CflipTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CflipTestView ��Ϣ�������

void CflipTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	POINT x1,x2,x3;
	POINT cd;
	CClientDC dc(this);
	dc.SetViewportOrg(50,50);
	dc.DPtoLP(&point);

	float k = (c.y-point.y)/float(c.x - point.x); //�Գ����б��

	x1.y = c.y;
	x1.x = (mid(point.y,c.y) - x1.y)*k + mid(point.x,c.x);

	x2.y = b.y;
	x2.x = (mid(point.y,c.y) - x2.y)*k + mid(point.x,c.x);

	if (x2.x > c.x)
	{
		x2.x = c.x;
		x2.y = mid(point.y,c.y) - (x2.x - mid(point.x,c.x))/k;
	}

	k = 1/k;
	//�Գ��᷽�� y = -kx+z
	float z = k * (mid(point.x,c.x)) + mid(point.y,c.y);

//	x3.x = 2*(k*z-b.x-k*b.y)/(k*k -1) - b.x;
//	x3.y = 2*((k*z-b.x-k*b.y)/(1-k) + z) - b.y;

	dc.MoveTo(c);
	dc.LineTo(point);
	dc.LineTo(x1);
	dc.LineTo(x2);
	//dc.LineTo(x3);
	//SetPixeldc.LineTo(cd);
	dc.LineTo(point);


	for (float x=200.0f;x<700;x += 0.1f)
	{
		float y = b.y + (x - b.x)/k;
		dc.SetPixel(x,y,RGB(0,255,0));
	}
	//������
	cd.x = (z-b.y+b.x/k)/(k+1/k);
	cd.y = -k*(cd.x) + z;
	dc.SetPixel(cd,RGB(255,0,0));


	CView::OnLButtonDown(nFlags, point);
}

void CflipTestView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	Invalidate();
	CView::OnRButtonDown(nFlags, point);
}
