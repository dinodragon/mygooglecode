// SdtMfcAppDoc.cpp : CSdtMfcAppDoc 类的实现
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


// CSdtMfcAppDoc 构造/析构

CSdtMfcAppDoc::CSdtMfcAppDoc()
{
	// TODO: 在此添加一次性构造代码

}

CSdtMfcAppDoc::~CSdtMfcAppDoc()
{
}

BOOL CSdtMfcAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CSdtMfcAppDoc 序列化

void CSdtMfcAppDoc::Serialize(CArchive& ar)
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


// CSdtMfcAppDoc 诊断

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


// CSdtMfcAppDoc 命令
