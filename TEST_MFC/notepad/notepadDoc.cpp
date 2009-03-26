// notepadDoc.cpp : CnotepadDoc 类的实现
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


// CnotepadDoc 构造/析构

CnotepadDoc::CnotepadDoc()
{
	// TODO: 在此添加一次性构造代码

}

CnotepadDoc::~CnotepadDoc()
{
}

BOOL CnotepadDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CnotepadDoc 序列化

void CnotepadDoc::Serialize(CArchive& ar)
{
	// CEditView 包含一个处理所有序列化的编辑控件
	reinterpret_cast<CEditView*>(m_viewList.GetHead())->SerializeRaw(ar);
}


// CnotepadDoc 诊断

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


// CnotepadDoc 命令
