// DrawDoc.h : CDrawDoc ��Ľӿ�
//


#pragma once


class CDrawDoc : public CDocument
{
protected: // �������л�����
	CDrawDoc();
	DECLARE_DYNCREATE(CDrawDoc)

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
	virtual ~CDrawDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


