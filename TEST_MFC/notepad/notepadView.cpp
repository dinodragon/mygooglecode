// notepadView.cpp : CnotepadView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CnotepadView ����/����

CnotepadView::CnotepadView()
{
	// TODO: �ڴ˴���ӹ������

}

CnotepadView::~CnotepadView()
{
}

BOOL CnotepadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// ���û���

	return bPreCreated;
}


// CnotepadView ��ӡ

BOOL CnotepadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ׼��
	return CEditView::OnPreparePrinting(pInfo);
}

void CnotepadView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ��ʼ��ӡ
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CnotepadView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ������ӡ
	CEditView::OnEndPrinting(pDC, pInfo);
}


// CnotepadView ���

#ifdef _DEBUG
void CnotepadView::AssertValid() const
{
	CEditView::AssertValid();
}

void CnotepadView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CnotepadDoc* CnotepadView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CnotepadDoc)));
	return (CnotepadDoc*)m_pDocument;
}
#endif //_DEBUG


// CnotepadView ��Ϣ�������
