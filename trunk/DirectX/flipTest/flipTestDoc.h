// flipTestDoc.h : CflipTestDoc ��Ľӿ�
//


#pragma once


class CflipTestDoc : public CDocument
{
protected: // �������л�����
	CflipTestDoc();
	DECLARE_DYNCREATE(CflipTestDoc)

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
	virtual ~CflipTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


