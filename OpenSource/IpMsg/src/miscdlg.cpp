static char *miscdlg_id = 
	"@(#)Copyright (C) H.Shirouzu 1996-2005   miscdlg.cpp	Ver2.05";
/* ========================================================================
	Project  Name			: IP Messenger for Win32
	Module Name				: Misc Dialog
	Create					: 1996-12-15(Sun)
	Update					: 2004-01-01(Thu)
	Copyright				: H.Shirouzu
	Reference				: 
	======================================================================== */

#include "resource.h"
#include "ipmsg.h"
#include "blowfish.h"
#include <mbstring.h>

int TMsgDlg::createCnt = 0;

/*
	TMsgDlgは、制約の多いMessageBoxU8()の代用として作成
*/
TMsgDlg::TMsgDlg(TWin *_parent) : TListDlg(MESSAGE_DIALOG, _parent)
{
	hAccel = ::LoadAccelerators(TApp::GetInstance(), (LPCSTR)IPMSG_ACCEL);
}

/*
	終了ルーチン
*/
TMsgDlg::~TMsgDlg()
{
	createCnt--;
}

/*
	Window生成ルーチン
*/
BOOL TMsgDlg::Create(char *text, char *title, int _showMode)
{
	showMode = _showMode;

	if (TDlg::Create() == FALSE)
		return	FALSE;

	SetDlgItemTextU8(MESSAGE_TEXT, text);
	SetWindowTextU8(title);
	if (showMode == SW_SHOW) {
		::EnableWindow(hWnd, TRUE);
		::ShowWindow(hWnd, ((GetAsyncKeyState(VK_LBUTTON)|GetAsyncKeyState(VK_RBUTTON)|GetAsyncKeyState(VK_MBUTTON)) & 0x8000) ? SW_SHOWNOACTIVATE : SW_SHOW);
	}
	else {
		::ShowWindow(hWnd, SW_SHOWMINNOACTIVE);
		::EnableWindow(hWnd, TRUE);
	}

	if (strstr(text, "\r\n"))
	{
		WINDOWPLACEMENT wp;
		wp.length = sizeof(wp);
		::GetWindowPlacement(GetDlgItem(MESSAGE_TEXT), &wp);
		wp.rcNormalPosition.top -= ::GetSystemMetrics(SM_CYCAPTION) / 4;
		::SetWindowPlacement(GetDlgItem(MESSAGE_TEXT), &wp);
	}
	return	TRUE;
}

/*
	WM_COMMAND CallBack
*/
BOOL TMsgDlg::EvCommand(WORD wNotifyCode, WORD wID, LPARAM hWndCtl)
{
	switch (wID)
	{
	case MISC_ACCEL:
	case HIDE_ACCEL:
		::PostMessage(GetMainWnd(), WM_COMMAND, wID, 0);
		return	TRUE;

	case IDOK:
	case IDCANCEL:
		EndDialog(FALSE);
		::PostMessage(GetMainWnd(), WM_MSGDLG_EXIT, (WPARAM)0, (LPARAM)this);
		return	TRUE;
	}
	return	FALSE;
}

/*
	Window 生成時の CallBack。Screenの中心を起点として、すでに開いている
	TMsgDlgの枚数 * Caption Sizeを ずらして表示
*/
BOOL TMsgDlg::EvCreate(LPARAM lParam)
{
	SetDlgIcon(hWnd);

	if (rect.left == CW_USEDEFAULT)
	{
		GetWindowRect(&rect);
		int xsize = rect.right - rect.left, ysize = rect.bottom - rect.top;
		int	cx = ::GetSystemMetrics(SM_CXFULLSCREEN), cy = ::GetSystemMetrics(SM_CYFULLSCREEN);
		int	x = (cx - xsize)/2 + createCnt * ::GetSystemMetrics(SM_CYCAPTION);
		int y = (cy - ysize)/2 + createCnt * ::GetSystemMetrics(SM_CYCAPTION);

		MoveWindow((x < 0) ? 0 : x % (cx - xsize), (y < 0) ? 0 : y % (cy - ysize), xsize, ysize, FALSE);
	}

	createCnt++;
	return	TRUE;
}

/*
	About Dialog初期化処理
*/
TAboutDlg::TAboutDlg(TWin *_parent) : TDlg(ABOUT_DIALOG, _parent)
{
}

/*
	Window 生成時の CallBack
*/
BOOL TAboutDlg::EvCreate(LPARAM lParam)
{
	SetDlgIcon(hWnd);

	char	buf[512], buf2[512];
	GetDlgItemTextU8(ABOUT_TEXT, buf, sizeof(buf));
	wsprintf(buf2, buf, GetVersionStr());
	SetDlgItemTextU8(ABOUT_TEXT, buf2);

	if (rect.left == CW_USEDEFAULT)
	{
		GetWindowRect(&rect);
		int xsize = rect.right - rect.left, ysize = rect.bottom - rect.top;
		int	cx = ::GetSystemMetrics(SM_CXFULLSCREEN), cy = ::GetSystemMetrics(SM_CYFULLSCREEN);
		int	x = (cx - xsize)/2;
		int y = (cy - ysize)/2;

		MoveWindow((x < 0) ? 0 : x % (cx - xsize), (y < 0) ? 0 : y % (cy - ysize), xsize, ysize, FALSE);
	}
	else
		MoveWindow(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, FALSE);

	return	TRUE;
}

BOOL TAboutDlg::EvCommand(WORD wNotifyCode, WORD wID, LPARAM hWndCtl)
{
	switch (wID)
	{
	case IDOK:
	case IDCANCEL:
		EndDialog(TRUE);
		return	TRUE;

	case IPMSG_ICON: case IPMSGWEB_BUTTON:
		if (wID == IPMSGWEB_BUTTON || wNotifyCode == 1)
			ShellExecuteU8(NULL, NULL, GetLoadStrU8(IDS_IPMSGURL), NULL, NULL, SW_SHOW);
		return	TRUE;
	}
	return	FALSE;
}

/*
	listview control の subclass化
	Focus を失ったときにも、選択色を変化させないための小細工
*/
#define INVALID_INDEX	-1
TListViewEx::TListViewEx(TWin *_parent) : TSubClassCtl(_parent)
{
	focus_index = INVALID_INDEX;
}

BOOL TListViewEx::EventFocus(UINT uMsg, HWND hFocusWnd)
{
	LV_ITEM	lvi;

	memset(&lvi, 0, sizeof(lvi));
	lvi.mask = LVIF_STATE;
	lvi.stateMask = LVIS_FOCUSED;
	int	maxItem = SendMessage(LVM_GETITEMCOUNT, 0, 0);
	int itemNo;

	for (itemNo=0; itemNo < maxItem; itemNo++) {
		if (SendMessage(LVM_GETITEMSTATE, itemNo, (LPARAM)LVIS_FOCUSED) & LVIS_FOCUSED)
			break;
	}

	if (uMsg == WM_SETFOCUS)
	{
		if (itemNo == maxItem) {
			lvi.state = LVIS_FOCUSED;
			if (focus_index == INVALID_INDEX)
				focus_index = 0;
			SendMessage(LVM_SETITEMSTATE, focus_index, (LPARAM)&lvi);
			SendMessage(LVM_SETSELECTIONMARK, 0, focus_index);
		}
		return	FALSE;
	}
	else {	// WM_KILLFOCUS
		if (itemNo != maxItem) {
			SendMessage(LVM_SETITEMSTATE, itemNo, (LPARAM)&lvi);
			focus_index = itemNo;
		}
		return	TRUE;	// WM_KILLFOCUS は伝えない
	}
}

BOOL TListViewEx::EventButton(UINT uMsg, int nHitTest, POINTS pos)
{
	switch (uMsg)
	{
	case WM_RBUTTONDOWN:
		return	TRUE;
	case WM_RBUTTONUP:
		::PostMessage(parent->hWnd, uMsg, nHitTest, *(LPARAM *)&pos);
		return	TRUE;
	}
	return	FALSE;
}

BOOL TListViewEx::EventUser(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (focus_index == INVALID_INDEX)
		return	FALSE;

	switch (uMsg) {
	case LVM_INSERTITEM:
		if (((LV_ITEM *)lParam)->iItem <= focus_index)
			focus_index++;
		break;
	case LVM_DELETEITEM:
		if ((int)wParam == focus_index)
			focus_index = INVALID_INDEX;
		else if ((int)wParam < focus_index)
			focus_index--;
		break;
	case LVM_DELETEALLITEMS:
		focus_index = INVALID_INDEX;
		break;
	}
	return	FALSE;
}

/*
	edit control の subclass化
*/
TEditSub::TEditSub(Cfg *_cfg, TWin *_parent) : TSubClassCtl(_parent)
{
	cfg = _cfg;
}

#define EM_SETEVENTMASK			(WM_USER + 69)
#define EM_GETEVENTMASK			(WM_USER + 59)
#define ENM_LINK				0x04000000

BOOL TEditSub::AttachWnd(HWND _hWnd)
{
	if (!TSubClassCtl::AttachWnd(_hWnd))
		return	FALSE;

	DWORD	evMask = SendMessage(EM_GETEVENTMASK, 0, 0) | ENM_LINK;
	SendMessage(EM_SETEVENTMASK, 0, evMask); 
	dblClicked = FALSE;
	return	TRUE;
}

BOOL TEditSub::EvCommand(WORD wNotifyCode, WORD wID, LPARAM hWndCtl)
{
	switch (wID)
	{
	case WM_UNDO:
	case WM_CUT:
	case WM_COPY:
	case WM_PASTE:
	case WM_CLEAR:
		SendMessage(wID, 0, 0);
		return	TRUE;

	case EM_SETSEL:
		SendMessage(wID, 0, -1);
		return	TRUE;
	}
	return	FALSE;
}

BOOL TEditSub::EventButton(UINT uMsg, int nHitTest, POINTS pos)
{
	switch (uMsg)
	{
	case WM_LBUTTONDBLCLK:
//		PostMessage(WM_EDIT_DBLCLK, 0, 0);
		dblClicked = TRUE;
		break;

	case WM_LBUTTONUP:
		if (dblClicked) {
			PostMessage(WM_EDIT_DBLCLK, 0, 0);
			dblClicked = FALSE;
		}
		break;
	}
	return	FALSE;
}

BOOL TEditSub::EventFocus(UINT uMsg, HWND hFocusWnd)
{
	return	FALSE;
}

BOOL TEditSub::EvContextMenu(HWND childWnd, POINTS pos)
{
	HMENU	hMenu = ::CreatePopupMenu();
	BOOL	is_readonly = GetWindowLong(GWL_STYLE) & ES_READONLY;

	AppendMenuU8(hMenu, MF_STRING|((is_readonly || !SendMessage(EM_CANUNDO, 0, 0)) ? MF_DISABLED|MF_GRAYED : 0), WM_UNDO, GetLoadStrU8(IDS_UNDO));
	AppendMenuU8(hMenu, MF_SEPARATOR, 0, 0);
	AppendMenuU8(hMenu, MF_STRING|(is_readonly ? MF_DISABLED|MF_GRAYED : 0), WM_CUT, GetLoadStrU8(IDS_CUT));
	AppendMenuU8(hMenu, MF_STRING, WM_COPY, GetLoadStrU8(IDS_COPY));
	AppendMenuU8(hMenu, MF_STRING|((is_readonly || !SendMessage(EM_CANPASTE, 0, 0)) ? MF_DISABLED|MF_GRAYED : 0), WM_PASTE, GetLoadStrU8(IDS_PASTE));
	AppendMenuU8(hMenu, MF_STRING|(is_readonly ? MF_DISABLED|MF_GRAYED : 0), WM_CLEAR, GetLoadStrU8(IDS_DELETE));
	AppendMenuU8(hMenu, MF_SEPARATOR, 0, 0);
	AppendMenuU8(hMenu, MF_STRING, EM_SETSEL, GetLoadStrU8(IDS_SELECTALL));

	::TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, pos.x, pos.y, 0, hWnd, NULL);
	::DestroyMenu(hMenu);

	return	TRUE;
}

BOOL TEditSub::EventUser(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_EDIT_DBLCLK:
		CHARRANGE	cr;
		LONG		&start	= cr.cpMin;
		LONG		&end	= cr.cpMax;

		SendMessageW(EM_EXGETSEL, 0, (LPARAM)&cr);

		if (start != end && end < MAX_UDPBUF) {
			WCHAR	*wbuf = new WCHAR[MAX_UDPBUF];
			UrlObj	*obj = NULL;
			BOOL	modify = FALSE;
			WCHAR	*terminate_chars = L"\r\n\t \x3000";	// \x3000 ... 全角空白

			int max_len = ExGetText(wbuf, MAX_UDPBUF, GT_DEFAULT, 1200);	// 1200 == UNICODE

			for ( ; start > 0 && !wcschr(terminate_chars, wbuf[start-1]); start--) {
				modify = TRUE;
			}
			if (!wcschr(terminate_chars, wbuf[end-1])) {
				for ( ; end < max_len && !wcschr(terminate_chars, wbuf[end]); end++) {
					modify = TRUE;
				}
			}
			if (modify) {
				SendMessageW(EM_EXSETSEL, 0, (LPARAM)&cr);
			}
			memmove(wbuf, wbuf + start, (end - start) * sizeof(WCHAR));
			wbuf[end - start] = 0;
			char	*url_ptr;
			char	*u8buf = WtoU8(wbuf, TRUE);

			if ((url_ptr = strstr(u8buf, URL_STR))) {
				char	proto[MAX_NAMEBUF];

				strncpyz(proto, u8buf, min(url_ptr - u8buf + 1, sizeof(proto)));
				for (int i=0; proto[i]; i++) {
					if ((obj = SearchUrlObj(&cfg->urlList, proto + i)) != NULL) {
						url_ptr = u8buf + i;
						break;
					}
				}
			}
			if (obj && *obj->program) {
				if ((int)ShellExecuteU8(NULL, NULL, obj->program, url_ptr ? url_ptr : u8buf, NULL, SW_SHOW) <= WINEXEC_ERR_MAX)
					MessageBoxU8(obj->program, GetLoadStrU8(IDS_CANTEXEC), MB_OK|MB_ICONINFORMATION);
			}
			else if (!url_ptr && cfg->ShellExec || url_ptr && cfg->DefaultUrl) {
				ShellExecuteU8(NULL, NULL, url_ptr ? url_ptr : u8buf, NULL, NULL, SW_SHOW);
			}
			delete [] u8buf;
			delete	[] wbuf;
		}
		return	TRUE;
	}
	return	FALSE;
}

BOOL TEditSub::SetFont(LOGFONT	*lf, BOOL dualFont)
{
	CHARFORMAT	cf;
	memset(&cf, 0, sizeof(cf));
	cf.cbSize = sizeof(cf);
	SendMessage(EM_GETCHARFORMAT, 0, (LPARAM)&cf);
//	cf.dwMask |= CFM_BOLD|CFM_ITALIC|CFM_UNDERLINE|CFM_STRIKEOUT|CFM_PROTECTED|CFM_SIZE|CFM_COLOR|CFM_FACE|CFM_OFFSET|CFM_CHARSET;
	cf.dwEffects |= (lf->lfItalic ? CFE_ITALIC : 0) | (lf->lfUnderline ? CFE_UNDERLINE : 0) | (lf->lfStrikeOut ? CFE_STRIKEOUT : 0);

	HDC hDc = ::GetDC(hWnd);
	cf.yHeight = abs(1440 * lf->lfHeight / ::GetDeviceCaps(hDc, LOGPIXELSY));
	::ReleaseDC(hWnd, hDc);

	cf.bCharSet = lf->lfCharSet;
	cf.bPitchAndFamily = lf->lfPitchAndFamily;
	strcpy(cf.szFaceName, lf->lfFaceName);
	SendMessage(EM_SETCHARFORMAT, 0, (LPARAM)&cf);

	DWORD	langOpts = SendMessage(EM_GETLANGOPTIONS, 0, 0);
	langOpts = dualFont ? (langOpts | IMF_DUALFONT) : (langOpts & ~IMF_DUALFONT);
	SendMessage(EM_SETLANGOPTIONS, 0, langOpts);
	return	TRUE;
}

int TEditSub::ExGetText(void *buf, int max_len, DWORD flags, UINT codepage)
{
	GETTEXTEX	ge;

	memset(&ge, 0, sizeof(ge));
	ge.cb = max_len;
	ge.flags = flags;
	ge.codepage = codepage;

	return	SendMessageW(EM_GETTEXTEX, (WPARAM)&ge, (LPARAM)buf);
}

int TEditSub::ExSetText(const void *buf, int max_len, DWORD flags, UINT codepage)
{
	SETTEXTEX	se;

	se.flags = flags;
	se.codepage = codepage;

	return	SendMessageW(EM_SETTEXTEX, (WPARAM)&se, (LPARAM)buf);
}

/*
	static control の subclass化
*/
TSeparateSub::TSeparateSub(TWin *_parent) : TSubClassCtl(_parent)
{
	hCursor = ::LoadCursor(NULL, IDC_SIZENS);
}

BOOL TSeparateSub::EvSetCursor(HWND cursorWnd, WORD nHitTest, WORD wMouseMsg)
{
	::SetCursor(hCursor);
	return	TRUE;
}

BOOL TSeparateSub::EvNcHitTest(POINTS pos, LRESULT *result)
{
	*result = HTCLIENT;
	return	TRUE;	// きちんとイベントを飛ばすため(win3.1/nt3.51)
}

BOOL TSeparateSub::EventButton(UINT uMsg, int nHitTest, POINTS pos)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		parent->SendMessage(WM_SENDDLG_RESIZE, 0, 0);
		return	TRUE;
	}
	return	FALSE;
}


/*
	不在通知文設定ダイアログ
*/
extern char	*DefaultAbsence[], *DefaultAbsenceHead[];

TAbsenceDlg::TAbsenceDlg(Cfg *_cfg, TWin *_parent) : TDlg(ABSENCE_DIALOG, _parent)
{
	cfg = _cfg;
	hAccel = ::LoadAccelerators(TApp::GetInstance(), (LPCSTR)IPMSG_ACCEL);
}

TAbsenceDlg::~TAbsenceDlg()
{
}

BOOL TAbsenceDlg::EvCreate(LPARAM lParam)
{
	SetDlgIcon(hWnd);

	if (rect.left == CW_USEDEFAULT)
	{
		DWORD	val = GetMessagePos();
		POINTS	pos = MAKEPOINTS(val);

		GetWindowRect(&rect);
		int cx = ::GetSystemMetrics(SM_CXFULLSCREEN), cy = ::GetSystemMetrics(SM_CYFULLSCREEN);
		int xsize = rect.right - rect.left, ysize = rect.bottom - rect.top;
		int x = pos.x - xsize / 2, y = pos.y - ysize;

		if (x + xsize > cx)
			x = cx - xsize;
		if (y + ysize > cy)
			y = cy - ysize;

		MoveWindow(x > 0 ? x : 0, y > 0 ? y : 0, xsize, ysize, FALSE);
	}
	else
		MoveWindow(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, FALSE);

	typedef char MaxBuf[MAX_PATH_U8];
	typedef char MaxHead[MAX_NAMEBUF];
	tmpAbsenceStr = new MaxBuf[cfg->AbsenceMax];
	tmpAbsenceHead = new MaxHead[cfg->AbsenceMax];

	SetData();
	return	TRUE;
}

BOOL TAbsenceDlg::EvNcDestroy(void)
{
	delete [] tmpAbsenceHead;
	delete [] tmpAbsenceStr;
	return	TRUE;
}

BOOL TAbsenceDlg::EvCommand(WORD wNotifyCode, WORD wID, LPARAM hWndCtl)
{
	switch (wID)
	{
	case IDOK:
		GetData();
		cfg->WriteRegistry(CFG_ABSENCE);
		cfg->AbsenceCheck = FALSE;
		::PostMessage(GetMainWnd(), WM_COMMAND, MENU_ABSENCE, 0);
		EndDialog(TRUE);
		return	TRUE;

	case SET_BUTTON:
		GetData();
		cfg->WriteRegistry(CFG_ABSENCE);
		if (cfg->AbsenceCheck)
		{
			cfg->AbsenceCheck = FALSE;
			::PostMessage(GetMainWnd(), WM_COMMAND, MENU_ABSENCE, 0);
		}
		EndDialog(FALSE);
		return	TRUE;

	case IDCANCEL:
		EndDialog(FALSE);
		return	TRUE;

	case ABSENCEINIT_BUTTON:
		SetDlgItemTextU8(ABSENCEHEAD_EDIT, DefaultAbsenceHead[currentChoice]);
		SetDlgItemTextU8(ABSENCE_EDIT, DefaultAbsence[currentChoice]);
		return	TRUE;

	case HIDE_ACCEL:
		::PostMessage(GetMainWnd(), WM_HIDE_CHILDWIN, 0, 0);
		return	TRUE;

	case ABSENCE_LIST:
		if (wNotifyCode == LBN_SELCHANGE)
		{
			int		index;

			if ((index = (int)SendDlgItemMessage(ABSENCE_LIST, LB_GETCURSEL, 0, 0)) != LB_ERR)
			{
				char	oldAbsenceHead[MAX_NAMEBUF];
				strcpy(oldAbsenceHead, tmpAbsenceHead[currentChoice]);
				GetDlgItemTextU8(ABSENCEHEAD_EDIT, tmpAbsenceHead[currentChoice], MAX_NAMEBUF);
				GetDlgItemTextU8(ABSENCE_EDIT, tmpAbsenceStr[currentChoice], MAX_PATH_U8);
				if (strcmp(oldAbsenceHead, tmpAbsenceHead[currentChoice]))
				{
					SendDlgItemMessage(ABSENCE_LIST, LB_DELETESTRING, currentChoice, 0);
					Wstr	head_w(tmpAbsenceHead[currentChoice], BY_UTF8);
					SendDlgItemMessageW(ABSENCE_LIST, LB_INSERTSTRING, currentChoice, (LPARAM)head_w.Buf());
					if (currentChoice == index)
					{
						SendDlgItemMessage(ABSENCE_LIST, LB_SETCURSEL, currentChoice, 0);
						return	TRUE;
					}
				}
				currentChoice = index;
				PostMessage(WM_DELAYSETTEXT, 0, 0);
			}
		}
		else if (wNotifyCode == LBN_DBLCLK)
			PostMessage(WM_COMMAND, IDOK, 0);
		return	TRUE;
	}

	return	FALSE;
}

/*
	User定義 Event CallBack
*/
BOOL TAbsenceDlg::EventUser(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DELAYSETTEXT:
		{
			int		len = strlen(tmpAbsenceStr[currentChoice]);

			SetDlgItemTextU8(ABSENCEHEAD_EDIT, tmpAbsenceHead[currentChoice]);
			SetDlgItemTextU8(ABSENCE_EDIT, tmpAbsenceStr[currentChoice]);
			SendDlgItemMessage(ABSENCE_EDIT, EM_SETSEL, (WPARAM)len, (LPARAM)len);
		}
		return	TRUE;
	}

	return	FALSE;
}

void TAbsenceDlg::SetData(void)
{
	for (int cnt=0; cnt < cfg->AbsenceMax; cnt++)
	{
		strcpy(tmpAbsenceHead[cnt], cfg->AbsenceHead[cnt]);
		strcpy(tmpAbsenceStr[cnt], cfg->AbsenceStr[cnt]);
		Wstr	head_w(cfg->AbsenceHead[cnt], BY_UTF8);
		SendDlgItemMessageW(ABSENCE_LIST, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)head_w.Buf());
	}
	currentChoice = cfg->AbsenceChoice;
	PostMessage(WM_DELAYSETTEXT, 0, 0);
	SendDlgItemMessage(ABSENCE_LIST, LB_SETCURSEL, currentChoice, 0);
}

void TAbsenceDlg::GetData(void)
{
	GetDlgItemTextU8(ABSENCEHEAD_EDIT, tmpAbsenceHead[currentChoice], MAX_NAMEBUF);
	GetDlgItemTextU8(ABSENCE_EDIT, tmpAbsenceStr[currentChoice], MAX_PATH_U8);
	for (int cnt=0; cnt < cfg->AbsenceMax; cnt++)
	{
		strcpy(cfg->AbsenceHead[cnt], tmpAbsenceHead[cnt]);
		strcpy(cfg->AbsenceStr[cnt], tmpAbsenceStr[cnt]);
	}
	cfg->AbsenceChoice = currentChoice;
}


/*
	ソート設定ダイアログ
*/
TSortDlg *TSortDlg::exclusiveWnd = NULL;

TSortDlg::TSortDlg(Cfg *_cfg, TWin *_parent) : TDlg(SORT_DIALOG, _parent)
{
	cfg = _cfg;
}

int TSortDlg::Exec(void)
{
	if (exclusiveWnd)
		return	exclusiveWnd->SetForegroundWindow(), FALSE;

	exclusiveWnd = this;
	return	TDlg::Exec();
}

BOOL TSortDlg::EvCommand(WORD wNotifyCode, WORD wID, LPARAM hWndCtl)
{
	switch (wID)
	{
	case IDOK: case SET_BUTTON:
		GetData();
		cfg->WriteRegistry(CFG_GENERAL);
		if (wID == IDOK)
			EndDialog(TRUE), exclusiveWnd = NULL;
		return	TRUE;

	case IDCANCEL:
		EndDialog(FALSE);
		exclusiveWnd = NULL;
		return	TRUE;
	}

	return	FALSE;
}

BOOL TSortDlg::EvCreate(LPARAM lParam)
{
	GetWindowRect(&rect);
	int cx = ::GetSystemMetrics(SM_CXFULLSCREEN), cy = ::GetSystemMetrics(SM_CYFULLSCREEN);
	int x = rect.left + 50, y = rect.top + 20;
	int xsize = rect.right - rect.left, ysize = rect.bottom - rect.top;
	if (x + xsize > cx)
		x = cx - xsize;
	if (y + ysize > cy)
		y = cy - ysize;

	MoveWindow(x, y, xsize, ysize, FALSE);
	SetData();

	return	TRUE;
}

void TSortDlg::SetData(void)
{
	SendDlgItemMessage(GROUPDISP_CHECK, BM_SETCHECK, GetItem(cfg->ColumnItems, SW_GROUP), 0);
	SendDlgItemMessage(HOST_CHECK, BM_SETCHECK, GetItem(cfg->ColumnItems, SW_HOST), 0);
	SendDlgItemMessage(LOGON_CHECK, BM_SETCHECK, GetItem(cfg->ColumnItems, SW_USER), 0);
	SendDlgItemMessage(PRIORITY_CHECK, BM_SETCHECK, GetItem(cfg->ColumnItems, SW_PRIORITY), 0);
	SendDlgItemMessage(IPADDR_CHECK, BM_SETCHECK, GetItem(cfg->ColumnItems, SW_IPADDR), 0);
	SendDlgItemMessage(GLIDLINE_CHECK, BM_SETCHECK, cfg->GlidLineCheck, 0);

	SendDlgItemMessage(GROUP_CHECK, BM_SETCHECK, !(cfg->Sort & IPMSG_NOGROUPSORTOPT), 0);
	SendDlgItemMessage(GROUPREV_CHECK, BM_SETCHECK, (cfg->Sort & IPMSG_GROUPREVSORTOPT) != 0, 0);
	SendDlgItemMessage(USER_RADIO, BM_SETCHECK, GET_MODE(cfg->Sort) == IPMSG_NAMESORT, 0);
	SendDlgItemMessage(HOST_RADIO, BM_SETCHECK, GET_MODE(cfg->Sort) == IPMSG_HOSTSORT, 0);
	SendDlgItemMessage(IPADDR_RADIO, BM_SETCHECK, GET_MODE(cfg->Sort) == IPMSG_IPADDRSORT, 0);
	SendDlgItemMessage(SUBREV_CHECK, BM_SETCHECK, (cfg->Sort & IPMSG_SUBREVSORTOPT) != 0, 0);
	SendDlgItemMessage(ICMP_CHECK, BM_SETCHECK, (cfg->Sort & IPMSG_ICMPSORTOPT) != 0, 0);
	SendDlgItemMessage(KANJI_CHECK, BM_SETCHECK, !(cfg->Sort & IPMSG_NOKANJISORTOPT), 0);
}

void TSortDlg::GetData(void)
{
	SetItem(&cfg->ColumnItems, SW_GROUP, SendDlgItemMessage(GROUPDISP_CHECK, BM_GETCHECK, 0, 0));
	SetItem(&cfg->ColumnItems, SW_HOST, SendDlgItemMessage(HOST_CHECK, BM_GETCHECK, 0, 0));
	SetItem(&cfg->ColumnItems, SW_USER, SendDlgItemMessage(LOGON_CHECK, BM_GETCHECK, 0, 0));
	SetItem(&cfg->ColumnItems, SW_PRIORITY, SendDlgItemMessage(PRIORITY_CHECK, BM_GETCHECK, 0, 0));
	SetItem(&cfg->ColumnItems, SW_IPADDR, SendDlgItemMessage(IPADDR_CHECK, BM_GETCHECK, 0, 0));
	cfg->GlidLineCheck = SendDlgItemMessage(GLIDLINE_CHECK, BM_GETCHECK, 0, 0);

	cfg->Sort = 0;

	if (SendDlgItemMessage(GROUP_CHECK, BM_GETCHECK, 0, 0) == 0)
		cfg->Sort |= IPMSG_NOGROUPSORTOPT;
	if (SendDlgItemMessage(GROUPREV_CHECK, BM_GETCHECK, 0, 0))
		cfg->Sort |= IPMSG_GROUPREVSORTOPT;
	if (SendDlgItemMessage(USER_RADIO, BM_GETCHECK, 0, 0))
		cfg->Sort |= IPMSG_NAMESORT;
	if (SendDlgItemMessage(HOST_RADIO, BM_GETCHECK, 0, 0))
		cfg->Sort |= IPMSG_HOSTSORT;
	if (SendDlgItemMessage(IPADDR_RADIO, BM_GETCHECK, 0, 0))
		cfg->Sort |= IPMSG_IPADDRSORT;
	if (SendDlgItemMessage(SUBREV_CHECK, BM_GETCHECK, 0, 0))
		cfg->Sort |= IPMSG_SUBREVSORTOPT;
	if (SendDlgItemMessage(ICMP_CHECK, BM_GETCHECK, 0, 0))
		cfg->Sort |= IPMSG_ICMPSORTOPT;
	if (SendDlgItemMessage(KANJI_CHECK, BM_GETCHECK, 0, 0) == 0)
		cfg->Sort |= IPMSG_NOKANJISORTOPT;
}

/*
	クリッカブルURL設定ダイアログ
*/
TUrlDlg::TUrlDlg(Cfg *_cfg, TWin *_parent) : TDlg(URL_DIALOG, _parent)
{
	cfg = _cfg;
	*currentProtocol = 0;
}

TUrlDlg::~TUrlDlg()
{
}

BOOL TUrlDlg::EvCreate(LPARAM lParam)
{
	GetWindowRect(&rect);
	int cx = ::GetSystemMetrics(SM_CXFULLSCREEN), cy = ::GetSystemMetrics(SM_CYFULLSCREEN);
	int x = rect.left + 10, y = rect.top + 50;
	int xsize = rect.right - rect.left, ysize = rect.bottom - rect.top;
	if (x + xsize > cx)
		x = cx - xsize;
	if (y + ysize > cy)
		y = cy - ysize;

	MoveWindow(x, y, xsize, ysize, FALSE);
	SetData();
	SendDlgItemMessage(URL_LIST, LB_SETCURSEL, 0, 0);
	EvCommand(0, URL_LIST, 0);

	return	TRUE;
}

BOOL TUrlDlg::EvNcDestroy(void)
{
	UrlObj *urlObj;

	while ((urlObj = (UrlObj *)tmpUrlList.TopObj()) != NULL)
	{
		tmpUrlList.DelObj(urlObj);
		delete urlObj;
	}
	return	TRUE;
}

BOOL TUrlDlg::EvCommand(WORD wNotifyCode, WORD wID, LPARAM hWndCtl)
{
	switch (wID)
	{
	case IDOK: case SET_BUTTON:
		GetData();
		cfg->WriteRegistry(CFG_CLICKURL);
		if (wID == IDOK)
			EndDialog(TRUE);
		return	TRUE;

	case IDCANCEL:
		EndDialog(FALSE);
		return	TRUE;

	case ADD_BUTTON:
		{
			char	protocol[MAX_LISTBUF], buf[MAX_LISTBUF];
			int		index;
			UrlObj	*obj;

			if ((index = (int)SendDlgItemMessage(URL_LIST, LB_GETCURSEL, 0, 0)) != LB_ERR && SendDlgItemMessage(URL_LIST, LB_GETTEXT, (WPARAM)index, (LPARAM)protocol) != LB_ERR && (obj = SearchUrlObj(&tmpUrlList, protocol)) != NULL)
			{
				wsprintf(buf, GetLoadStrU8(IDS_EXECPROGRAM), protocol);
				OpenFileDlg(this).Exec(URL_EDIT, buf, GetLoadStrAsFilter(IDS_OPENFILEPRGFLTR));
			}
		}
		return	TRUE;

	case URL_LIST:
		{
			char	protocol[MAX_LISTBUF];
			int		index;
			UrlObj	*obj;

			if ((index = (int)SendDlgItemMessage(URL_LIST, LB_GETCURSEL, 0, 0)) != LB_ERR && SendDlgItemMessage(URL_LIST, LB_GETTEXT, (WPARAM)index, (LPARAM)protocol) != LB_ERR && (obj = SearchUrlObj(&tmpUrlList, protocol)) != NULL)
			{
				SetCurrentData();
				SetDlgItemTextU8(URL_EDIT, obj->program);
				strncpyz(currentProtocol, protocol, sizeof(currentProtocol));
			}
		}
		return	TRUE;
	}

	return	FALSE;
}

void TUrlDlg::SetCurrentData(void)
{
	UrlObj	*obj;

	if ((obj = SearchUrlObj(&tmpUrlList, currentProtocol)) != NULL)
		GetDlgItemTextU8(URL_EDIT, obj->program, sizeof(obj->program));
}

void TUrlDlg::SetData(void)
{
	for (UrlObj *obj = (UrlObj *)cfg->urlList.TopObj(); obj != NULL; obj = (UrlObj *)cfg->urlList.NextObj(obj))
	{
		UrlObj *tmp_obj = new UrlObj;
		strcpy(tmp_obj->protocol, obj->protocol);
		strcpy(tmp_obj->program, obj->program);
		tmpUrlList.AddObj(tmp_obj);

		SendDlgItemMessage(URL_LIST, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)obj->protocol);
	}
	SendDlgItemMessage(DEFAULTURL_CHECK, BM_SETCHECK, cfg->DefaultUrl, 0);
	SendDlgItemMessage(SHELLEXEC_CHECK, BM_SETCHECK, cfg->ShellExec, 0);
}

void TUrlDlg::GetData(void)
{
	SetCurrentData();

	for (UrlObj *tmp_obj = (UrlObj *)tmpUrlList.TopObj(); tmp_obj != NULL; tmp_obj = (UrlObj *)tmpUrlList.NextObj(tmp_obj))
	{
		UrlObj *obj = SearchUrlObj(&cfg->urlList, tmp_obj->protocol);

		if (obj == NULL)
		{
			obj = new UrlObj;
			cfg->urlList.AddObj(obj);
			strcpy(obj->protocol, tmp_obj->protocol);
		}
		strcpy(obj->program, tmp_obj->program);
	}
	cfg->DefaultUrl = (int)SendDlgItemMessage(DEFAULTURL_CHECK, BM_GETCHECK, 0, 0);
	cfg->ShellExec = (int)SendDlgItemMessage(SHELLEXEC_CHECK, BM_GETCHECK, 0, 0);
}


// パスワード確認用
TPasswordDlg::TPasswordDlg(Cfg *_cfg, TWin *_parent) : TDlg(PASSWORD_DIALOG, _parent)
{
	cfg = _cfg;
	outbuf = NULL;
}

// 単なるパスワード入力用
TPasswordDlg::TPasswordDlg(char *_outbuf, TWin *_parent) : TDlg(PASSWORD_DIALOG, _parent)
{
	cfg = NULL;
	outbuf = _outbuf;
}

BOOL TPasswordDlg::EvCommand(WORD wNotifyCode, WORD wID, LPARAM hWndCtl)
{
	switch (wID)
	{
	case IDOK:
		{
			char	_buf[MAX_NAMEBUF];
			char	*buf = outbuf ? outbuf : _buf;

			GetDlgItemTextU8(PASSWORD_EDIT, buf, MAX_NAMEBUF);
			if (cfg)
			{
				if (CheckPassword(cfg->PasswordStr, buf))
					EndDialog(TRUE);
				else
					SetDlgItemTextU8(PASSWORD_EDIT, ""), MessageBoxU8(GetLoadStrU8(IDS_CANTAUTH));
			}
			else EndDialog(TRUE);
		}
		return	TRUE;

	case IDCANCEL:
		EndDialog(FALSE);
		return	TRUE;
	}
	return	FALSE;
}

BOOL TPasswordDlg::EvCreate(LPARAM lParam)
{
	GetWindowRect(&rect);
	if (parent)
		MoveWindow(rect.left +100, rect.top +100, rect.right - rect.left, rect.bottom - rect.top, FALSE);
	else
	{
		GetWindowRect(&rect);
		int xsize = rect.right - rect.left, ysize = rect.bottom - rect.top;
		int	x = (::GetSystemMetrics(SM_CXFULLSCREEN) - xsize)/2;
		int y = (::GetSystemMetrics(SM_CYFULLSCREEN) - ysize)/2;
		MoveWindow(x, y, xsize, ysize, FALSE);
	}

	return	TRUE;
}

TPasswdChangeDlg::TPasswdChangeDlg(Cfg *_cfg, TWin *_parent) : TDlg(PASSWDCHANGE_DIALOG, _parent)
{
	cfg = _cfg;
}

BOOL TPasswdChangeDlg::EvCommand(WORD wNotifyCode, WORD wID, LPARAM hWndCtl)
{
	switch (wID)
	{
	case IDOK:
		char	buf[MAX_NAMEBUF], buf2[MAX_NAMEBUF];

		GetDlgItemTextU8(OLDPASSWORD_EDIT, buf, sizeof(buf));
		if (CheckPassword(cfg->PasswordStr, buf))
		{
			GetDlgItemTextU8(NEWPASSWORD_EDIT, buf, sizeof(buf));
			GetDlgItemTextU8(NEWPASSWORD_EDIT2, buf2, sizeof(buf2));
			if (strcmp(buf, buf2) == 0)
				MakePassword(buf, cfg->PasswordStr);
			else
				return	MessageBoxU8(GetLoadStrU8(IDS_NOTSAMEPASS)), TRUE;
			cfg->WriteRegistry(CFG_GENERAL);
			EndDialog(TRUE);
		}
		else
			SetDlgItemTextU8(PASSWORD_EDIT, ""), MessageBoxU8(GetLoadStrU8(IDS_CANTAUTH));
		return	TRUE;

	case IDCANCEL:
		EndDialog(FALSE);
		return	TRUE;
	}
	return	FALSE;
}

BOOL TPasswdChangeDlg::EvCreate(LPARAM lParam)
{
	GetWindowRect(&rect);
	MoveWindow(rect.left +50, rect.top +100, rect.right - rect.left, rect.bottom - rect.top, FALSE);

	if (*cfg->PasswordStr == 0)
		::EnableWindow(GetDlgItem(OLDPASSWORD_EDIT), FALSE);

	return	TRUE;
}


BOOL CheckPassword(const char *cfgPasswd, const char *inputPasswd)
{
	char	buf[MAX_NAMEBUF];

	MakePassword(inputPasswd, buf);

	return	strcmp(buf, cfgPasswd) == 0 ? TRUE : FALSE;
}

void MakePassword(const char *inputPasswd, char *outputPasswd)
{
	while (*inputPasswd)	// 可逆だぞ...DESライブラリがあればいいのに
		*outputPasswd++ = ((~*inputPasswd++) & 0x7f); //レジストリのストリング型は８ビット目を嫌う(;_;)

	*outputPasswd = 0;
}


/*
	URL検索ルーチン
*/
UrlObj *SearchUrlObj(TList *list, char *protocol)
{
	for (UrlObj *obj = (UrlObj *)list->TopObj(); obj != NULL; obj = (UrlObj *)list->NextObj(obj))
		if (stricmp(obj->protocol, protocol) == 0)
			return	obj;

	return	NULL;
}

/*
	ダイアログ用アイコン設定
*/
void SetDlgIcon(HWND hWnd)
{
	static HICON	oldHIcon = NULL;

	if (oldHIcon != TMainWin::GetIPMsgIcon())
	{
		oldHIcon = TMainWin::GetIPMsgIcon();
		::SetClassLong(hWnd, GCL_HICON, (LONG)oldHIcon);
	}
}

/*
	ログ記録用の HostEntry表示文字列
*/
void MakeListString(Cfg *cfg, HostSub *hostSub, THosts *hosts, char *buf)
{
	Host	*host;

	if ((host = hosts->GetHostByAddr(hostSub)) && IsSameHost(hostSub, &host->hostSub)
		/* || (host = cfg->priorityHosts.GetHostByName(hostSub)) != NULL */)
		MakeListString(cfg, host, buf);
	else {
		Host	host;

		memset(&host, 0, sizeof(host));
		host.hostSub = *hostSub;
		MakeListString(cfg, &host, buf);
	}
}

/*
	ログ記録用の HostEntry表示文字列
*/
void MakeListString(Cfg *cfg, Host *host, char *buf)
{
	char	*fmt = "%s ";

	if (*host->nickName)
	{
		if (cfg->NickNameCheck == IPMSG_NICKNAME)
			buf += wsprintf(buf, fmt, host->nickName);
		else {
			char	tmp_name[MAX_LISTBUF];
			wsprintf(tmp_name, "%s[%s]", host->nickName, host->hostSub.userName);
			buf += wsprintf(buf, fmt, tmp_name);
		}
	}
	else
		buf += wsprintf(buf, fmt, host->hostSub.userName);

	if (host->hostStatus & IPMSG_ABSENCEOPT)
		*buf++ = '*';

	buf += wsprintf(buf, "(%s%s%s", host->groupName, *host->groupName ? "/":"", host->hostSub.hostName);

	if (cfg->IPAddrCheck)
		buf += wsprintf(buf, "/%s", inet_ntoa(*(LPIN_ADDR)&host->hostSub.addr));

	strcpy(buf, ")");
}

/*
	IME 制御
*/
BOOL SetImeOpenStatus(HWND hWnd, BOOL flg)
{
	BOOL ret = FALSE;

	HIMC hImc;

	if ((hImc = ImmGetContext(hWnd)) != NULL)
	{
		ret = ImmSetOpenStatus(hImc, flg);
		ImmReleaseContext(hWnd, hImc);
	}
	return	ret;
}

BOOL GetImeOpenStatus(HWND hWnd)
{
	BOOL ret = FALSE;

	HIMC hImc;

	if ((hImc = ImmGetContext(hWnd)) != NULL)
	{
		ret = ImmGetOpenStatus(hImc);
		ImmReleaseContext(hWnd, hImc);
	}
	return	ret;
}

/*
	ホットキー設定
*/
BOOL SetHotKey(Cfg *cfg)
{
	if (cfg->HotKeyCheck)
	{
		RegisterHotKey(GetMainWnd(), WM_SENDDLG_OPEN, cfg->HotKeyModify, cfg->HotKeySend);
		RegisterHotKey(GetMainWnd(), WM_RECVDLG_OPEN, cfg->HotKeyModify, cfg->HotKeyRecv);
		RegisterHotKey(GetMainWnd(), WM_DELMISCDLG, cfg->HotKeyModify, cfg->HotKeyMisc);
	}
	else {
		UnregisterHotKey(GetMainWnd(), WM_SENDDLG_OPEN);
		UnregisterHotKey(GetMainWnd(), WM_RECVDLG_OPEN);
		UnregisterHotKey(GetMainWnd(), WM_DELMISCDLG);
	}
	return	TRUE;
}

/*
	Host1 と Host2 が同一かどうかを比較
*/
BOOL IsSameHost(HostSub *hostSub1, HostSub *hostSub2)
{
	if (stricmp(hostSub1->hostName, hostSub2->hostName))
		return	FALSE;

	return	stricmp(hostSub1->userName, hostSub2->userName) ? FALSE : TRUE;
}

/*
	RECT -> WINPOS
*/
void RectToWinPos(const RECT *rect, WINPOS *wpos)
{
	wpos->x = rect->left, wpos->y = rect->top;
	wpos->cx = rect->right - rect->left;
	wpos->cy = rect->bottom - rect->top;
}

/*
	host array class
*/
THosts::THosts(void)
{
	hostCnt = 0;
	memset(array, 0, sizeof(array));
	for (int kind=0; kind < MAX_ARRAY; kind++)
		enable[kind] = FALSE;
}

THosts::~THosts()
{
	for (int kind=0; kind < MAX_ARRAY; kind++) {
		if (array[kind])
			free(array[kind]);
	}
}


int THosts::Cmp(HostSub *hostSub1, HostSub *hostSub2, Kind kind)
{
	switch (kind) {
	case NAME: case NAME_ADDR:
		{
			int	cmp;
			if (cmp = stricmp(hostSub1->userName, hostSub2->userName))
				return	cmp;
			if ((cmp = stricmp(hostSub1->hostName, hostSub2->hostName)) || kind == NAME)
				return	cmp;
		}	// if cmp == 0 && kind == NAME_ADDR, through...
	case ADDR:
		if (hostSub1->addr > hostSub2->addr)
			return	1;
		if (hostSub1->addr < hostSub2->addr)
			return	-1;
		if (hostSub1->portNo > hostSub2->portNo)
			return	1;
		if (hostSub1->portNo < hostSub2->portNo)
			return	-1;
		return	0;
	}
	return	-1;
}

Host *THosts::Search(Kind kind, HostSub *hostSub, int *insertIndex)
{
	int	min = 0, max = hostCnt -1, cmp, tmpIndex;

	if (insertIndex == NULL)
		insertIndex = &tmpIndex;

	while (min <= max)
	{
		*insertIndex = (min + max) / 2;

		if ((cmp = Cmp(hostSub, &array[kind][*insertIndex]->hostSub, kind)) == 0)
			return	array[kind][*insertIndex];
		else if (cmp > 0)
			min = *insertIndex +1;
		else
			max = *insertIndex -1;
	}

	*insertIndex = min;
	return	NULL;
}

BOOL THosts::AddHost(Host *host)
{
	int		insertIndex[MAX_ARRAY], kind;

// すべてのインデックス種類での確認を先に行う
	for (kind=0; kind < MAX_ARRAY; kind++) {
		if (enable[kind] == FALSE)
			continue;
		if (Search((Kind)kind, &host->hostSub, &insertIndex[kind]) != NULL)
			return	FALSE;
	}

#define BIG_ALLOC	100
	for (kind=0; kind < MAX_ARRAY; kind++) {
		if (enable[kind] == FALSE)
			continue;
		if ((hostCnt % BIG_ALLOC) == 0)
		{
			Host	**tmpArray = (Host **)realloc(array[kind], (hostCnt + BIG_ALLOC) * sizeof(Host *));
			if (tmpArray == NULL)
				return	FALSE;
			array[kind] = tmpArray;
		}
		memmove(array[kind] + insertIndex[kind] + 1, array[kind] + insertIndex[kind], (hostCnt - insertIndex[kind]) * sizeof(Host *));
		array[kind][insertIndex[kind]] = host;
	}
	host->RefCnt(1);
	hostCnt++;
	return	TRUE;
}

BOOL THosts::DelHost(Host *host)
{
	int		insertIndex[MAX_ARRAY], kind;

// すべてのインデックス種類での確認を先に行う
	for (kind=0; kind < MAX_ARRAY; kind++) {
		if (enable[kind] == FALSE)
			continue;
		if (Search((Kind)kind, &host->hostSub, &insertIndex[kind]) == NULL)
			return	FALSE;
	}

	hostCnt--;

	for (kind=0; kind < MAX_ARRAY; kind++) {
		if (enable[kind] == FALSE)
			continue;
		memmove(array[kind] + insertIndex[kind], array[kind] + insertIndex[kind] + 1, (hostCnt - insertIndex[kind]) * sizeof(Host *));
	}
	host->RefCnt(-1);

	return	TRUE;
}

BOOL THosts::PriorityHostCnt(int priority, int range)
{
	int		member = 0;

	for (int cnt=0; cnt < hostCnt; cnt++)
		if (array[NAME][cnt]->priority >= priority && array[NAME][cnt]->priority < priority + range)
			member++;
	return	member;
}

TFindDlg::TFindDlg(Cfg *_cfg, TSendDlg *_parent) : TDlg(FIND_DIALOG, _parent)
{
	cfg = _cfg;
	sendDlg = _parent;
}

BOOL TFindDlg::EvCommand(WORD wNotifyCode, WORD wID, LPARAM hWndCtl)
{
	switch (wID)
	{
	case IDOK:
		int		cnt;
		GetDlgItemTextU8(FIND_COMBO, cfg->FindStr[0], MAX_NAMEBUF);
		cfg->FindAll = SendDlgItemMessage(ALLFIND_CHECK, BM_GETCHECK, 0, 0);

		if (sendDlg->FindHost(cfg->FindStr[0], cfg->FindAll)) {
			for (cnt=1; cnt < cfg->FindMax; cnt++)
				if (stricmp(cfg->FindStr[cnt], cfg->FindStr[0]) == 0)
					break;
			memmove(cfg->FindStr[2], cfg->FindStr[1], (cnt == cfg->FindMax ? cnt-2 : cnt-1) * MAX_NAMEBUF);
			memcpy(cfg->FindStr[1], cfg->FindStr[0], MAX_NAMEBUF);
			DWORD	start, end;		// エディット部の選択状態の保存
			SendDlgItemMessage(FIND_COMBO, CB_GETEDITSEL, (WPARAM)&start, (LPARAM)&end);
			// CB_RESETCONTENT でエディット部がクリア
			// なお、DELETESTRING でも edit 同名stringの場合、同じくクリアされる
			SendDlgItemMessage(FIND_COMBO, CB_RESETCONTENT, 0, 0);
			for (cnt=1; cnt < cfg->FindMax && cfg->FindStr[cnt][0]; cnt++) {
				Wstr	find_w(cfg->FindStr[cnt], BY_UTF8);
				SendDlgItemMessageW(FIND_COMBO, CB_INSERTSTRING, cnt-1, (LPARAM)find_w.Buf());
			}
			SetDlgItemTextU8(FIND_COMBO, cfg->FindStr[0]);
			SendDlgItemMessage(FIND_COMBO, CB_SETEDITSEL, 0, MAKELPARAM(start, end));
		}
		cfg->WriteRegistry(CFG_FINDHIST);
		return	TRUE;

	case IDCANCEL: case CLOSE_BUTTON:
		EndDialog(FALSE);
		return	TRUE;
	}

	return	FALSE;
}

BOOL TFindDlg::EvCreate(LPARAM lParam)
{
	SendDlgItemMessage(ALLFIND_CHECK, BM_SETCHECK, cfg->FindAll, 0);

	for (int cnt=1; cnt < cfg->FindMax && cfg->FindStr[cnt][0]; cnt++) {
		Wstr	find_w(cfg->FindStr[cnt], BY_UTF8);
		SendDlgItemMessageW(FIND_COMBO, CB_INSERTSTRING, (WPARAM)cnt-1, (LPARAM)find_w.Buf());
	}
	if (cfg->FindStr[0][0])
		SetDlgItemTextU8(FIND_COMBO, cfg->FindStr[0]);

	if (rect.left == CW_USEDEFAULT) {
		GetWindowRect(&rect);
		rect.left += 140;
		rect.right += 140;
		rect.top -= 20;
		rect.bottom -= 20;
	}
	MoveWindow(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, FALSE);
	Show();
	return	TRUE;
}

/*
	ファイルダイアログ用汎用ルーチン
*/
BOOL OpenFileDlg::Exec(UINT editCtl, char *title, char *filter, char *defaultDir)
{
	char buf[MAX_PATH_U8];

	if (parent == NULL)
		return FALSE;

	parent->GetDlgItemTextU8(editCtl, buf, sizeof(buf));

	if (Exec(buf, title, filter, defaultDir) == FALSE)
		return	FALSE;

	parent->SetDlgItemTextU8(editCtl, buf);
	return	TRUE;
}

BOOL OpenFileDlg::Exec(char *target, char *title, char *filter, char *defaultDir)
{
	OPENFILENAME	ofn;
	char			szDirName[MAX_BUF_EX] = "", szFile[MAX_BUF_EX] = "", *fname = NULL;

	if (*target && GetFullPathNameU8(target, MAX_BUF, szDirName, &fname) != 0 && fname)
		*(fname -1) = 0, strncpyz(szFile, fname, MAX_PATH_U8);
	else if (defaultDir)
		strncpyz(szDirName, defaultDir, MAX_PATH_U8);

	memset(&ofn, 0, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = parent ? parent->hWnd : NULL;
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = filter ? 1 : 0;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrTitle = title;
	ofn.lpstrInitialDir = szDirName;
	ofn.lpfnHook = hook;
	ofn.Flags = OFN_HIDEREADONLY|OFN_EXPLORER|(hook ? OFN_ENABLEHOOK : 0);
	if (mode == OPEN || mode == MULTI_OPEN)
		ofn.Flags |= OFN_FILEMUSTEXIST | (mode == MULTI_OPEN ? OFN_ALLOWMULTISELECT : 0);
	else
		ofn.Flags |= (mode == NODEREF_SAVE ? OFN_NODEREFERENCELINKS : 0);

	char	dirNameBak[MAX_PATH_U8];
	GetCurrentDirectoryU8(sizeof(dirNameBak), dirNameBak);

	BOOL	ret = (mode == OPEN || mode == MULTI_OPEN) ? GetOpenFileNameU8(&ofn) : GetSaveFileNameU8(&ofn);

	SetCurrentDirectoryU8(dirNameBak);
	if (ret)
	{
		if (mode == MULTI_OPEN)
			memcpy(target, szFile, sizeof(szFile));
		else
			strncpyz(target, ofn.lpstrFile, MAX_PATH_U8);

		if (defaultDir)
			strncpyz(defaultDir, ofn.lpstrFile, ofn.nFileOffset);
	}

	return	ret;
}

/*
	BrowseDirDlg用コールバック
*/
int CALLBACK BrowseDirDlgProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM path)
{
	switch (uMsg)
	{
	case BFFM_INITIALIZED:
		SendMessageW(hWnd, BFFM_SETSELECTIONW, (WPARAM)TRUE, path);
		break;

	case BFFM_SELCHANGED:
		break;
	}
	return 0;
}

/*
	ディレクトリダイアログ用汎用ルーチン
*/
BOOL BrowseDirDlg(TWin *parentWin, const char *title, const char *defaultDir, char *buf)
{ 
	IMalloc			*iMalloc = NULL;
	BROWSEINFOW		brInfo;
	LPITEMIDLIST	pidlBrowse;
	BOOL			ret = FALSE;
	Wstr			buf_w(MAX_PATH), defaultDir_w(MAX_PATH), title_w(title);

	if (!SUCCEEDED(SHGetMalloc(&iMalloc)))
		return FALSE;

	U8toW(defaultDir, defaultDir_w.Buf(), MAX_PATH);
	brInfo.hwndOwner = parentWin->hWnd;
	brInfo.pidlRoot = 0;
	brInfo.pszDisplayName = buf_w.Buf();
	brInfo.lpszTitle = title_w;
	brInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	brInfo.lpfn = BrowseDirDlgProc;
	brInfo.lParam = (LPARAM)defaultDir_w.Buf();
	brInfo.iImage = 0;

	if ((pidlBrowse = SHBrowseForFolderV((BROWSEINFO *)&brInfo)) != NULL)
	{
		ret = SHGetPathFromIDListV(pidlBrowse, buf_w.Buf());
		iMalloc->Free(pidlBrowse);
		if (ret)
			WtoU8(buf_w, buf, MAX_PATH_U8);
	}

	iMalloc->Release();
	return	ret;
}

BOOL GetLastErrorMsg(char *msg, TWin *win)
{
	char	buf[MAX_BUF];
	wsprintf(buf, "%s error = %x", msg ? msg : "", GetLastError());
	return	MessageBox(win ? win->hWnd : NULL, buf, MSG_STR, MB_OK);
}

BOOL GetSockErrorMsg(char *msg, TWin *win)
{
	char	buf[MAX_BUF];
	wsprintf(buf, "%s error = %d", msg ? msg : "", WSAGetLastError());
	return	MessageBox(win ? win->hWnd : NULL, buf, MSG_STR, MB_OK);
}


/*
	パスからファイル名部分だけを取り出す
*/
BOOL PathToFname(const char *org_path, char *target_fname)
{
	char	path[MAX_BUF], *fname=NULL;

	if (GetFullPathNameU8(org_path, sizeof(path), path, &fname) == 0 || fname == NULL)
		return	FALSE;

	strncpyz(target_fname, fname, MAX_PATH_U8);
	return	TRUE;
}

/*
	パスからファイル名部分だけを取り出す（強制的に名前を作る）
*/
void ForcePathToFname(const char *org_path, char *target_fname)
{
	if (PathToFname(org_path, target_fname))
		return;

	if (org_path[1] == ':')
		wsprintf(target_fname, "(%c-drive)", *org_path);
	else if (org_path[0] == '\\' && org_path[1] == '\\') {
		if (PathToFname(org_path + 2, target_fname) == FALSE)
			wsprintf(target_fname, "(root)");
	}
	else wsprintf(target_fname, "(unknown)");
}

/*
	2byte文字系でもきちんと動作させるためのルーチン
	 (*strrchr(path, "\\")=0 だと '表'などで問題を起すため)
*/
BOOL PathToDir(const char *org_path, char *target_dir)
{
	char	path[MAX_BUF], *fname=NULL;

	if (GetFullPathNameU8(org_path, sizeof(path), path, &fname) == 0 || fname == NULL)
		return	strncpyz(target_dir, org_path, MAX_PATH_U8), FALSE;

	if (fname - path > 3 || path[1] != ':')
		*(fname - 1) = 0;
	else
		*fname = 0;		// C:\ の場合

	strncpyz(target_dir, path, MAX_PATH_U8);
	return	TRUE;
}

/*
	fname にファイル名以外の要素が含まれていないことを確かめる
*/
BOOL IsSafePath(const char *fullpath, const char *fname)
{
	char	fname2[MAX_PATH_U8];

	if (PathToFname(fullpath, fname2) == FALSE)
		return	FALSE;

	return	strcmp(fname, fname2) == 0 ? TRUE : FALSE;
}

#if 0
int MakePath(char *dest, const char *dir, const char *file)
{
	BOOL	separetor = TRUE;
	int		len;

	if ((len = strlen(dir)) == 0)
		return	wsprintf(dest, "%s", file);

	if (dir[len -1] == '\\')	// 表など、2byte目が'\\'で終る文字列対策
	{
		if (len >= 2 && IsDBCSLeadByte(dir[len -2]) == FALSE)
			separetor = FALSE;
		else {
			for (u_char *p=(u_char *)dir; *p && p[1]; IsDBCSLeadByte(*p) ? p+=2 : p++)
				;
			if (*p == '\\')
				separetor = FALSE;
		}
	}
	return	wsprintf(dest, "%s%s%s", dir, separetor ? "\\" : "", file);
}
#endif

BOOL IsValidFileName(char *fname)
{
	char	buf[MAX_BUF], *tok;
	strncpyz(buf, fname, MAX_BUF);
	return	(tok = (char *)_mbstok((u_char *)buf, (u_char *)"\\/<>|:\?*")) && strcmp(tok, fname) == 0 ? TRUE : FALSE;
}



/*
	time() の代わり
	...なぜか数時間の誤差はあるらしい
	（相対時間としてしか、使用しない）
*/
time_t Time(void)
{
	SYSTEMTIME	st;
	_int64		ft;
// 1601年1月1日から1970年1月1日までの通算100ナノ秒
#define UNIXTIME_BASE	((_int64)0x019db1ded53e8000)

	::GetLocalTime(&st);
	::SystemTimeToFileTime(&st, (FILETIME *)&ft);
	return	(time_t)((ft - UNIXTIME_BASE) / 10000000);
}

/*
	ctime() の代わり
	ただし、改行なし
*/
char *Ctime(SYSTEMTIME *st)
{
	static char	buf[] = "Mon Jan 01 00:00:00 2999";
	static char *wday = "SunMonTueWedThuFriSat";
	static char *mon  = "JanFebMarAprMayJunJulAugSepOctNovDec";
	SYSTEMTIME	_st;

	if (st == NULL)
	{
		st = &_st;
		::GetLocalTime(st);
	}
	wsprintf(buf, "%.3s %.3s %02d %02d:%02d:%02d %04d", &wday[st->wDayOfWeek * 3], &mon[(st->wMonth - 1) * 3], st->wDay, st->wHour, st->wMinute, st->wSecond, st->wYear);
	return	buf;
}

/*
	サイズを文字列に
*/
int MakeSizeString(char *buf, _int64 size, int flg)
{
	if (size >= 1024 * 1024)
	{
		if (flg & MSS_NOPOINT)
			return	wsprintf(buf, "%d%sMB", (int)(size / 1024 / 1024), flg & MSS_SPACE ? " " : "");
		else
			return	wsprintf(buf, "%d.%d%sMB", (int)(size / 1024 / 1024), (int)((size * 10 / 1024 / 1024) % 10), flg & MSS_SPACE ? " " : "");
	}
	else return	wsprintf(buf, "%d%sKB", (int)(ALIGN_BLOCK(size, 1024)), flg & MSS_SPACE ? " " : "");
}

/*
	strtok_r() の簡易版
*/
char *separate_token(char *buf, char separetor, char **handle)
{
	char	*_handle;

	if (handle == NULL)
		handle = &_handle;

	if (buf)
		*handle = buf;

	if (*handle == NULL || **handle == 0)
		return	NULL;

	while (**handle == separetor)
		(*handle)++;
	buf = *handle;

	if (**handle == 0)
		return	NULL;

	while (**handle && **handle != separetor)
		(*handle)++;

	if (**handle == separetor)
		*(*handle)++ = 0;

	return	buf;
}

void MakeHash(const BYTE *data, int len, char *hashStr)
{
	CBlowFish	bl((BYTE *)"ipmsg", 5);
	BYTE		*buf = new BYTE [len + 8];

	bl.Encrypt(data, buf, len);
	bin2hexstr(buf + len - 8, 8, hashStr);
	delete [] buf;
}

BOOL VerifyHash(const BYTE *data, int len, const char *orgHash)
{
	char	hash[MAX_NAMEBUF];

	MakeHash(data, len, hash);
	return	stricmp(hash, orgHash);
}

ULONG ResolveAddr(const char *_host)
{
	if (_host == NULL)
		return 0;

	ULONG	addr = ::inet_addr(_host);

	if (addr == 0xffffffff)
	{
		hostent	*ent = ::gethostbyname(_host);
		addr = ent ? *(ULONG *)ent->h_addr_list[0] : 0;
	}

	return	addr;
}

void TBroadcastList::Reset()
{
	TBroadcastObj	*obj;

	while ((obj = Top()) != NULL)
	{
		DelObj(obj);
		delete obj;
	}
}

#if 0
BOOL TBroadcastList::SetHost(const char *host)
{
	ULONG	addr = ResolveAddr(host);

	if (addr == 0 || IsExistHost(host))
		return	FALSE;

	SetHostRaw(host, addr);
	return	TRUE;
}

BOOL TBroadcastList::IsExistHost(const char *host)
{
	for (TBroadcastObj *obj=Top(); obj; obj=Next(obj))
		if (stricmp(obj->Host(), host) == 0)
			return	TRUE;

	return	FALSE;
}

#endif

char *GetLoadStrAsFilter(UINT id)
{
	char	*ret = GetLoadStrU8(id);
	if (ret) {
		for (char *p = ret; *p; p++) {
			if (*p == '!') {
				*p = '\0';
			}
		}
	}
	return	ret;
}

BOOL GetCurrentScreenSize(RECT *rect, HWND hRefWnd)
{
	rect->left = rect->top = 0;
	rect->right = ::GetSystemMetrics(SM_CXFULLSCREEN);
	rect->bottom = ::GetSystemMetrics(SM_CYFULLSCREEN);

	static BOOL (WINAPI *GetMonitorInfoV)(HMONITOR hMonitor, MONITORINFO *lpmi);
	static HMONITOR (WINAPI *MonitorFromPointV)(POINT pt, DWORD dwFlags);
	static HMONITOR (WINAPI *MonitorFromWindowV)(HWND hWnd, DWORD dwFlags);
	static HMODULE hUser32;

	if (!hUser32) {
		hUser32 = ::GetModuleHandle("user32.dll");
		GetMonitorInfoV = (BOOL (WINAPI *)(HMONITOR, MONITORINFO *))::GetProcAddress(hUser32, "GetMonitorInfoW");
		MonitorFromPointV = (HMONITOR (WINAPI *)(POINT, DWORD))::GetProcAddress(hUser32, "MonitorFromPoint");
		MonitorFromWindowV = (HMONITOR (WINAPI *)(HWND, DWORD))::GetProcAddress(hUser32, "MonitorFromWindow");
	}

	if (MonitorFromPointV && GetMonitorInfoV && MonitorFromWindowV) {
		POINT	pt;
		::GetCursorPos(&pt);

		HMONITOR	hMon = hRefWnd ? MonitorFromWindowV(hRefWnd, MONITOR_DEFAULTTONEAREST) : MonitorFromPointV(pt, MONITOR_DEFAULTTONEAREST);

		if (hMon) {
			MONITORINFO	info;
			info.cbSize = sizeof(info);

			if (GetMonitorInfoV(hMon, &info))
				*rect = info.rcMonitor;
		}
	}

	return	TRUE;
}


