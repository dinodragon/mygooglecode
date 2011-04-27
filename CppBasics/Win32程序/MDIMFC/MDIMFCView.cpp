// MDIMFCView.cpp : CMDIMFCView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMDIMFCView ����/����

CMDIMFCView::CMDIMFCView()
{
	// TODO: �ڴ˴���ӹ������

}

CMDIMFCView::~CMDIMFCView()
{
}

BOOL CMDIMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMDIMFCView ����

void CMDIMFCView::OnDraw(CDC* /*pDC*/)
{
	CMDIMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMDIMFCView ��ӡ

BOOL CMDIMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMDIMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMDIMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMDIMFCView ���

#ifdef _DEBUG
void CMDIMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CMDIMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMDIMFCDoc* CMDIMFCView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMDIMFCDoc)));
	return (CMDIMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CMDIMFCView ��Ϣ�������
