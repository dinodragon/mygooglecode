// MDIMFCDoc.cpp : CMDIMFCDoc 类的实现
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


// CMDIMFCDoc 构造/析构

CMDIMFCDoc::CMDIMFCDoc()
{
	// TODO: 在此添加一次性构造代码

}

CMDIMFCDoc::~CMDIMFCDoc()
{
}

BOOL CMDIMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMDIMFCDoc 序列化

void CMDIMFCDoc::Serialize(CArchive& ar)
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


// CMDIMFCDoc 诊断

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


// CMDIMFCDoc 命令
