static char *recvdlg_id = 
	"@(#)Copyright (C) H.Shirouzu 1996-2004   recvdlg.cpp	Ver2.05";
/* ========================================================================
	Project  Name			: IP Messenger for Win32
	Module Name				: Receive Dialog
	Create					: 1996-06-01(Sat)
	Update					: 2004-01-01(Thu)
	Copyright				: H.Shirouzu
	Reference				: 
	======================================================================== */

#include <time.h>
#include "resource.h"
#include "ipmsg.h"
#include "blowfish.h"

int TRecvDlg::createCnt = 0;

TRecvDlg::TRecvDlg(MsgMng *_msgMng, MsgBuf *_msg, THosts *_hosts, Cfg *_cfg, LogMng *_logmng) : TListDlg(RECEIVE_DIALOG), editSub(_cfg, this)
{
	msgMng		= _msgMng;
	cfg			= _cfg;
	openFlg		= FALSE;
	logmng		= _logmng;
	hosts		= _hosts;
	hEditFont	= NULL;
	hHeadFont	= NULL;
	fileObj		= NULL;
	shareInfo	= NULL;
	timerID		= 0;
	retryCnt	= 0;
	cryptCapa	= 0;
	createCnt++;
	::GetLocalTime(&recvTime);

	memset(&orgFont, 0, sizeof(orgFont));
	msg.Init(_msg);

	MakeListString(cfg, &msg.hostSub, hosts, head);

	if (msg.command & IPMSG_FILEATTACHOPT)
	{
		char	*shareStr = msg.msgBuf + msg.exOffset;
		if ((shareInfo = DecodeShareMsg(shareStr)) != NULL)
		{
			fileObj = new RecvFileObj;
			memset(fileObj, 0, sizeof(RecvFileObj));
		}
	}

	status = TRUE;
	if (msg.command & IPMSG_ENCRYPTOPT) {
		if ((status = DecryptMsg()) == FALSE)
			msgMng->Send(&msg.hostSub, IPMSG_SENDMSG|IPMSG_NOLOGOPT, GetLoadStr(IDS_DECRYPTERR));
	}
/* msgmng.cpp �ŕϊ��ς�
	else if ((msg.command & IPMSG_UTF8OPT) == 0) {
		strncpyz(msg.msgBuf, AtoU8(msg.msgBuf), sizeof(msg.msgBuf));
	}
*/
	if (status) {
		if ((msg.command & IPMSG_PASSWORDOPT) == 0 || cfg->PasswdLogCheck == FALSE)
			logmng->WriteRecvMsg(&msg, hosts, shareInfo);

		hAccel = ::LoadAccelerators(TApp::GetInstance(), (LPCSTR)IPMSG_ACCEL);
	}
}

TRecvDlg::~TRecvDlg()
{
	if (shareInfo) 
	{
		if (shareInfo->fileCnt > 0)
			msgMng->Send(&msg.hostSub, IPMSG_RELEASEFILES, msg.packetNo);
		// ���ƂŎ�M�I���ʒm�̃R�[�h������
		FreeDecodeShareMsg(shareInfo);
	}
	if (fileObj)
	{
		if (fileObj->conInfo)
			delete fileObj->conInfo;
		delete fileObj;
	}

	if (hHeadFont)
		::DeleteObject(hHeadFont);
	if (hEditFont)
		::DeleteObject(hEditFont);

	createCnt--;
}

/*
	���b�Z�[�W�̕�����
*/
BOOL TRecvDlg::DecryptMsg()
{
	HCRYPTKEY	hKey=0, hExKey=0;
	char		*capa_hex, *skey_hex, *msg_hex, *p;
	BYTE		skey[MAX_BUF];
	int			len, msgLen;
	HCRYPTPROV	target_csp;

	if ((capa_hex = separate_token(msg.msgBuf, ':', &p)) == NULL)
		return	FALSE;
	cryptCapa = strtoul(capa_hex, 0, 16);
	target_csp = (cryptCapa & IPMSG_RSA_1024) && cfg->pubKey.Key() ? cfg->hCsp : cfg->hSmallCsp;
	hExKey = target_csp == cfg->hCsp ? cfg->hPrivKey : cfg->hSmallPrivKey;

	if ((skey_hex = separate_token(NULL, ':', &p)) == NULL)
		return	FALSE;
	if ((msg_hex = separate_token(NULL, 0, &p)) == NULL)
		return	FALSE;

	if (cryptCapa & IPMSG_BLOWFISH_128) {	// blowfish
		hexstr2bin_bigendian(skey_hex, skey, sizeof(skey), &len);
		// ���J���擾
		if (!pCryptDecrypt(hExKey, 0, TRUE, 0, (BYTE *)skey, (DWORD *)&len))
			return	wsprintf(msg.msgBuf, "CryptDecrypt Err(%X)", GetLastError()), FALSE;

		CBlowFish	bl(skey, len);
		hexstr2bin(msg_hex, (BYTE *)msg.msgBuf, sizeof(msg.msgBuf), &msgLen);
		bl.Decrypt((BYTE *)msg.msgBuf, (BYTE *)msg.msgBuf, msgLen);
	}
	else {	// RC2
	// Skey Blob �����
		skey[0] = SIMPLEBLOB;
		skey[1] = CUR_BLOB_VERSION;
		*(WORD *)(skey + 2) = 0;
		*(ALG_ID *)(skey + 4) = CALG_RC2;
		*(ALG_ID *)(skey + 8) = CALG_RSA_KEYX;
		hexstr2bin_bigendian(skey_hex, skey + SKEY_HEADER_SIZE, sizeof(skey) - SKEY_HEADER_SIZE, &len);

	// �Z�b�V�����L�[�� import
		if (!pCryptImportKey(target_csp, skey, len + SKEY_HEADER_SIZE, hExKey, 0, &hKey))
			return	wsprintf(msg.msgBuf, "CryptImportKey Err(%X)", GetLastError()), FALSE;

	// ���b�Z�[�W�� Decrypt
		hexstr2bin(msg_hex, (BYTE *)msg.msgBuf, sizeof(msg.msgBuf), &msgLen);
		if (!pCryptDecrypt(hKey, 0, TRUE, 0, (BYTE *)msg.msgBuf, (DWORD *)&msgLen))
			return	wsprintf(msg.msgBuf, "CryptDecrypt Err(%X)", GetLastError()), FALSE;
		pCryptDestroyKey(hKey);
	}
	// UNIX �`���̉��s��ϊ�
	if (cryptCapa & (IPMSG_BLOWFISH_128|IPMSG_RC2_40))
		MsgMng::UnixNewLineToLocal(msg.msgBuf, msg.msgBuf, sizeof(msg.msgBuf));

	if ((msg.command & IPMSG_UTF8OPT) == 0) {
		char	*u8buf = AtoU8(msg.msgBuf);
		int		u8len = strlen(u8buf), diff=0;

		u8len = min(u8len, MAX_UDPBUF-1);
		int		dif = u8len - strlen(msg.msgBuf);

		if (msg.exOffset &&	diff > 0) {
			memmove(msg.msgBuf + msg.exOffset + diff, msg.msgBuf + msg.exOffset, diff);
		}
		strncpyz(msg.msgBuf, u8buf, u8len+1);
	}

	return	TRUE;
}


BOOL TRecvDlg::EvCreate(LPARAM lParam)
{
	editSub.AttachWnd(GetDlgItem(RECV_EDIT));

	editSub.SendMessage(EM_AUTOURLDETECT, 1, 0);
	editSub.SendMessage(EM_SETBKGNDCOLOR, FALSE, ::GetSysColor(COLOR_3DFACE));
	editSub.SendMessage(EM_SETTARGETDEVICE, 0, 0);		// �܂�Ԃ�

	SetDlgIcon(hWnd);
	SetDlgItemTextU8(RECV_HEAD, head);

	if (msg.command & IPMSG_BROADCASTOPT)
		SetDlgItemTextU8(RECV_TITLE, GetLoadStrU8(IDS_BROADCAST));
	else if (msg.command & IPMSG_MULTICASTOPT)
		SetDlgItemTextU8(RECV_TITLE, GetLoadStrU8(IDS_MULTICAST));
	else
		SetDlgItemTextU8(RECV_TITLE, GetLoadStrU8(IDS_UNICAST));

	if (msg.command & IPMSG_AUTORETOPT)
		SetDlgItemTextU8(RECV_TITLE, GetLoadStrU8(IDS_UNIABSENCE));

	char	buf[MAX_LISTBUF];
	if (msg.command & IPMSG_ENCRYPTOPT)
	{
		GetWindowText(buf, sizeof(buf));
		strcat(buf, (cryptCapa & IPMSG_BLOWFISH_128) ? " +" : " -");
		SetWindowText(buf);
	}

	wsprintf(head, "at %s", Ctime(&recvTime));
	SetDlgItemTextU8(RECV_HEAD2, head);

	editSub.ExSetText(msg.msgBuf);

	if (msg.command & IPMSG_SECRETOPT)
		editSub.ShowWindow(SW_HIDE), ::ShowWindow(GetDlgItem(QUOTE_CHECK), SW_HIDE);
	else {
		::ShowWindow(GetDlgItem(OPEN_BUTTON), SW_HIDE), openFlg = TRUE;
		if (shareInfo)
			SetFileButton(this, FILE_BUTTON, shareInfo);
	}

	if (msg.command & IPMSG_FILEATTACHOPT)
	{
		GetDlgItemTextU8(OPEN_BUTTON, buf, sizeof(buf));
		strcat(buf, " ");
		strcat(buf, GetLoadStrU8(IDS_FILEATTACH));
		SetDlgItemTextU8(OPEN_BUTTON, buf);
	}
	if (msg.command & IPMSG_PASSWORDOPT)
	{
		GetDlgItemTextU8(OPEN_BUTTON, buf, sizeof(buf));
		strcat(buf, GetLoadStrU8(IDS_KEYOPEN));
		SetDlgItemTextU8(OPEN_BUTTON, buf);
	}

	if (cfg->QuoteCheck)
		SendDlgItemMessage(QUOTE_CHECK, BM_SETCHECK, cfg->QuoteCheck, 0);

	if (cfg->AbnormalButton)
		SetDlgItemTextU8(IDOK, GetLoadStrU8(IDS_INTERCEPT));

	SetFont();
	SetSize();

	HMENU	hMenu = ::GetSystemMenu(hWnd, FALSE);
	AppendMenuU8(hMenu, MF_SEPARATOR, NULL, NULL);
	SetMainMenu(hMenu);

	if (IsNewShell() != TRUE)
	{
		ULONG	style = GetWindowLong(GWL_STYLE);
		style &= 0xffffff0f;
		style |= 0x00000080;
		SetWindowLong(GWL_STYLE, style);
	}
	SetForegroundWindow();

	if (msg.command & IPMSG_NOADDLISTOPT)
		::EnableWindow(GetDlgItem(IDOK), FALSE);
	EvSize(SIZE_RESTORED, 0, 0);

	return	TRUE;
}

BOOL TRecvDlg::EvCommand(WORD wNotifyCode, WORD wID, LPARAM hWndCtl)
{
	switch (wID)
	{
	case IDOK:
		if (openFlg && ::IsDlgButtonChecked(hWnd, QUOTE_CHECK)) {
			CHARRANGE	cr;
			editSub.SendMessageW(EM_EXGETSEL, 0, (LPARAM)&cr);
			// GT_SELECTION + GT_USECRLF �̑g�ݍ��킹�ɂ́A�o�O�����邽�߁A�g���Ȃ� �� ���O�� "\r" -> "\r\n" �ɕϊ�
			DynBuf	buf(MAX_UDPBUF);
			editSub.ExGetText(buf.Buf(), buf.Size(), (cr.cpMin == cr.cpMax ? GT_DEFAULT : GT_SELECTION));
			int i=0, j=0;
			for ( ; buf.Buf()[i] && j < MAX_UDPBUF; i++, j++) {
				if ((msg.msgBuf[j] = buf.Buf()[i]) == '\r') {
					msg.msgBuf[++j] = '\n';
				}
			}
			msg.msgBuf[j] = 0;
		}
		else
			*msg.msgBuf = 0;
		::PostMessage(GetMainWnd(), WM_SENDDLG_OPEN, (WPARAM)hWnd, (LPARAM)&msg);
		return	TRUE;

	case IDCANCEL:
		if ((GetAsyncKeyState(VK_ESCAPE) & 0x8000) == 0)
		{
			if (fileObj && fileObj->conInfo)
				return	EvCommand(0, FILE_BUTTON, 0), TRUE;
			if (timerID == 0)
				::PostMessage(GetMainWnd(), WM_RECVDLG_EXIT, 0, (LPARAM)this);
			else
				TWin::Show(SW_HIDE);
		}
		return	TRUE;

	case MISC_ACCEL:
	case HIDE_ACCEL:
		::PostMessage(GetMainWnd(), WM_COMMAND, wID, 0);
		return	TRUE;

	case ALLSELECT_ACCEL:
		editSub.SendMessage(EM_SETSEL, 0, (LPARAM)-1);
		return	TRUE;

	case OPEN_BUTTON:
		if (openFlg)
			return	TRUE;

		if (msg.command & IPMSG_PASSWORDOPT)
		{
			TPasswordDlg	dlg(cfg, this);

			if (dlg.Exec() != TRUE)
				return	TRUE;

			if (cfg->PasswdLogCheck)
				logmng->WriteRecvMsg(&msg, hosts, shareInfo);
		}
		openFlg = TRUE;

		editSub.ShowWindow(SW_SHOW);
		::ShowWindow(GetDlgItem(QUOTE_CHECK), SW_SHOW);
		::ShowWindow(GetDlgItem(OPEN_BUTTON), SW_HIDE);
		::EnableWindow(GetDlgItem(OPEN_BUTTON), FALSE);

		if (shareInfo)
			SetFileButton(this, FILE_BUTTON, shareInfo), EvSize(SIZE_RESTORED, 0, 0);

		if (msg.command & IPMSG_SECRETOPT)
		{
			char	buf[MAX_LISTBUF];
			wsprintf(buf, "%ld", msg.packetNo);
			packetNo = msgMng->MakeMsg(readMsgBuf, IPMSG_READMSG|(msg.command & IPMSG_READCHECKOPT), buf);
			msgMng->UdpSend(msg.hostSub.addr, msg.hostSub.portNo, readMsgBuf);
			if (msg.command & IPMSG_READCHECKOPT)
				timerID = ::SetTimer(hWnd, IPMSG_RECV_TIMER, cfg->RetryMSec, NULL);
		}
		return	TRUE;

	case FILE_BUTTON:
		if (fileObj && fileObj->conInfo)
		{
			if (fileObj->hThread)
				::SuspendThread(fileObj->hThread);
			int ret = MessageBoxU8(GetLoadStrU8(IDS_TRANSSTOP), MSG_STR, MB_OKCANCEL);
			if (fileObj->hThread)
				::ResumeThread(fileObj->hThread);
			if (ret == IDOK)
				if (fileObj->conInfo) EndRecvFile(TRUE);
		}
		else if (fileObj) {
			TSaveCommonDlg	dlg(shareInfo, cfg, this);
			if (dlg.Exec())
			{
				memset(fileObj, 0, sizeof(RecvFileObj));
				strncpyz(fileObj->saveDir, cfg->lastSaveDir, MAX_PATH_U8);
				SaveFile();
			}
		}
		break;

	case MENU_SAVEPOS:
		if ((cfg->RecvSavePos = !cfg->RecvSavePos) != 0)
		{
			GetWindowRect(&rect);
			cfg->RecvXpos = rect.left;
			cfg->RecvYpos = rect.top;
		}
		cfg->WriteRegistry(CFG_WINSIZE);
		return	TRUE;

	case MENU_SAVESIZE:
		GetWindowRect(&rect);
		cfg->RecvXdiff = (rect.right - rect.left) - (orgRect.right - orgRect.left);
		cfg->RecvYdiff = (rect.bottom - rect.top) - (orgRect.bottom - orgRect.top);
		cfg->WriteRegistry(CFG_WINSIZE);
		return	TRUE;

	case MENU_NORMALSIZE:
		GetWindowRect(&rect);
		MoveWindow(rect.left, rect.top, orgRect.right - orgRect.left, orgRect.bottom - orgRect.top, TRUE);
		return	TRUE;

	case MENU_EDITFONT: case MENU_HEADFONT:
		CHOOSEFONT	cf;
		LOGFONT		tmpFont, *targetFont;

		targetFont = wID == MENU_EDITFONT ? &cfg->RecvEditFont : &cfg->RecvHeadFont;
		memset(&cf, 0, sizeof(cf));
		cf.lStructSize	= sizeof(cf);
		cf.hwndOwner	= hWnd;
		cf.lpLogFont	= &(tmpFont = *targetFont);
		cf.Flags		= CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT | CF_SHOWHELP;
		cf.nFontType	= SCREEN_FONTTYPE;
		if (::ChooseFont(&cf))
		{
			*targetFont = tmpFont;
			SetFont();
			::InvalidateRgn(hWnd, NULL, TRUE);
		}
		cfg->WriteRegistry(CFG_FONT);
		return	TRUE;

	case MENU_DEFAULTFONT:
		cfg->RecvHeadFont = orgFont;
		cfg->RecvEditFont = orgFont;
		SetFont();
		::InvalidateRgn(hWnd, NULL, TRUE);
		cfg->WriteRegistry(CFG_FONT);
		return	TRUE;
	}

	return	FALSE;
}

BOOL TRecvDlg::SaveFile(void)
{
	int		target;
	for (target=0; target < shareInfo->fileCnt; target++)
		if (shareInfo->fileInfo[target]->IsSelected())
			break;
	if (target == shareInfo->fileCnt)
		return	FALSE;

	memset(fileObj, 0, (char *)&fileObj->totalTrans - (char *)fileObj);
	fileObj->conInfo = new ConnectInfo;
	fileObj->fileInfo = shareInfo->fileInfo[target];
	fileObj->isDir = GET_MODE(fileObj->fileInfo->Attr()) == IPMSG_FILE_DIR ? TRUE : FALSE;
	fileObj->status = fileObj->isDir ? FS_DIRFILESTART : FS_TRANSFILE;
	fileObj->hFile = INVALID_HANDLE_VALUE;
	if (fileObj->isDir)
		strncpyz(fileObj->path, fileObj->saveDir, MAX_PATH_U8);

	if (ConnectRecvFile())
		SetDlgItemTextU8(FILE_BUTTON, GetLoadStrU8(IDS_PREPARETRANS));
	else {
		delete fileObj->conInfo;
		fileObj->conInfo = NULL;
	}
	fileObj->startTick = ::GetTickCount();
	return	TRUE;
}

BOOL TRecvDlg::EvSysCommand(WPARAM uCmdType, POINTS pos)
{
	switch (uCmdType)
	{
	case MENU_SAVEPOS:
	case MENU_SAVESIZE:
	case MENU_NORMALSIZE:
	case MENU_EDITFONT: case MENU_HEADFONT:
	case MENU_DEFAULTFONT:
		return	EvCommand(0, uCmdType, 0);
	}

	return	FALSE;
}

/*
	User��` Event CallBack
*/
BOOL TRecvDlg::EventUser(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_TCPEVENT:
		TcpEvent(wParam, lParam);
		return	TRUE;

	case WM_RECVDLG_FILEBUTTON:
		SetTransferButtonText();
		return	TRUE;
	}
	return	FALSE;
}

/*
	WM_TIMER event call back
	���M�m�F/�đ��p
*/
BOOL TRecvDlg::EvTimer(WPARAM _timerID, TIMERPROC proc)
{
	if (retryCnt++ < cfg->RetryMax * 2)
	{
		msgMng->UdpSend(msg.hostSub.addr, msg.hostSub.portNo, readMsgBuf);
		return	TRUE;
	}

	::KillTimer(hWnd, IPMSG_RECV_TIMER);
	if (timerID == 0)	// �ē��悯
		return	FALSE;
	timerID = 0;

	if (::IsWindowVisible(hWnd) == FALSE)
		::PostMessage(GetMainWnd(), WM_RECVDLG_EXIT, 0, (LPARAM)this);

	return	TRUE;
}

BOOL TRecvDlg::EvSize(UINT fwSizeType, WORD nWidth, WORD nHeight)
{
	if (fwSizeType != SIZE_RESTORED && fwSizeType != SIZE_MAXIMIZED)
		return	FALSE;

	GetWindowRect(&rect);
	int	xdiff = (rect.right - rect.left) - (orgRect.right - orgRect.left);
	int ydiff = (rect.bottom - rect.top) - (orgRect.bottom - orgRect.top);

	HDWP	hdwp = ::BeginDeferWindowPos(max_recvitem);	// MAX item number
	WINPOS	*wpos;
	BOOL	isFileBtn = IsWindowEnabled(GetDlgItem(FILE_BUTTON));
	UINT	dwFlg = (IsNewShell() ? SWP_SHOWWINDOW : SWP_NOREDRAW) | SWP_NOZORDER;
	UINT	dwHideFlg = SWP_HIDEWINDOW | SWP_NOZORDER;
	if (hdwp == NULL)
		return	FALSE;

// �T�C�Y���������Ȃ�ꍇ�̒����l�́ATry and Error(^^;
	wpos = &item[title_item];
	if ((hdwp = ::DeferWindowPos(hdwp, GetDlgItem(RECV_TITLE), NULL, wpos->x, wpos->y, wpos->cx + xdiff, wpos->cy, dwFlg)) == NULL)
		return	FALSE;

	wpos = &item[head_item];
	if ((hdwp = ::DeferWindowPos(hdwp, GetDlgItem(RECV_HEAD), NULL, wpos->x, wpos->y, wpos->cx + xdiff, wpos->cy, dwFlg)) == NULL)
		return	FALSE;

	wpos = &item[head2_item];
	if ((hdwp = ::DeferWindowPos(hdwp, GetDlgItem(RECV_HEAD2), NULL, wpos->x, wpos->y, wpos->cx + xdiff, wpos->cy, dwFlg)) == NULL)
		return	FALSE;

	wpos = &item[file_item];
	if ((hdwp = ::DeferWindowPos(hdwp, GetDlgItem(FILE_BUTTON), NULL, wpos->x, wpos->y, wpos->cx + xdiff, wpos->cy, (isFileBtn && openFlg) ? dwFlg : dwHideFlg)) == NULL)
		return	FALSE;

	wpos = &item[open_item];
	if ((hdwp = ::DeferWindowPos(hdwp, GetDlgItem(OPEN_BUTTON), NULL, wpos->x, wpos->y, wpos->cx + xdiff, wpos->cy + ydiff, openFlg ? dwHideFlg : dwFlg)) == NULL)
		return	FALSE;

	wpos = &item[edit_item];
	if ((hdwp = ::DeferWindowPos(hdwp, editSub.hWnd, NULL, wpos->x, (isFileBtn ? wpos->y : item[file_item].y), wpos->cx + xdiff, wpos->cy + ydiff + (isFileBtn ? 0 : wpos->y - item[file_item].y), openFlg ? dwFlg : dwHideFlg)) == NULL)
		return	FALSE;

	wpos = &item[ok_item];
	if ((hdwp = ::DeferWindowPos(hdwp, GetDlgItem(IDOK), NULL, wpos->x + (xdiff >= 0 ? xdiff / 2 : xdiff * 3 / 4), wpos->y + ydiff, wpos->cx + (xdiff >= 0 ? 0 : xdiff / 4), wpos->cy, dwFlg)) == NULL)
		return	FALSE;

	wpos = &item[cancel_item];
	if ((hdwp = ::DeferWindowPos(hdwp, GetDlgItem(IDCANCEL), NULL, wpos->x + (xdiff >= 0 ? xdiff / 2 : xdiff * 3 / 8), wpos->y + ydiff, wpos->cx + (xdiff >= 0 ? 0 : xdiff * 1 / 4), wpos->cy, dwFlg)) == NULL)
		return	FALSE;

	wpos = &item[quote_item];
	if ((hdwp = ::DeferWindowPos(hdwp, GetDlgItem(QUOTE_CHECK), NULL, wpos->x + (xdiff >= 0 ? xdiff / 2 : xdiff), wpos->y + ydiff, wpos->cx, wpos->cy, openFlg ? dwFlg : dwHideFlg)) == NULL)
		return	FALSE;

	EndDeferWindowPos(hdwp);

	if (!IsNewShell())
		::InvalidateRgn(hWnd, NULL, TRUE);

	return	TRUE;
}


BOOL TRecvDlg::EvGetMinMaxInfo(MINMAXINFO *info)
{
	info->ptMinTrackSize.x = (orgRect.right - orgRect.left) * 2 / 3;
	info->ptMinTrackSize.y = (orgRect.bottom - orgRect.top) * 2 / 3;

	return	TRUE;
}

/*
	Context Menu event call back
*/
BOOL TRecvDlg::EvContextMenu(HWND childWnd, POINTS pos)
{
	PopupContextMenu(pos);
	return	TRUE;
}

/*
	Notify Event CallBack
*/
BOOL TRecvDlg::EvNotify(UINT ctlID, NMHDR *pNmHdr)
{
	switch (pNmHdr->code) {
	case EN_LINK:
		{
			ENLINK	*el = (ENLINK *)pNmHdr;
			if (el->msg == WM_LBUTTONDOWN) {
//				Debug("EN_LINK (%d %d)\n", el->chrg.cpMin, el->chrg.cpMax);
				editSub.SendMessageW(EM_EXSETSEL, 0, (LPARAM)&el->chrg);
				editSub.EventUser(WM_EDIT_DBLCLK, 0, 0);
			}
		}
		return	TRUE;
	}

	return	FALSE;
}


BOOL TRecvDlg::IsSamePacket(MsgBuf *test_msg)
{
	if (test_msg->packetNo == msg.packetNo && test_msg->hostSub.addr == msg.hostSub.addr && test_msg->hostSub.portNo == msg.hostSub.portNo)
		return	TRUE;
	else
		return	FALSE;
}

void TRecvDlg::SetFont(void)
{
	HFONT	hDlgFont;
	LOGFONT	*editFont;

	if ((hDlgFont = (HFONT)SendMessage(WM_GETFONT, 0, 0L)) == NULL)
		return;
	if (::GetObject(hDlgFont, sizeof(LOGFONT), (LPSTR)&orgFont) == NULL)
		return;

	if (*cfg->RecvHeadFont.lfFaceName == 0)	//�����f�[�^�Z�b�g
		cfg->RecvHeadFont = orgFont;
	if (*cfg->RecvEditFont.lfFaceName == 0)	//�����f�[�^�Z�b�g
		cfg->RecvEditFont = orgFont;

	if (*cfg->RecvHeadFont.lfFaceName && (hDlgFont = ::CreateFontIndirect(&cfg->RecvHeadFont)) != NULL)
	{
		SendDlgItemMessage(RECV_HEAD, WM_SETFONT, (UINT)hDlgFont, 0L);
		SendDlgItemMessage(RECV_HEAD2, WM_SETFONT, (UINT)hDlgFont, 0L);
		if (hHeadFont)
			::DeleteObject(hHeadFont);
		hHeadFont = hDlgFont;
	}

	editFont = &cfg->RecvEditFont;

	if (editFont->lfFaceName /*&& (hDlgFont = ::CreateFontIndirect(editFont)) != NULL*/)
	{
		editSub.SetFont(&cfg->RecvEditFont);
		editSub.ExSetText(msg.msgBuf);
//		editSub.SendMessage(WM_SETFONT, (UINT)hDlgFont, 0L);
//		if (hEditFont)
//			::DeleteObject(hEditFont);
//		hEditFont = hDlgFont;
	}
}

void TRecvDlg::SetSize(void)
{
	WINDOWPLACEMENT wp;
	wp.length = sizeof(wp);

	::GetWindowPlacement(GetDlgItem(RECV_TITLE), &wp);
	RectToWinPos(&wp.rcNormalPosition, &item[title_item]);

	::GetWindowPlacement(GetDlgItem(RECV_HEAD), &wp);
	RectToWinPos(&wp.rcNormalPosition, &item[head_item]);

	::GetWindowPlacement(GetDlgItem(RECV_HEAD2), &wp);
	RectToWinPos(&wp.rcNormalPosition, &item[head2_item]);

	::GetWindowPlacement(GetDlgItem(FILE_BUTTON), &wp);
	RectToWinPos(&wp.rcNormalPosition, &item[file_item]);

	::GetWindowPlacement(GetDlgItem(OPEN_BUTTON), &wp);
	RectToWinPos(&wp.rcNormalPosition, &item[open_item]);

	::GetWindowPlacement(editSub.hWnd, &wp);
	RectToWinPos(&wp.rcNormalPosition, &item[edit_item]);

	::GetWindowPlacement(GetDlgItem(IDOK), &wp);
	RectToWinPos(&wp.rcNormalPosition, &item[ok_item]);

	::GetWindowPlacement(GetDlgItem(IDCANCEL), &wp);
	RectToWinPos(&wp.rcNormalPosition, &item[cancel_item]);

	::GetWindowPlacement(GetDlgItem(QUOTE_CHECK), &wp);
	RectToWinPos(&wp.rcNormalPosition, &item[quote_item]);

	GetWindowRect(&rect);
	orgRect = rect;

	RECT	scRect;
	GetCurrentScreenSize(&scRect);

	int	cx = scRect.right - scRect.left, cy = scRect.bottom - scRect.top;
	int	xsize = rect.right - rect.left + cfg->RecvXdiff, ysize = rect.bottom - rect.top + cfg->RecvYdiff;
	int	x = cfg->RecvXpos, y = cfg->RecvYpos;

	if (cfg->RecvSavePos == 0)
	{
		x = (cx - xsize)/2 + (rand() % (cx/4)) - cx/8;
		y = (cy - ysize)/2 + (rand() % (cy/4)) - cy/8;
	}
	if (x + xsize > cx)
		x = cx - xsize;
	if (y + ysize > cy)
		y = cy - ysize;

	MoveWindow(max(x, scRect.left), max(y, scRect.top), xsize, ysize, TRUE);
}

/*
	Menu Event CallBack
*/
BOOL TRecvDlg::EventInitMenu(UINT uMsg, HMENU hMenu, UINT uPos, BOOL fSystemMenu)
{
	switch (uMsg)
	{
	case WM_INITMENU:
		{
			ModifyMenuU8(hMenu, MENU_SAVEPOS, MF_BYCOMMAND|(cfg->RecvSavePos ? MF_CHECKED :  0), MENU_SAVEPOS, GetLoadStrU8(IDS_SAVEPOS));
		}
		return	TRUE;
	}
	return	FALSE;
}

/*
	Color Event CallBack
*/
BOOL TRecvDlg::EventCtlColor(UINT uMsg, HDC hDcCtl, HWND hWndCtl, HBRUSH *result)
{
#if 0
	switch (uMsg) {
	case WM_CTLCOLORDLG:
		{ static HBRUSH hb; if (hb == NULL) hb = ::CreateSolidBrush(0x222222); *result = hb; }
		break;
	case WM_CTLCOLOREDIT:
		{ static HBRUSH hb; if (hb == NULL) hb = ::CreateSolidBrush(0x222222); *result = hb; }
		SetTextColor(hDcCtl, 0xeeeeee);
		SetBkColor(hDcCtl, 0x222222);
		break;
	case WM_CTLCOLORSTATIC:
		{ static HBRUSH hb; if (hb == NULL) hb = ::CreateSolidBrush(0x222222); *result = hb; }
		SetTextColor(hDcCtl, 0xeeeeee);
		SetBkColor(hDcCtl, 0x222222);
		break;
	}
	return	TRUE;
#else
	return	FALSE;
#endif
}

BOOL TRecvDlg::EventButton(UINT uMsg, int nHitTest, POINTS pos)
{
	switch (uMsg)
	{
	case WM_RBUTTONUP:
		if (!IsNewShell())
			PopupContextMenu(pos);
		return	TRUE;
	}
	return	FALSE;
}

void TRecvDlg::PopupContextMenu(POINTS pos)
{
	HMENU	hMenu = ::CreatePopupMenu();

	SetMainMenu(hMenu);
	::TrackPopupMenu(hMenu, TPM_LEFTALIGN|TPM_RIGHTBUTTON, pos.x, pos.y, 0, hWnd, NULL);
	::DestroyMenu(hMenu);
}

void TRecvDlg::SetMainMenu(HMENU hMenu)
{
	AppendMenuU8(hMenu, MF_POPUP, (UINT)::LoadMenu(TApp::GetInstance(), (LPCSTR)RECVFONT_MENU), GetLoadStrU8(IDS_FONTSET));
	AppendMenuU8(hMenu, MF_POPUP, (UINT)::LoadMenu(TApp::GetInstance(), (LPCSTR)SIZE_MENU), GetLoadStrU8(IDS_SIZESET));
	AppendMenuU8(hMenu, MF_STRING, MENU_SAVEPOS, GetLoadStrU8(IDS_SAVEPOS));
}

/*
	���M�I���ʒm
*/
BOOL TRecvDlg::SendFinishNotify(HostSub *hostSub, ULONG packet_no)
{
	if (msg.hostSub.addr == hostSub->addr && msg.hostSub.portNo == hostSub->portNo && packet_no == packetNo) {
		if (timerID == IPMSG_RECV_TIMER) {
			::KillTimer(hWnd, IPMSG_RECV_TIMER);
			timerID = 0;
			if (::IsWindowVisible(hWnd) == FALSE)
				::PostMessage(GetMainWnd(), WM_RECVDLG_EXIT, 0, (LPARAM)this);
		}
		return	TRUE;
	}
	return	FALSE;
}

/*
	���M���́AShow��visible���͂���
*/
void TRecvDlg::Show(int mode)
{
	if (timerID == 0 && hWnd)
		TWin::Show(mode);
}

BOOL TRecvDlg::TcpEvent(SOCKET sd, LPARAM lParam)
{
	if (fileObj == NULL || fileObj->conInfo == NULL)
		return	FALSE;

	switch (LOWORD(lParam)) {
	case FD_CONNECT:	// connect done
		StartRecvFile();
		break;

	case FD_CLOSE:
		EndRecvFile();
		break;
	}
	return	TRUE;
}

BOOL TRecvDlg::ConnectRecvFile(void)
{
	memset(fileObj->conInfo, 0, sizeof(ConnectInfo));
	fileObj->conInfo->addr = msg.hostSub.addr;
	fileObj->conInfo->port = msg.hostSub.portNo;

	if (msgMng->Connect(hWnd, fileObj->conInfo) != TRUE)
		return	FALSE;

	if (fileObj->conInfo->complete)
		StartRecvFile();

	return	TRUE;
}

#define	OFFSET 0

BOOL TRecvDlg::StartRecvFile(void)
{
	char	buf[MAX_PATH_U8], tcpbuf[MAX_BUF];
	wsprintf(buf, fileObj->isDir ? "%x:%x:" : "%x:%x:%x:", msg.packetNo, fileObj->fileInfo->Id(), OFFSET);
	fileObj->conInfo->complete = TRUE;
	msgMng->MakeMsg(tcpbuf, fileObj->isDir ? IPMSG_GETDIRFILES : IPMSG_GETFILEDATA, buf);
	msgMng->ConnectDone(hWnd, fileObj->conInfo);

//fileObj->offset = fileObj->woffset = OFFSET;

	if (::send(fileObj->conInfo->sd, tcpbuf, strlen(tcpbuf), 0) < (int)strlen(tcpbuf))
		return	EndRecvFile(), FALSE;

	fileObj->conInfo->startTick = fileObj->conInfo->lastTick = ::GetTickCount();

	if (fileObj->isDir == FALSE)
		fileObj->curFileInfo = *fileObj->fileInfo;
	fileObj->recvBuf = new char [cfg->TransMax];

	// 0byte file �����́A����
	if (fileObj->isDir == FALSE && fileObj->curFileInfo.Size() == 0)
	{
		if (OpenRecvFile())
		{
			CloseRecvFile(TRUE);
			fileObj->status = FS_COMPLETE;
		}
		else fileObj->status = FS_ERROR;

		PostMessage(WM_TCPEVENT, fileObj->conInfo->sd, FD_CLOSE);
		return	TRUE;
	}

	DWORD	id;	// �g�킸�i95�n�� error �ɂȂ�̂�h�������j
	fileObj->hThread = (HANDLE)~0;	// �����ȗ̈�������
	// thread ���ł� MT �Ή����K�v�� crt �͎g�킸
	if ((fileObj->hThread = ::CreateThread(NULL, 0, RecvFileThread, this, 0, &id)) == NULL)
	{
		EndRecvFile();
		return	FALSE;
	}

	return	TRUE;
}

DWORD WINAPI TRecvDlg::RecvFileThread(void *_recvDlg)
{
	TRecvDlg	*recvDlg = (TRecvDlg *)_recvDlg;
	RecvFileObj	*fileObj = recvDlg->fileObj;
	fd_set		rfd;
	timeval		tv;
	int			sock_ret;
	BOOL		(TRecvDlg::*RecvFileFunc)(void) =
				fileObj->isDir ? &TRecvDlg::RecvDirFile : &TRecvDlg::RecvFile;

	FD_ZERO(&rfd);
	FD_SET(fileObj->conInfo->sd, &rfd);

	for (int waitCnt=0; waitCnt < 120 && fileObj->hThread != NULL; waitCnt++)
	{
		tv.tv_sec = 1, tv.tv_usec = 0;
		if ((sock_ret = ::select(fileObj->conInfo->sd + 1, &rfd, NULL, NULL, &tv)) > 0)
		{
			waitCnt = 0;
			if ((recvDlg->*RecvFileFunc)() != TRUE)
				break;
			if (fileObj->status == FS_COMPLETE)
				break;
		}
		else if (sock_ret == 0) {
			FD_ZERO(&rfd);
			FD_SET(fileObj->conInfo->sd, &rfd);
			fileObj->conInfo->lastTick = ::GetTickCount();
			recvDlg->PostMessage(WM_RECVDLG_FILEBUTTON, 0, 0);
		}
		else if (sock_ret == SOCKET_ERROR) {
			break;
		}
	}
	recvDlg->CloseRecvFile(fileObj->status == FS_COMPLETE ? TRUE : FALSE);
	if (fileObj->status != FS_COMPLETE)
		fileObj->status = FS_ERROR;

	recvDlg->PostMessage(WM_TCPEVENT, fileObj->conInfo->sd, FD_CLOSE);
	::ExitThread(0);
	return	0;
}

BOOL TRecvDlg::CloseRecvFile(BOOL setAttr)
{
	if (fileObj->hFile != INVALID_HANDLE_VALUE)
	{
		if (setAttr)
		{
			FILETIME	ft;
			UnixTime2FileTime(fileObj->curFileInfo.Mtime(), &ft);
#if 1	// �b�菈�u�iprotocol format �ύX�̉\���j
			if (fileObj->isDir || (fileObj->curFileInfo.Mtime() & 0xffffff00))
#endif
				::SetFileTime(fileObj->hFile, NULL, &ft, &ft);
		}
		fileObj->totalTrans += fileObj->offset;
		fileObj->totalFiles++;
		fileObj->offset = fileObj->woffset = 0;

		::CloseHandle(fileObj->hFile);
		fileObj->hFile = INVALID_HANDLE_VALUE;
	}
	return	TRUE;
}

BOOL TRecvDlg::DecodeDirEntry(char *buf, FileInfo *info, char *u8fname)
{
	char	*tok, *ptr, *p;

	ConvertShareMsgEscape(buf);	// "::" -> ';'

	if ((tok = separate_token(buf, ':', &p)) == NULL)	// header size
		return	FALSE;

	if ((tok = separate_token(NULL, ':', &p)) == NULL)	// fname
		return	FALSE;
	WCHAR	wbuf[MAX_PATH];
	AtoW(tok, wbuf, MAX_PATH);
	WtoU8(wbuf, u8fname, MAX_PATH_U8);
	info->SetFnameExt(u8fname);
	while ((ptr = strchr(tok, '?')) != NULL)	// UNICODE �܂ł̎b��
		*ptr = '_';

	if (strlen(tok) >= MAX_PATH_U8)
		return	FALSE;

	if ((tok = separate_token(NULL, ':', &p)) == NULL)	// size
		return	FALSE;
	info->SetSize(hex2ll(tok));

	if ((tok = separate_token(NULL, ':', &p)) == NULL)	// attr
		return	FALSE;
	info->SetAttr(strtoul(tok, 0, 16));

	while ((tok = separate_token(NULL, ':', &p)) != NULL)	// exattr
	{
		if ((ptr = strchr(tok, '=')) == NULL)
			continue;
		*ptr = 0;

		UINT	exattr = strtoul(tok, 0, 16);
		UINT	val = strtoul(ptr + 1, 0, 16);

		switch (exattr) {
		case IPMSG_FILE_MTIME:		info->SetMtime(val); break;
//		case IPMSG_FILE_CREATETIME:	info->SetCrtime(val); break;	����ł͎g��Ȃ�
//		case IPMSG_FILE_ATIME:		info->SetAtime(val); break;		����ł͎g��Ȃ�
		default: break;
		}
	}
	return	TRUE;
}

BOOL TRecvDlg::RecvDirFile(void)
{
#define BIG_ALLOC	50
#define PEEK_SIZE	8

	if (fileObj->status == FS_DIRFILESTART || fileObj->status == FS_TRANSINFO)
	{
		int		size;
		if (fileObj->infoLen == 0)
		{
			if ((size = ::recv(fileObj->conInfo->sd, fileObj->info + (int)fileObj->offset, PEEK_SIZE - (int)fileObj->offset, 0)) <= 0)
				return	FALSE;
			if ((fileObj->offset += size) < PEEK_SIZE)
				return	TRUE;
			fileObj->info[fileObj->offset] = 0;
			if ((fileObj->infoLen = strtoul(fileObj->info, 0, 16)) >= sizeof(fileObj->info) -1 || fileObj->infoLen <= 0)
				return	FALSE;	// too big or small
		}
		if (fileObj->offset < fileObj->infoLen)
		{
			if ((size = ::recv(fileObj->conInfo->sd, fileObj->info + (int)fileObj->offset, fileObj->infoLen - (int)fileObj->offset, 0)) <= 0)
				return	FALSE;
			fileObj->offset += size;
		}
		if (fileObj->offset == fileObj->infoLen)
		{
			fileObj->info[fileObj->infoLen] = 0;
			if (DecodeDirEntry(fileObj->info, &fileObj->curFileInfo, fileObj->u8fname) == FALSE)
				return	FALSE;	// Illegal entry
			fileObj->offset = fileObj->infoLen = 0;	// ������

			if (GET_MODE(fileObj->curFileInfo.Attr()) == IPMSG_FILE_DIR)
			{
				char	buf[MAX_BUF];
				const char *fname = fileObj->dirCnt == 0 ? fileObj->fileInfo->Fname() : fileObj->curFileInfo.Fname();

				if (MakePath(buf, fileObj->path, fname) >= MAX_PATH_U8)
					return	MessageBoxU8(buf, GetLoadStrU8(IDS_PATHTOOLONG)), FALSE;
				if (IsSafePath(buf, fname) == FALSE)
					return	FALSE;

				if (CreateDirectoryU8(buf, NULL) == FALSE)
					return	FALSE;
				strncpyz(fileObj->path, buf, MAX_PATH_U8);
				fileObj->dirCnt++;
			}
			else if (GET_MODE(fileObj->curFileInfo.Attr()) == IPMSG_FILE_RETPARENT)
			{
				if (fileObj->curFileInfo.Mtime())	// directory �� time stamp �����킹��(NT�n�̂�)
				{
					FILETIME	ft;
					HANDLE		hFile;
					UnixTime2FileTime(fileObj->curFileInfo.Mtime(), &ft);
					if ((hFile = CreateFileU8(fileObj->path, GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0)) != INVALID_HANDLE_VALUE)
					{
						::SetFileTime(hFile, NULL, NULL, &ft);
						::CloseHandle(hFile);
					}
				}
				if (fileObj->curFileInfo.Attr() & IPMSG_FILE_RONLYOPT)
				SetFileAttributesU8(fileObj->path, FILE_ATTRIBUTE_READONLY);
				if (--fileObj->dirCnt <= 0)
				{
					fileObj->status = FS_COMPLETE;
					return	TRUE;
				}
				if (PathToDir(fileObj->path, fileObj->path) == FALSE)
					return	FALSE;
			}
			else {
				if (fileObj->dirCnt == 0)
					return	FALSE;
				
				if (fileObj->curFileInfo.Size() == 0)	// 0byte file
				{
					if (OpenRecvFile())		// 0byte�̏ꍇ�͍쐬���s�𖳎�
						CloseRecvFile(TRUE);
				}
				fileObj->status = fileObj->curFileInfo.Size() ? FS_TRANSFILE : FS_TRANSINFO;
			}
			return	TRUE;
		}
	}

	if (fileObj->status == FS_TRANSFILE)
	{
		if (RecvFile() != TRUE)
		{
			CloseRecvFile();
			return	FALSE;
		}
		if (fileObj->status == FS_ENDFILE)
		{
			CloseRecvFile(TRUE);
			fileObj->status = FS_TRANSINFO;
		}
	}

	return	TRUE;
}

BOOL TRecvDlg::OpenRecvFile(void)
{
	char	path[MAX_BUF];

	if (MakePath(path, fileObj->isDir ? fileObj->path : fileObj->saveDir, fileObj->curFileInfo.Fname()) >= MAX_PATH_U8)
		return	MessageBoxU8(path, GetLoadStrU8(IDS_PATHTOOLONG)), FALSE;
	if (IsSafePath(path, fileObj->curFileInfo.Fname()) == FALSE)
		return	MessageBoxU8(path, GetLoadStrU8(IDS_NOTSAFEPATH)), FALSE;

	if ((fileObj->hFile = CreateFileU8(path, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0)) == INVALID_HANDLE_VALUE)
		return	fileObj->isDir ? FALSE : (MessageBoxU8(GetLoadStrU8(IDS_CREATEFAIL), path), FALSE);

	if (fileObj->curFileInfo.Attr() & IPMSG_FILE_RONLYOPT)
		SetFileAttributesU8(path, FILE_ATTRIBUTE_READONLY);

//::SetFilePointer(fileObj->hFile, OFFSET, 0, FILE_BEGIN);
//::SetEndOfFile(fileObj->hFile);

	return	TRUE;
}

BOOL TRecvDlg::RecvFile(void)
{
	int		wresid = (int)(fileObj->offset - fileObj->woffset);
	_int64	remain = fileObj->curFileInfo.Size() - fileObj->offset;
	int		size = 0;

	if (remain > cfg->TransMax - wresid)
		remain = cfg->TransMax - wresid;

	if ((size = ::recv(fileObj->conInfo->sd, fileObj->recvBuf + wresid, (int)remain, 0)) <= 0)
		return	FALSE;

	if (fileObj->hFile == INVALID_HANDLE_VALUE)
		if (OpenRecvFile() == FALSE)
			return	FALSE;

	wresid += size;
	if (fileObj->offset + size >= fileObj->curFileInfo.Size() || cfg->TransMax == wresid)
	{
		DWORD	wsize;
		if (::WriteFile(fileObj->hFile, fileObj->recvBuf, wresid, &wsize, 0) != TRUE || wresid != (int)wsize)
			return	MessageBoxU8(GetLoadStrU8(IDS_WRITEFAIL)), FALSE;
		fileObj->woffset += wresid;
	}
	fileObj->offset += size;

	DWORD	nowTick = ::GetTickCount();

	if (nowTick - fileObj->conInfo->lastTick >= 1000)
	{
		fileObj->conInfo->lastTick = nowTick;
		PostMessage(WM_RECVDLG_FILEBUTTON, 0, 0);
	}

	if (fileObj->offset >= fileObj->curFileInfo.Size())
		fileObj->status = fileObj->isDir ? FS_ENDFILE : FS_COMPLETE;

	return	TRUE;
}

int MakeTransRateStr(char *buf, DWORD ticks, _int64 cur_size, _int64 total_size)
{
	int len = 0;
	buf[len++] = ' ';
	len += MakeSizeString(buf + len, cur_size) -2;	// "MB"�����𔲂�
	buf[len++] = '/';
	len += MakeSizeString(buf + len, total_size);
	buf[len++] = ' ';
	len += MakeSizeString(buf + len, cur_size * 1000 / (ticks ? ticks : 10));
	return len + wsprintf(buf + len, "/s (%d%%)", (int)(cur_size * 100 / (total_size ? total_size : 1)));
}

int MakeDirTransRateStr(char *buf, DWORD ticks, _int64 cur_size, int files)
{
	int len = 0;
	buf[len++] = ' ';
	len += wsprintf(buf + len, "Total ");
	len += MakeSizeString(buf + len, cur_size);
	len += wsprintf(buf + len, "/%dfiles (", files);
	len += MakeSizeString(buf + len, cur_size * 1000 / (ticks ? ticks : 1));
	return	len + wsprintf(buf + len, "/s)" );
}

class RecvTransEndDlg : public TDlg {
	RecvFileObj	*fileObj;

public:
	RecvTransEndDlg(RecvFileObj *_fileObj, TWin *_win) : TDlg(_fileObj->status == FS_COMPLETE ? TRANSEND_DIALOG : SUSPEND_DIALOG, _win) { fileObj = _fileObj; }
	virtual BOOL	EvCreate(LPARAM lParam);
	virtual BOOL	EvCommand(WORD wNotifyCode, WORD wID, LPARAM hwndCtl);
};

BOOL RecvTransEndDlg::EvCreate(LPARAM lParam)
{
	char	buf[MAX_BUF];
	DWORD	difftick = fileObj->lastTick - fileObj->startTick;
	int		len = 0;

	len += wsprintf(buf + len, "Total: ");
	len += MakeSizeString(buf + len, fileObj->totalTrans);
	len += wsprintf(buf + len, " (");
	len += MakeSizeString(buf + len, fileObj->totalTrans * 1000 / (difftick ? difftick : 1));
	len += wsprintf(buf + len, "/s)\r\n%d", difftick/1000);
	if (difftick/1000 < 20)
		len += wsprintf(buf + len, ".%02d", (difftick%1000) / 10);
	len += wsprintf(buf + len, " sec   ");
	if (fileObj->totalFiles > 1 || fileObj->isDir)
		len += wsprintf(buf + len, "%d files", fileObj->totalFiles);
	else
		len += wsprintf(buf + len, "%s", fileObj->fileInfo->Fname());

	if (fileObj->status == FS_COMPLETE)
	{
		if (fileObj->totalFiles > 1 || fileObj->isDir)
			::EnableWindow(GetDlgItem(EXEC_BUTTON), FALSE);
	}

	SetDlgItemTextU8(FILE_STATIC, buf);

	GetWindowRect(&rect);
	MoveWindow(rect.left + 30, rect.top + 30, rect.right - rect.left, rect.bottom - rect.top, TRUE);
	return	TRUE;
}

BOOL RecvTransEndDlg::EvCommand(WORD wNotifyCode, WORD wID, LPARAM hwndCtl)
{
	if (fileObj->status == FS_COMPLETE && wID == IDCANCEL)
		wID = IDOK;

	switch (wID)
	{
	case FOLDER_BUTTON: case EXEC_BUTTON: case IDCANCEL: case IDOK: case IDRETRY:
		EndDialog(wID);
		return	TRUE;
	}

	return	FALSE;
}

BOOL TRecvDlg::EndRecvFile(BOOL manual_suspend)
{
	if (fileObj->hThread)
	{
		HANDLE	hThread = fileObj->hThread;
		fileObj->hThread = 0;	// ���f�̍��}
		WaitForSingleObject(hThread, INFINITE);
		::CloseHandle(hThread);
	}

	fileObj->lastTick = fileObj->conInfo->lastTick = ::GetTickCount();
	SetTransferButtonText();

	int			target = ShareMng::GetFileInfoNo(shareInfo, fileObj->fileInfo);
	FileInfo	*fileInfo = fileObj->fileInfo;
	BOOL		isSingleTrans = fileObj->startTick == fileObj->conInfo->startTick;

	::closesocket(fileObj->conInfo->sd);
	delete [] fileObj->recvBuf;
	delete fileObj->conInfo;
	fileObj->conInfo = NULL;

	if (fileObj->status == FS_COMPLETE)
	{
		for (int cnt=0; cnt < shareInfo->fileCnt; cnt++)
		{
			if (shareInfo->fileInfo[cnt]->IsSelected() && shareInfo->fileInfo[cnt] != fileInfo)
			{
				FreeDecodeShareMsgFile(shareInfo, target);
				return	SaveFile();
			}
		}
	}

	int ret = manual_suspend ? IDCANCEL : RecvTransEndDlg(fileObj, this).Exec();

	if (ret == EXEC_BUTTON || ret == FOLDER_BUTTON && fileObj->isDir && isSingleTrans)
	{
		char	buf[MAX_BUF];
		MakePath(buf, fileObj->saveDir, fileInfo->Fname());
		ShellExecuteU8(NULL, NULL, buf, 0, 0, SW_SHOW);
	}
	else if (ret == FOLDER_BUTTON)
		ShellExecuteU8(NULL, NULL, fileObj->saveDir, 0, 0, SW_SHOW);

	if (ret == IDOK || ret == FOLDER_BUTTON || ret == EXEC_BUTTON)
		FreeDecodeShareMsgFile(shareInfo, target);

	SetFileButton(this, FILE_BUTTON, shareInfo);
	EvSize(SIZE_RESTORED, 0, 0);

	if (ret == IDRETRY)
		PostMessage(WM_COMMAND, FILE_BUTTON, 0);

	return	TRUE;
}

void TRecvDlg::SetTransferButtonText(void)
{
	char	buf[MAX_LISTBUF];

	if (fileObj->conInfo == NULL)
		return;
	if (fileObj->isDir)
		MakeDirTransRateStr(buf, fileObj->conInfo->lastTick - fileObj->startTick, fileObj->totalTrans + fileObj->offset, fileObj->totalFiles);
	else
		MakeTransRateStr(buf, fileObj->conInfo->lastTick - fileObj->conInfo->startTick, fileObj->status < FS_COMPLETE ? fileObj->offset : fileObj->curFileInfo.Size(), fileObj->curFileInfo.Size());
	SetDlgItemTextU8(FILE_BUTTON, buf);
}

