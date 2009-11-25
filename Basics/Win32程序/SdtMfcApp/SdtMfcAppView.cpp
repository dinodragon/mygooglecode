// SdtMfcAppView.cpp : CSdtMfcAppView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CSdtMfcAppView ����/����

CSdtMfcAppView::CSdtMfcAppView()
{
	// TODO: �ڴ˴���ӹ������

}

CSdtMfcAppView::~CSdtMfcAppView()
{
}

BOOL CSdtMfcAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	m_mybtn.Dump(afxDump);
	return CView::PreCreateWindow(cs);
}

// CSdtMfcAppView ����

void CSdtMfcAppView::OnDraw(CDC* /*pDC*/)
{
	CSdtMfcAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CSdtMfcAppView ��ӡ

BOOL CSdtMfcAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CSdtMfcAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CSdtMfcAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CSdtMfcAppView ���

#ifdef _DEBUG
void CSdtMfcAppView::AssertValid() const
{
	CView::AssertValid();
}

void CSdtMfcAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
	dc<<"CSdtMfcAppView::Dump������";
}

CSdtMfcAppDoc* CSdtMfcAppView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSdtMfcAppDoc)));
	return (CSdtMfcAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CSdtMfcAppView ��Ϣ�������

void CSdtMfcAppView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
		// TODO: �ڴ���Ӵ洢����
		arrStr.Serialize(ar);
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}

	CView::OnLButtonDown(nFlags, point);
}
