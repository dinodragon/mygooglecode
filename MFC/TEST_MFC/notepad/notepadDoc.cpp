// notepadDoc.cpp : CnotepadDoc ���ʵ��
//

#include "stdafx.h"
#include "notepad.h"

#include "notepadDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CnotepadDoc

IMPLEMENT_DYNCREATE(CnotepadDoc, CDocument)

BEGIN_MESSAGE_MAP(CnotepadDoc, CDocument)
END_MESSAGE_MAP()


// CnotepadDoc ����/����

CnotepadDoc::CnotepadDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CnotepadDoc::~CnotepadDoc()
{
}

BOOL CnotepadDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CnotepadDoc ���л�

void CnotepadDoc::Serialize(CArchive& ar)
{
	// CEditView ����һ�������������л��ı༭�ؼ�
	reinterpret_cast<CEditView*>(m_viewList.GetHead())->SerializeRaw(ar);
}


// CnotepadDoc ���

#ifdef _DEBUG
void CnotepadDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CnotepadDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CnotepadDoc ����
