// MDIMFCView.cpp : CMDIMFCView 类的实现
//

#include "stdafx.h"
#include "MDIMFC.h"

#include "MDIMFCDoc.h"
#include "MDIMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMDIMFCView

IMPLEMENT_DYNCREATE(CMDIMFCView, CView)

BEGIN_MESSAGE_MAP(CMDIMFCView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMDIMFCView 构造/析构

CMDIMFCView::CMDIMFCView()
{
	// TODO: 在此处添加构造代码

}

CMDIMFCView::~CMDIMFCView()
{
}

BOOL CMDIMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMDIMFCView 绘制

void CMDIMFCView::OnDraw(CDC* /*pDC*/)
{
	CMDIMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMDIMFCView 打印

BOOL CMDIMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMDIMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMDIMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清除过程
}


// CMDIMFCView 诊断

#ifdef _DEBUG
void CMDIMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CMDIMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMDIMFCDoc* CMDIMFCView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMDIMFCDoc)));
	return (CMDIMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CMDIMFCView 消息处理程序
