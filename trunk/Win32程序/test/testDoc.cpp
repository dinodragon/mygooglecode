// testDoc.cpp : CtestDoc ���ʵ��
//

#include "stdafx.h"
#include "test.h"

#include "testDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestDoc

IMPLEMENT_DYNCREATE(CtestDoc, CDocument)

BEGIN_MESSAGE_MAP(CtestDoc, CDocument)
END_MESSAGE_MAP()


// CtestDoc ����/����

CtestDoc::CtestDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CtestDoc::~CtestDoc()
{
}

BOOL CtestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CtestDoc ���л�

void CtestDoc::Serialize(CArchive& ar)
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


// CtestDoc ���

#ifdef _DEBUG
void CtestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CtestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CtestDoc ����
