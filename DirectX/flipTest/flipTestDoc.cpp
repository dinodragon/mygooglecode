// flipTestDoc.cpp : CflipTestDoc ���ʵ��
//

#include "stdafx.h"
#include "flipTest.h"

#include "flipTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CflipTestDoc

IMPLEMENT_DYNCREATE(CflipTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CflipTestDoc, CDocument)
END_MESSAGE_MAP()


// CflipTestDoc ����/����

CflipTestDoc::CflipTestDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CflipTestDoc::~CflipTestDoc()
{
}

BOOL CflipTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CflipTestDoc ���л�

void CflipTestDoc::Serialize(CArchive& ar)
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


// CflipTestDoc ���

#ifdef _DEBUG
void CflipTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CflipTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CflipTestDoc ����
