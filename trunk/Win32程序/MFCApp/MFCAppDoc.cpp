// MFCAppDoc.cpp : CMFCAppDoc ���ʵ��
//

#include "stdafx.h"
#include "MFCApp.h"

#include "MFCAppDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCAppDoc

IMPLEMENT_DYNCREATE(CMFCAppDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCAppDoc, CDocument)
END_MESSAGE_MAP()


// CMFCAppDoc ����/����

CMFCAppDoc::CMFCAppDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CMFCAppDoc::~CMFCAppDoc()
{
}

BOOL CMFCAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMFCAppDoc ���л�

void CMFCAppDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CMFCAppDoc ���

#ifdef _DEBUG
void CMFCAppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCAppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCAppDoc ����
