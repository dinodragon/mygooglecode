// MyButton.cpp : ʵ���ļ�
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



// CMyButton ��Ϣ�������



void CMyButton::Dump(CDumpContext& dc) const
{
	CButton::Dump(dc);

	// TODO: �ڴ����ר�ô����/����û���
}
