// MFCAppDoc.cpp : CMFCAppDoc 类的实现
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


// CMFCAppDoc 构造/析构

CMFCAppDoc::CMFCAppDoc()
{
	// TODO: 在此添加一次性构造代码

}

CMFCAppDoc::~CMFCAppDoc()
{
}

BOOL CMFCAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMFCAppDoc 序列化

void CMFCAppDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CMFCAppDoc 诊断

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


// CMFCAppDoc 命令
