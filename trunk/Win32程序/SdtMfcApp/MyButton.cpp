// MyButton.cpp : 实现文件
//

#include "stdafx.h"
#include "SdtMfcApp.h"
#include "MyButton.h"


// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)

CMyButton::CMyButton()
{

}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
END_MESSAGE_MAP()



// CMyButton 消息处理程序



void CMyButton::Dump(CDumpContext& dc) const
{
	CButton::Dump(dc);

	// TODO: 在此添加专用代码和/或调用基类
}
