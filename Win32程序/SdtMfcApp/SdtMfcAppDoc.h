// SdtMfcAppDoc.h : CSdtMfcAppDoc ��Ľӿ�
//


#pragma once


class CSdtMfcAppDoc : public CDocument
{
protected: // �������л�����
	CSdtMfcAppDoc();
	DECLARE_DYNCREATE(CSdtMfcAppDoc)

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
	virtual ~CSdtMfcAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


