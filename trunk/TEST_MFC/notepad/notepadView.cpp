// notepadView.cpp : CnotepadView 类的实现
//

#include "stdafx.h"
#include "notepad.h"

#include "notepadDoc.h"
#include "notepadView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CnotepadView

IMPLEMENT_DYNCREATE(CnotepadView, CEditView)

BEGIN_MESSAGE_MAP(CnotepadView, CEditView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CnotepadView 构造/析构

CnotepadView::CnotepadView()
{
	// TODO: 在此处添加构造代码

}

CnotepadView::~CnotepadView()
{
}

BOOL CnotepadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// 启用换行

	return bPreCreated;
}


// CnotepadView 打印

BOOL CnotepadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认 CEditView 准备
	return CEditView::OnPreparePrinting(pInfo);
}

void CnotepadView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// 默认 CEditView 开始打印
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CnotepadView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// 默认 CEditView 结束打印
	CEditView::OnEndPrinting(pDC, pInfo);
}


// CnotepadView 诊断

#ifdef _DEBUG
void CnotepadView::AssertValid() const
{
	CEditView::AssertValid();
}

void CnotepadView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CnotepadDoc* CnotepadView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CnotepadDoc)));
	return (CnotepadDoc*)m_pDocument;
}
#endif //_DEBUG


// CnotepadView 消息处理程序
