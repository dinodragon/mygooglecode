// notepadDoc.h : CnotepadDoc ��Ľӿ�
//


#pragma once


class CnotepadDoc : public CDocument
{
protected: // �������л�����
	CnotepadDoc();
	DECLARE_DYNCREATE(CnotepadDoc)

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
	virtual ~CnotepadDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


