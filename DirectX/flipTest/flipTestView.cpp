// flipTestView.cpp : CflipTestView 类的实现
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CflipTestView 构造/析构

CflipTestView::CflipTestView()
{
	// TODO: 在此处添加构造代码
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
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CflipTestView 绘制
#define mid(a,b) (((a)+(b))/(2.0f))

void CflipTestView::OnDraw(CDC* pDC)
{
	CflipTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	// TODO: 在此处为本机数据添加绘制代码

	CClientDC dc(this);
	dc.SetViewportOrg(50,50);

	dc.Rectangle(a.x,a.y,c.x,c.y);

}


// CflipTestView 打印

BOOL CflipTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CflipTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CflipTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清除过程
}


// CflipTestView 诊断

#ifdef _DEBUG
void CflipTestView::AssertValid() const
{
	CView::AssertValid();
}

void CflipTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CflipTestDoc* CflipTestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CflipTestDoc)));
	return (CflipTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CflipTestView 消息处理程序

void CflipTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	POINT x1,x2,x3;
	POINT cd;
	CClientDC dc(this);
	dc.SetViewportOrg(50,50);
	dc.DPtoLP(&point);

	float k = (c.y-point.y)/float(c.x - point.x); //对称轴的斜率

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
	//对称轴方程 y = -kx+z
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
	//画垂点
	cd.x = (z-b.y+b.x/k)/(k+1/k);
	cd.y = -k*(cd.x) + z;
	dc.SetPixel(cd,RGB(255,0,0));


	CView::OnLButtonDown(nFlags, point);
}

void CflipTestView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Invalidate();
	CView::OnRButtonDown(nFlags, point);
}
