// MFCAppDoc.h : CMFCAppDoc ��Ľӿ�
//


#pragma once


class CMFCAppDoc : public CDocument
{
protected: // �������л�����
	CMFCAppDoc();
	DECLARE_DYNCREATE(CMFCAppDoc)

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
	virtual ~CMFCAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


