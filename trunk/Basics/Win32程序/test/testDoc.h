// testDoc.h : CtestDoc ��Ľӿ�
//


#pragma once


class CtestDoc : public CDocument
{
protected: // �������л�����
	CtestDoc();
	DECLARE_DYNCREATE(CtestDoc)

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
	virtual ~CtestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


