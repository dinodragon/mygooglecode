// SDIDoc.h : CSDIDoc ��Ľӿ�
//


#pragma once
#include "atltypes.h"


class CSDIDoc : public CDocument
{
public: // �������л�����
	CSDIDoc();
	DECLARE_DYNCREATE(CSDIDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CSDIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	CPoint m_point;
};


