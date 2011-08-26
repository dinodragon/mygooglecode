// ListCtrlWithCustomDraw.cpp : implementation file
//

#include "stdafx.h"
#include "ListCtrlColor.h"
#include "ListCtrlWithCustomDraw.h"


// CListCtrlWithCustomDraw

IMPLEMENT_DYNAMIC(CListCtrlWithCustomDraw, CListCtrl)

CListCtrlWithCustomDraw::CListCtrlWithCustomDraw()
{

}

CListCtrlWithCustomDraw::~CListCtrlWithCustomDraw()
{
}


BEGIN_MESSAGE_MAP(CListCtrlWithCustomDraw, CListCtrl)
  ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CListCtrlWithCustomDraw::OnNMCustomdraw)
END_MESSAGE_MAP()



// CListCtrlWithCustomDraw message handlers



void CListCtrlWithCustomDraw::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
  LPNMLVCUSTOMDRAW lpLVCustomDraw = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);

  switch(lpLVCustomDraw->nmcd.dwDrawStage)
  {
    case CDDS_ITEMPREPAINT:
    case CDDS_ITEMPREPAINT | CDDS_SUBITEM:
      if (0 == ((lpLVCustomDraw->nmcd.dwItemSpec + lpLVCustomDraw->iSubItem) % 2))
      {
        lpLVCustomDraw->clrText = RGB(255,255,255);
        lpLVCustomDraw->clrTextBk = RGB(0,0,0);
      }
      else 
      {
        lpLVCustomDraw->clrText = CLR_DEFAULT;
        lpLVCustomDraw->clrTextBk = CLR_DEFAULT;
      }
    break;

    default: break;    
  }

  // TODO: Add your control notification handler code here
  *pResult = 0;
  *pResult |= CDRF_NOTIFYPOSTPAINT;
  *pResult |= CDRF_NOTIFYITEMDRAW;
  *pResult |= CDRF_NOTIFYSUBITEMDRAW;
}
