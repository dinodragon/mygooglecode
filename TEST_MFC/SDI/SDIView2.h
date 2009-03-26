#pragma once
#include "afxwin.h"
#include "SDIDoc.h"

class CSDIView2 :
	public CView
{
public:
	DECLARE_DYNCREATE(CSDIView2)
	CSDIView2(void);
	~CSDIView2(void);
	CSDIDoc* GetDocument() const;
protected:
	virtual void OnDraw(CDC* /*pDC*/);
};
