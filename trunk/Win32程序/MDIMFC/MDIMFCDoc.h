// MDIMFCDoc.h : CMDIMFCDoc ��Ľӿ�
//


#pragma once


class CMDIMFCDoc : public CDocument
{
protected: // �������л�����
	CMDIMFCDoc();
	DECLARE_DYNCREATE(CMDIMFCDoc)

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
	virtual ~CMDIMFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


