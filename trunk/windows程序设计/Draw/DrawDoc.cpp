// DrawDoc.cpp : CDrawDoc ���ʵ��
//

#include "stdafx.h"
#include "Draw.h"

#include "DrawDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawDoc

IMPLEMENT_DYNCREATE(CDrawDoc, CDocument)

BEGIN_MESSAGE_MAP(CDrawDoc, CDocument)
END_MESSAGE_MAP()


// CDrawDoc ����/����

CDrawDoc::CDrawDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CDrawDoc::~CDrawDoc()
{
}

BOOL CDrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CDrawDoc ���л�

void CDrawDoc::Serialize(CArchive& ar)
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


// CDrawDoc ���

#ifdef _DEBUG
void CDrawDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDrawDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDrawDoc ����
