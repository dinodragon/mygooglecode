// SdtMfcAppDoc.cpp : CSdtMfcAppDoc ���ʵ��
//

#include "stdafx.h"
#include "SdtMfcApp.h"

#include "SdtMfcAppDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSdtMfcAppDoc

IMPLEMENT_DYNCREATE(CSdtMfcAppDoc, CDocument)

BEGIN_MESSAGE_MAP(CSdtMfcAppDoc, CDocument)
END_MESSAGE_MAP()


// CSdtMfcAppDoc ����/����

CSdtMfcAppDoc::CSdtMfcAppDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CSdtMfcAppDoc::~CSdtMfcAppDoc()
{
}

BOOL CSdtMfcAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CSdtMfcAppDoc ���л�

void CSdtMfcAppDoc::Serialize(CArchive& ar)
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


// CSdtMfcAppDoc ���

#ifdef _DEBUG
void CSdtMfcAppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSdtMfcAppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSdtMfcAppDoc ����
