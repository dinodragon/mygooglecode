// SdtMfcAppView.cpp : CSdtMfcAppView 类的实现
//

#include "stdafx.h"
#include "SdtMfcApp.h"

#include "SdtMfcAppDoc.h"
#include "SdtMfcAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSdtMfcAppView

IMPLEMENT_DYNCREATE(CSdtMfcAppView, CView)

BEGIN_MESSAGE_MAP(CSdtMfcAppView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CSdtMfcAppView 构造/析构

CSdtMfcAppView::CSdtMfcAppView()
{
	// TODO: 在此处添加构造代码

}

CSdtMfcAppView::~CSdtMfcAppView()
{
}

BOOL CSdtMfcAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	m_mybtn.Dump(afxDump);
	return CView::PreCreateWindow(cs);
}

// CSdtMfcAppView 绘制

void CSdtMfcAppView::OnDraw(CDC* /*pDC*/)
{
	CSdtMfcAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CSdtMfcAppView 打印

BOOL CSdtMfcAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CSdtMfcAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CSdtMfcAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清除过程
}


// CSdtMfcAppView 诊断

#ifdef _DEBUG
void CSdtMfcAppView::AssertValid() const
{
	CView::AssertValid();
}

void CSdtMfcAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
	dc<<"CSdtMfcAppView::Dump被调用";
}

CSdtMfcAppDoc* CSdtMfcAppView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSdtMfcAppDoc)));
	return (CSdtMfcAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CSdtMfcAppView 消息处理程序

void CSdtMfcAppView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CFile * pfile = new CFile(TEXT("test.txt"),CFile::modeReadWrite | CFile::modeCreate);
	ASSERT(pfile);
	CArchive ar(pfile,CArchive::store);
	CString str = TEXT("ABCDEFG");
	CStringArray arrStr;
	arrStr.Add(str);
	//ar<<arrStr;
	BOOL flag = arrStr.IsSerializable();
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		arrStr.Serialize(ar);
	}
	else
	{
		// TODO: 在此添加加载代码
	}

	CView::OnLButtonDown(nFlags, point);
}
