// MDIMFCDoc.cpp : CMDIMFCDoc ���ʵ��
//

#include "stdafx.h"
#include "MDIMFC.h"

#include "MDIMFCDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMDIMFCDoc

IMPLEMENT_DYNCREATE(CMDIMFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CMDIMFCDoc, CDocument)
END_MESSAGE_MAP()


// CMDIMFCDoc ����/����

CMDIMFCDoc::CMDIMFCDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CMDIMFCDoc::~CMDIMFCDoc()
{
}

BOOL CMDIMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMDIMFCDoc ���л�

void CMDIMFCDoc::Serialize(CArchive& ar)
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


// CMDIMFCDoc ���

#ifdef _DEBUG
void CMDIMFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMDIMFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMDIMFCDoc ����
