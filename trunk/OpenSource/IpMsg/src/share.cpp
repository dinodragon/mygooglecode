static char *share_id = 
	"@(#)Copyright (C) H.Shirouzu 2002   share.cpp	Ver2.10";
/* ========================================================================
	Project  Name			: IP Messenger for Win32
	Module Name				: File Share
	Create					: 2002-04-14(Sun)
	Update					: 2010-09-18(Sat)
	Copyright				: H.Shirouzu
	Reference				: 
	======================================================================== */

#include "resource.h"
#include "ipmsg.h"
#include <stddef.h>

#define BIG_ALLOC 5

/*
	���J�t�@�C���Ǘ�
*/
ShareMng::ShareMng(Cfg *_cfg)
{
	top = (ShareInfo *)&_top;	// �ԕ�
	top->prior = top->next = top;
	cfg = _cfg;
	statDlg = NULL;
}

ShareInfo *ShareMng::CreateShare(int packetNo)
{
	if (Search(packetNo) != NULL)
		return	FALSE;

	ShareInfo *info = new ShareInfo(packetNo);
	info->LinkList(top);

	return	info;
}

BOOL ShareMng::AddFileShare(ShareInfo *info, char *fname)
{
	for (int cnt=0; cnt < info->fileCnt; cnt++)
		if (strcmp(fname, info->fileInfo[cnt]->Fname()) == 0)
			return	FALSE;

	FileInfo	*fileInfo = new FileInfo;
	if (SetFileInfo(fname, fileInfo) == FALSE)
		return	FALSE;

	if ((info->fileCnt % BIG_ALLOC) == 0)
		info->fileInfo = (FileInfo **)realloc(info->fileInfo, (info->fileCnt + BIG_ALLOC) * sizeof(FileInfo *));
	info->fileInfo[info->fileCnt] = fileInfo;
	info->fileCnt++;

	return	TRUE;
}

BOOL ShareMng::DelFileShare(ShareInfo *info, int fileNo)
{
	if (fileNo >= info->fileCnt)
		return	FALSE;
	memmove(info->fileInfo + fileNo, info->fileInfo + fileNo +1, (--info->fileCnt - fileNo) * sizeof(FileInfo *));

	statDlg->Refresh();

	return	TRUE;
}

BOOL ShareMng::SetFileInfo(char *fname, FileInfo *info)
{
	WIN32_FIND_DATA_U8	fdat;

	if (GetFileInfomationU8(fname, &fdat, FALSE) != TRUE)
		return	FALSE;

	UINT	attr = (fdat.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? IPMSG_FILE_DIR : IPMSG_FILE_REGULAR;
	attr |= (fdat.dwFileAttributes & FILE_ATTRIBUTE_READONLY) ? IPMSG_FILE_RONLYOPT : 0;
	attr |= (fdat.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) ? IPMSG_FILE_SYSTEMOPT : 0;
	info->SetAttr(attr);
	info->SetFname(fname);
	if (GET_MODE(info->Attr()) == IPMSG_FILE_DIR)
	{
		info->SetSize(0);
		strncpyz(cfg->lastOpenDir, fname, MAX_PATH_U8);
	}
	else {
		info->SetSize((_int64)fdat.nFileSizeHigh << 32 | fdat.nFileSizeLow);
		PathToDir(fname, cfg->lastOpenDir);
	}
	info->SetMtime(FileTime2UnixTime(&fdat.ftLastWriteTime));

	return	TRUE;
}

BOOL ShareMng::AddHostShare(ShareInfo *info, SendEntry *entry, int entryNum)
{
	info->host = new Host *[info->hostCnt = entryNum];
	info->transStat = new char [info->hostCnt * info->fileCnt];
	memset(info->transStat, TRANS_INIT, info->hostCnt * info->fileCnt);

	for (int cnt=0; cnt < entryNum; cnt++)
	{
		info->host[cnt] = (Host *)cfg->fileHosts.GetHostByNameAddr(&entry[cnt].Host()->hostSub);
		if (info->host[cnt] == NULL)
		{
			info->host[cnt] = new Host;
			info->host[cnt]->hostSub = entry[cnt].Host()->hostSub;
			strncpyz(info->host[cnt]->nickName, entry[cnt].Host()->nickName, MAX_NAMEBUF);
			cfg->fileHosts.AddHost(info->host[cnt]);
		}
		else info->host[cnt]->RefCnt(1);
	}
	SYSTEMTIME	st;
	::GetSystemTime(&st);
	::SystemTimeToFileTime(&st, &info->attachTime);

	statDlg->Refresh();

	return	TRUE;
}

int ShareMng::GetFileInfoNo(ShareInfo *info, FileInfo *fileInfo)
{
	for (int target=0; info->fileCnt; target++)
		if (info->fileInfo[target] == fileInfo)
			return	target;
	return	-1;
}

BOOL ShareMng::EndHostShare(int packetNo, HostSub *hostSub, FileInfo *fileInfo, BOOL done)
{
	ShareInfo *info = Search(packetNo);

	if (info == NULL)
		return	FALSE;

	for (int cnt=0; cnt < info->hostCnt; cnt++)
	{
		if (IsSameHostEx(&info->host[cnt]->hostSub, hostSub))
		{
			if (fileInfo)
			{
				info->transStat[info->fileCnt * cnt + GetFileInfoNo(info, fileInfo)] = done ? TRANS_DONE : TRANS_INIT;
				if (done == FALSE)
					return	statDlg->Refresh(), TRUE;
				for (int cnt2=0; cnt2 < info->fileCnt; cnt2++)
					if (info->transStat[info->fileCnt * cnt + cnt2] != TRANS_DONE)
						return	statDlg->Refresh(), TRUE;
			}
			if (info->host[cnt]->RefCnt(-1) == 0)
			{
				cfg->fileHosts.DelHost(info->host[cnt]);
				delete info->host[cnt];
			}
			memmove(info->host + cnt, info->host + cnt + 1, (--info->hostCnt - cnt) * sizeof(Host *));
			memmove(info->transStat + info->fileCnt * cnt, info->transStat + info->fileCnt * (cnt + 1), (info->hostCnt - cnt) * info->fileCnt);
			if (info->hostCnt == 0)
				DestroyShare(info);
			return	statDlg->Refresh(), TRUE;
		}
	}
	return	FALSE;
}

void ShareMng::DestroyShare(ShareInfo *info)
{
	info->next->prior = info->prior;
	info->prior->next = info->next;

	while (info->hostCnt-- > 0)
	{
		if (info->host[info->hostCnt]->RefCnt(-1) == 0)
		{
			cfg->fileHosts.DelHost(info->host[info->hostCnt]);
			delete info->host[info->hostCnt];
		}
	}
	delete [] info->host;
	delete [] info->transStat;

	while (info->fileCnt-- > 0)
		delete info->fileInfo[info->fileCnt];
	free(info->fileInfo);
	statDlg->Refresh();
}

ShareInfo *ShareMng::Search(int packetNo)
{
	for (ShareInfo *info=Top(); info; info=Next(info))
		if (info->packetNo == packetNo)
			return	info;
	return	NULL;
}

BOOL ShareMng::GetShareCntInfo(ShareCntInfo *cntInfo, ShareInfo *shareInfo)
{

	memset(cntInfo, 0, sizeof(ShareCntInfo));

	for (ShareInfo *info = shareInfo ? shareInfo : Top(); info; info=Next(info))
	{
		if (info->hostCnt)
		{
			cntInfo->packetCnt++;
			cntInfo->hostCnt += info->hostCnt;
			int cnt;
			for (cnt=info->fileCnt * info->hostCnt -1; cnt >= 0; cnt--)
			{
				cntInfo->fileCnt++;
				switch (info->transStat[cnt]) {
				case TRANS_INIT: break;
				case TRANS_BUSY: cntInfo->transferCnt++;	break;
				case TRANS_DONE: cntInfo->doneCnt++;		break;
				}
			}
			for (cnt=0; cnt < info->fileCnt; cnt++)
			{
				if (GET_MODE(info->fileInfo[cnt]->Attr()) == IPMSG_FILE_DIR)
					cntInfo->dirCnt++;
				cntInfo->totalSize += info->fileInfo[cnt]->Size();
			}
		}
		if (shareInfo)
			return	TRUE;
	}
	return	TRUE;
}


BOOL ShareMng::GetAcceptableFileInfo(ConnectInfo *info, char *buf, AcceptFileInfo *fileInfo)
{
	// �{���͂���ȂƂ���Ńf�R�[�h�����Amsgmng �ɂ�点��ׂ�����...
	char		*tok, *p, *user_name, *host_name;
	int			targetID;
	ShareInfo	*shareInfo;
	HostSub		hostSub = { "", "", info->addr, info->port };

	if ((tok = separate_token(buf, ':', &p)) == NULL || atoi(tok) != IPMSG_VERSION)
		return	FALSE;

	if ((tok = separate_token(NULL, ':', &p)) == NULL)	// packet no
		return	FALSE;

	if ((user_name = separate_token(NULL, ':', &p)) == NULL)
		return	FALSE;

	if ((host_name = separate_token(NULL, ':', &p)) == NULL)
		return	FALSE;

	if ((tok = separate_token(NULL, ':', &p)) == NULL)	// command
		return	FALSE;
	fileInfo->command = atoi(tok);

	if (fileInfo->command & IPMSG_UTF8OPT) {
		strncpyz(hostSub.userName, user_name, MAX_NAMEBUF);
		strncpyz(hostSub.hostName, host_name, MAX_NAMEBUF);
	}
	else {
		strncpyz(hostSub.userName, AtoU8(user_name), MAX_NAMEBUF);
		strncpyz(hostSub.hostName, AtoU8(host_name), MAX_NAMEBUF);
	}

	if ((tok = separate_token(NULL, ':', &p)) == NULL)
		return	FALSE;
	fileInfo->packetNo = strtol(tok, 0, 16);

	if ((tok = separate_token(NULL, ':', &p)) == NULL)
		return	FALSE;
	targetID = strtol(tok, 0, 16);

	if (GET_MODE(fileInfo->command) == IPMSG_GETFILEDATA)
	{
		if ((tok = separate_token(NULL, ':', &p)) == NULL)
			return	FALSE;
		fileInfo->offset = hex2ll(tok);
	}
	else if (GET_MODE(fileInfo->command) == IPMSG_GETDIRFILES)
		fileInfo->offset = 0;
	else return	FALSE;

	if ((shareInfo = Search(fileInfo->packetNo)) == NULL)
		return	FALSE;

	int	host_cnt, file_cnt;

	for (host_cnt=0; host_cnt < shareInfo->hostCnt; host_cnt++)
	{
		if (IsSameHostEx(&shareInfo->host[host_cnt]->hostSub, &hostSub))
		{
			fileInfo->host = shareInfo->host[host_cnt];
			break;
		}
	}
	if (host_cnt == shareInfo->hostCnt)
		return	FALSE;

	for (file_cnt=0; file_cnt < shareInfo->fileCnt; file_cnt++)
	{
		if (shareInfo->fileInfo[file_cnt]->Id() == targetID)
		{
			fileInfo->fileInfo = shareInfo->fileInfo[file_cnt];
			if (shareInfo->transStat[shareInfo->fileCnt * host_cnt + file_cnt] != TRANS_INIT)
				return	FALSE;	// download �ς݁ior �Œ��j
			if (GET_MODE(fileInfo->command) != IPMSG_GETDIRFILES && GET_MODE(fileInfo->fileInfo->Attr()) == IPMSG_FILE_DIR)		// dir �ɑ΂��� IPMSG_GETDIRFILES �ȊO�͔F�߂Ȃ�
				return	FALSE;
			fileInfo->attachTime = shareInfo->attachTime;
			shareInfo->transStat[shareInfo->fileCnt * host_cnt + file_cnt] = TRANS_BUSY;
			statDlg->Refresh();
			return	TRUE;
		}
	}
	return	FALSE;
}

/* ShareDlg */
TShareDlg::TShareDlg(ShareMng *_shareMng, ShareInfo *_shareInfo, Cfg *_cfg, TWin *_parent) : TDlg(FILE_DIALOG, _parent), shareListView(this)
{
	shareMng = _shareMng;
	shareInfo = _shareInfo;
	cfg = _cfg;
}

TShareDlg::~TShareDlg()
{
	SendDlgItemMessage(FILE_LIST, LVM_DELETEALLITEMS, 0, 0);
}

BOOL TShareDlg::EvCreate(LPARAM lParam)
{
	SendDlgItemMessage(FILE_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, parent->SendDlgItemMessage(HOST_LIST, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0) & ~LVS_EX_HEADERDRAGDROP);

	LV_COLUMNW	lvC;
	memset(&lvC, 0, sizeof(lvC));
	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	char	*title[] = { GetLoadStrU8(IDS_FILENAME), GetLoadStrU8(IDS_SIZE), GetLoadStrU8(IDS_LOCATION), NULL };
	int	size[] = { 120, 70, 180 };
	int	fmt[] = { LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_LEFT, LVCFMT_LEFT };
	for (lvC.iSubItem = 0; title[lvC.iSubItem]; lvC.iSubItem++)
	{
		lvC.pszText = U8toW(title[lvC.iSubItem]);
		lvC.fmt = fmt[lvC.iSubItem];
		lvC.cx = size[lvC.iSubItem];
		SendDlgItemMessageW(FILE_LIST, LVM_INSERTCOLUMNW, lvC.iSubItem, (LPARAM)&lvC);
	}

	for (int cnt=0; cnt < shareInfo->fileCnt; cnt++)
		AddList(cnt);

 	shareListView.AttachWnd(GetDlgItem(FILE_LIST));

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

	Show();
	::SetFocus(shareListView.hWnd);
	return	TRUE;
}

BOOL TShareDlg::AddList(int cnt)
{
	LV_ITEM	lvi;

	memset(&lvi, 0, sizeof(lvi));
	lvi.mask = LVIF_TEXT|LVIF_PARAM;
	lvi.iItem = cnt;
	lvi.pszText = LPSTR_TEXTCALLBACK;
	lvi.lParam = 0;
	return	SendDlgItemMessage(FILE_LIST, LVM_INSERTITEMW, 0, (LPARAM)&lvi);
}

BOOL TShareDlg::DelList(int cnt)
{
	SendDlgItemMessage(FILE_LIST, LVM_DELETEITEM, cnt, 0);
	shareMng->DelFileShare(shareInfo, cnt);
	return	TRUE;
}

BOOL TShareDlg::EvNotify(UINT ctlID, NMHDR *pNmHdr)
{
	if (pNmHdr->code == LVN_GETDISPINFOW)
	{
		LV_DISPINFOW	*dispInfo = (LV_DISPINFOW *)pNmHdr;
		const char	*fname = shareInfo->fileInfo[dispInfo->item.iItem]->Fname();
		char	buf[MAX_PATH_U8];

		switch (dispInfo->item.iSubItem) {
		case 0: ForcePathToFname(fname, buf);
				break;
		case 1: if (GET_MODE(shareInfo->fileInfo[dispInfo->item.iItem]->Attr()) == IPMSG_FILE_DIR)
					strcpy(buf, "(DIR)");
				else
					MakeSizeString(buf, shareInfo->fileInfo[dispInfo->item.iItem]->Size(), MSS_SPACE);
				break;
		case 2: PathToDir(fname, buf);
				break;
		default: return	FALSE;
		}
		U8toW(buf, lvBuf, sizeof(lvBuf)/sizeof(WCHAR));
		dispInfo->item.pszText = lvBuf;
		return	TRUE;
	}

	return	FALSE;
}

BOOL TShareDlg::EvDropFiles(HDROP hDrop)
{
	int	lastFileCnt = shareInfo->fileCnt;
	parent->EvDropFiles(hDrop);
	while (lastFileCnt < shareInfo->fileCnt)
		AddList(lastFileCnt++);
	return	TRUE;
}

BOOL TShareDlg::EvCommand(WORD wNotifyCode, WORD wID, LPARAM hWndCtl)
{
	switch (wID)
	{
	case IDOK:		EndDialog(TRUE); break;
	case IDCANCEL:	EndDialog(FALSE); break;

	case FILE_BUTTON:
		{
			int	cnt = shareInfo->fileCnt;
			if (FileAddDlg(this, shareMng, shareInfo, cfg))
				for (cnt; cnt < shareInfo->fileCnt; cnt++)
					AddList(cnt);
		}
		break;

	case FOLDER_BUTTON:
		if (BrowseDirDlg(this, GetLoadStrU8(IDS_FOLDERATTACH), cfg->lastOpenDir, cfg->lastOpenDir))
		{
			if (shareMng->AddFileShare(shareInfo, cfg->lastOpenDir))
			{
				AddList(shareInfo->fileCnt -1);
				cfg->WriteRegistry(CFG_GENERAL);
			}
		}
		break;

	case DEL_BUTTON:
		{
			for (int cnt=shareInfo->fileCnt-1; cnt >= 0; cnt--)
			{
				if ((SendDlgItemMessage(FILE_LIST, LVM_GETITEMSTATE, cnt, LVIS_SELECTED) & LVIS_SELECTED) == 0)
					continue;
				DelList(cnt);
			}
		}
		break;

	default: break;
	}
	return	TRUE;
}

BOOL TShareDlg::FileAddDlg(TDlg *dlg, ShareMng *shareMng, ShareInfo *shareInfo, Cfg *cfg)
{
	char	buf[MAX_BUF_EX] = "", path[MAX_BUF_EX];

	if (OpenFileDlg(dlg, OpenFileDlg::MULTI_OPEN).Exec(buf, GetLoadStrU8(IDS_ADDFILE), GetLoadStrAsFilter(IDS_OPENFILEALLFLTR), cfg->lastOpenDir) != TRUE)
		return	FALSE;

	cfg->WriteRegistry(CFG_GENERAL);

	int		dirlen = strlen(cfg->lastOpenDir);
	if (buf[dirlen])
		return	shareMng->AddFileShare(shareInfo, buf);

	for (char *fname=buf+dirlen+1; *fname; fname += strlen(fname) +1)
	{
		if (MakePath(path, buf, fname) >= MAX_PATH_U8)
			continue;
		shareMng->AddFileShare(shareInfo, path);
	}
	return	TRUE;
}

/* TShareStatDlg */
TShareStatDlg::TShareStatDlg(ShareMng *_shareMng, Cfg *_cfg, TWin *_parent) : TDlg(SHARE_DIALOG, _parent), shareListView(this)
{
	shareMng = _shareMng;
	cfg = _cfg;
	shareMng->RegisterShareStatDlg(this);
}

TShareStatDlg::~TShareStatDlg()
{
	SendDlgItemMessage(SHARE_LIST, LVM_DELETEALLITEMS, 0, 0);
}

BOOL TShareStatDlg::EvCreate(LPARAM lParam)
{
	SendDlgItemMessage(SHARE_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, SendDlgItemMessage(SHARE_LIST, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0) | LVS_EX_FULLROWSELECT | (cfg->GlidLineCheck ? LVS_EX_GRIDLINES : 0));

	LV_COLUMNW	lvC;
	memset(&lvC, 0, sizeof(lvC));
	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	char	*title[] = { "No", "Files", "Size", "All/done/trans", "Users", NULL };
	int	size[] = { 30, 110, 70, 100, 100 };
	int	fmt[] = { LVCFMT_RIGHT, LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_LEFT };
	for (lvC.iSubItem = 0; title[lvC.iSubItem]; lvC.iSubItem++)
	{
		lvC.pszText = U8toW(title[lvC.iSubItem]);
		lvC.fmt = fmt[lvC.iSubItem];
		lvC.cx = size[lvC.iSubItem];
		SendDlgItemMessageW(SHARE_LIST, LVM_INSERTCOLUMNW, lvC.iSubItem, (LPARAM)&lvC);
	}

 	shareListView.AttachWnd(GetDlgItem(SHARE_LIST));
	SetAllList();

	SendDlgItemMessage(MODIFY_CHECK, BM_SETCHECK, (cfg->fileTransOpt & FT_STRICTDATE) ? TRUE : FALSE, 0);

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
	Show();
	::SetFocus(shareListView.hWnd);

	return	TRUE;
}

BOOL TShareStatDlg::Refresh(void)
{
	if (hWnd == NULL)
		return	FALSE;
	SetAllList();
	return	TRUE;
}

BOOL TShareStatDlg::SetAllList(void)
{
	SendDlgItemMessage(SHARE_LIST, LVM_DELETEALLITEMS, 0, 0);

	LV_ITEM	lvi;
	memset(&lvi, 0, sizeof(lvi));
	int	cnt = 0;

	for (ShareInfo *info=shareMng->Top(); info; info=shareMng->Next(info))
	{
		if (info->hostCnt == 0)
			continue;
		lvi.iItem = cnt++;
		lvi.mask = LVIF_TEXT|LVIF_PARAM;
		lvi.pszText = LPSTR_TEXTCALLBACK;
		lvi.lParam = (LPARAM)info->packetNo;
		SendDlgItemMessage(SHARE_LIST, LVM_INSERTITEMW, 0, (LPARAM)&lvi);
	}
	return	TRUE;
}

BOOL TShareStatDlg::DelList(int cnt)
{
	LV_ITEM	lvi;
	memset(&lvi, 0, sizeof(lvi));
	lvi.iItem = cnt;
	lvi.mask = LVIF_PARAM;
	SendDlgItemMessage(SHARE_LIST, LVM_GETITEM, 0, (LPARAM)&lvi);
	SendDlgItemMessage(SHARE_LIST, LVM_DELETEITEM, cnt, 0);
	ShareInfo *info = shareMng->Search(lvi.lParam);

	if (info == NULL)
		return	FALSE;

	for (cnt=info->fileCnt * info->hostCnt -1; cnt >= 0; cnt--)
		if (info->transStat[cnt] == ShareMng::TRANS_BUSY)
			return	FALSE;

	shareMng->DestroyShare(info);

	return	TRUE;
}

BOOL TShareStatDlg::EvNotify(UINT ctlID, NMHDR *pNmHdr)
{
	if (pNmHdr->code == LVN_GETDISPINFOW)
	{
		LV_DISPINFOW	*dispInfo = (LV_DISPINFOW *)pNmHdr;
		ShareInfo		*info = shareMng->Search(dispInfo->item.lParam);
		ShareCntInfo	cntInfo;
		char			buf[MAX_BUF] = "";
		int				len = 0, cnt;

		switch (dispInfo->item.iSubItem) {
		case 0: wsprintf(buf, "%d", dispInfo->item.iItem); break;
		case 1:
			for (cnt=0; cnt < info->fileCnt && len < sizeof(buf); cnt++)
			{
				ForcePathToFname(info->fileInfo[cnt]->Fname(), (char *)lvBuf);
				len += wsprintf(buf + len, "%s ", lvBuf);
			}
			break;
		case 2:
			shareMng->GetShareCntInfo(&cntInfo, info);
			MakeSizeString(buf, cntInfo.totalSize, MSS_SPACE);
			if (cntInfo.dirCnt)
				wsprintf(buf + strlen(buf), "/%dDIR", cntInfo.dirCnt);
			break;
		case 3:
			shareMng->GetShareCntInfo(&cntInfo, info);
			wsprintf(buf, "%d / %d/ %d", cntInfo.fileCnt, cntInfo.doneCnt, cntInfo.transferCnt);
			break;
		case 4:
			for (cnt=0; cnt < info->hostCnt && len < sizeof(buf); cnt++)
				len += wsprintf(buf + len, "%.14s(%.10s) ", *info->host[cnt]->nickName ? info->host[cnt]->nickName : info->host[cnt]->hostSub.userName, info->host[cnt]->hostSub.hostName);
			break;
		default: return	FALSE;
		}
		U8toW(buf, lvBuf, sizeof(lvBuf)/sizeof(WCHAR));
		dispInfo->item.pszText = lvBuf;
		return	TRUE;
	}

	return	FALSE;
}

BOOL TShareStatDlg::EvCommand(WORD wNotifyCode, WORD wID, LPARAM hWndCtl)
{
	switch (wID)
	{
	case IDOK:		EndDialog(TRUE); break;
	case IDCANCEL:	EndDialog(FALSE); break;
	case DEL_BUTTON:
		{
			for (int cnt=SendDlgItemMessage(SHARE_LIST, LVM_GETITEMCOUNT, 0, 0)-1; cnt >= 0; cnt--)
			{
				if ((SendDlgItemMessage(SHARE_LIST, LVM_GETITEMSTATE, cnt, LVIS_SELECTED) & LVIS_SELECTED) == 0)
					continue;
				DelList(cnt);
			}
			SetAllList();
		}
		break;
	case MODIFY_CHECK:
		cfg->fileTransOpt = SendDlgItemMessage(MODIFY_CHECK, BM_GETCHECK, 0, 0) ? FT_STRICTDATE : 0;
		cfg->WriteRegistry(CFG_GENERAL);
		break;
	default: break;
	}
	return	TRUE;
}

#define PRIOR_BUTTON	2000
#define NEXT_BUTTON		2001
#define LUMP_CHECK		2002
#define RESULT_STATIC	2003

TSaveCommonDlg::TSaveCommonDlg(ShareInfo *_shareInfo, Cfg *_cfg, TWin *_parentWin) : TDlg((UINT)0, _parentWin)
{
	parentWin = _parentWin;
	shareInfo = _shareInfo;
	cfg = _cfg;
	offset = 0;

	for (int cnt=0; cnt < shareInfo->fileCnt; cnt++)
		shareInfo->fileInfo[cnt]->SetSelected(FALSE);
}

BOOL GetParentDir(const char *srcfile, char *dir)
{
	char	path[MAX_BUF], *fname=NULL;

	if (GetFullPathNameU8(srcfile, sizeof(path), path, &fname) == 0 || fname == NULL)
		return	strcpy(dir, srcfile), FALSE;

	if (fname - path > 3 || path[1] != ':')
		*(fname - 1) = 0;
	else
		*fname = 0;		// C:\ �̏ꍇ

	strcpy(dir, path);
	return	TRUE;
}


int TSaveCommonDlg::Exec(void)
{
	modalFlg = TRUE;

	char	fname[MAX_BUF], last_dir[MAX_BUF], buf[MAX_BUF], *ext;

	// �ŏI�ۑ��f�B���N�g���������Ȃ��Ă���ꍇ�A���������̂ڂ�
	for (int cnt=0; cnt < 5; cnt++) {
		if (*cfg->lastSaveDir && GetFileAttributesU8(cfg->lastSaveDir) == 0xffffffff)
			if (PathToDir(cfg->lastSaveDir, cfg->lastSaveDir) == FALSE)
				break;
	}

	strcpy(last_dir, *cfg->lastSaveDir ? cfg->lastSaveDir : ".");

	while (1) {
		FileInfo	*fileInfo = shareInfo->fileInfo[offset];

		MakePath(fname, last_dir, fileInfo->Fname());

	// �t�@�C���_�C�A���O
		TApp::GetApp()->AddWin(this);
		BOOL	ret = OpenFileDlg(parentWin, OpenFileDlg::NODEREF_SAVE, (LPOFNHOOKPROC)TApp::WinProc).Exec(fname, GetLoadStrU8(IDS_SAVEFILE), GetLoadStrAsFilter(IDS_OPENFILEALLFLTR), last_dir);
		TApp::GetApp()->DelWin(this);
		hWnd = NULL;

		if (ret == FALSE)
			return	FALSE;

	// shortcut �̏ꍇ�́A�����N��ɔ��
		if (!isLinkFile && (ext = strrchr(fname, '.')) && stricmp(ext, ".lnk") == 0) {
			char	arg[MAX_BUF];
			if (ReadLinkU8(fname, last_dir, arg)) {
				if ((GetFileAttributesU8(last_dir) & FILE_ATTRIBUTE_DIRECTORY) == 0)
					GetParentDir(last_dir, last_dir);
			}
			continue;
		}

		fileInfo = shareInfo->fileInfo[offset];

		PathToDir(fname, last_dir);
		ForcePathToFname(fname, fname);
		fileInfo->SetSelected(TRUE);

	// �㏑���m�F
		for (int cnt=0; cnt < shareInfo->fileCnt; cnt++)
		{
			if (shareInfo->fileInfo[cnt]->IsSelected() == FALSE)
				continue;
			MakePath(buf, last_dir, offset == cnt ? fname : shareInfo->fileInfo[cnt]->Fname());
			if (GetFileAttributesU8(buf) != 0xffffffff)
			{
				if ((ret = parentWin->MessageBoxU8(GetLoadStrU8(IDS_OVERWRITE), GetLoadStrU8(IDS_ATTENTION), MB_OKCANCEL|MB_ICONEXCLAMATION) == IDOK) == FALSE)
					for (int cnt2=0; cnt2 < shareInfo->fileCnt; cnt2++)
						shareInfo->fileInfo[cnt2]->SetSelected(FALSE);
				break;
			}
		}
		if (ret) {
			fileInfo->SetFname(fname);
			strcpy(cfg->lastSaveDir, last_dir);
			cfg->WriteRegistry(CFG_GENERAL);
			return	TRUE;
		}
	}
	// not reach
}

BOOL TSaveCommonDlg::EvCreate(LPARAM lParam)
{
	RECT	ok_rect = { 0, 0, 50, 20 }, cl_rect;
	HWND	pWnd = ::GetParent(hWnd);

	::ShowWindow(::GetDlgItem(pWnd, 0x441), SW_HIDE);
	::ShowWindow(::GetDlgItem(pWnd, 0x470), SW_HIDE);

//	if (shareInfo->fileCnt == 1)
//		return	TRUE;

	if (::GetWindowRect(::GetDlgItem(pWnd, IDOK), &ok_rect) == FALSE)
		return	TRUE;

	int	ok_xsize = ok_rect.right - ok_rect.left;
	int	ok_ysize = ok_rect.bottom - ok_rect.top;

// �{�^��������2�{���L����
	SetWindowLong(GWL_STYLE, GetWindowLong(GWL_STYLE)|WS_CLIPSIBLINGS);
	::GetClientRect(pWnd, &cl_rect);
	GetWindowRect(&rect);
	MoveWindow(0, 0, cl_rect.right, (rect.bottom - rect.top) + ok_ysize * 5 / 2, FALSE);
	GetWindowRect(&rect);

	int		cx = 20, cy = ok_ysize;

	CreateWindowU8(STATIC_CLASS, "", WS_CHILD|WS_VISIBLE|SS_LEFT, cx, 0, rect.right, ok_ysize, hWnd, (HMENU)RESULT_STATIC, TApp::GetInstance(), NULL);

	DWORD	flg = (shareInfo->fileCnt == 1 ? WS_DISABLED : 0)|WS_CHILD|WS_VISIBLE;
	CreateWindowU8(BUTTON_CLASS, GetLoadStrU8(IDS_PREVBUTTON), flg | BS_PUSHBUTTON, cx, cy, ok_xsize, ok_ysize, hWnd, (HMENU)PRIOR_BUTTON, TApp::GetInstance(), NULL);
	CreateWindowU8(BUTTON_CLASS, GetLoadStrU8(IDS_NEXTBUTTON), flg | BS_PUSHBUTTON, cx+=ok_xsize+20, cy, ok_xsize, ok_ysize, hWnd, (HMENU)NEXT_BUTTON, TApp::GetInstance(), NULL);

	CreateWindowU8(BUTTON_CLASS, "", WS_CHILD|WS_VISIBLE|BS_CHECKBOX, cx+=ok_xsize+20, cy, ok_xsize * 2, ok_ysize, hWnd, (HMENU)LUMP_CHECK, TApp::GetInstance(), NULL);

	HFONT	hDlgFont = (HFONT)::SendDlgItemMessage(pWnd, IDOK, WM_GETFONT, 0, 0L);
	if (hDlgFont)
	{
		SendDlgItemMessage(RESULT_STATIC, WM_SETFONT, (UINT)hDlgFont, 0L);
		SendDlgItemMessage(PRIOR_BUTTON, WM_SETFONT, (UINT)hDlgFont, 0L);
		SendDlgItemMessage(NEXT_BUTTON, WM_SETFONT, (UINT)hDlgFont, 0L);
		SendDlgItemMessage(LUMP_CHECK, WM_SETFONT, (UINT)hDlgFont, 0L);
	}
	SetInfo();
	if (cfg->LumpCheck)
		LumpCheck();

	return	TRUE;
}

BOOL TSaveCommonDlg::EvCommand(WORD wNotifyCode, WORD wID, LPARAM hwndCtl)
{
	switch (wID) {
	case PRIOR_BUTTON:
		if (offset > 0)
			offset--;
		SetInfo();
		return	TRUE;

	case NEXT_BUTTON:
		if (offset < shareInfo->fileCnt -1)
			offset++;
		SetInfo();
		return	TRUE;

	case LUMP_CHECK:
		LumpCheck();
		return	TRUE;
	}
	return	FALSE;
}

BOOL TSaveCommonDlg::LumpCheck()
{
	cfg->LumpCheck = SendDlgItemMessage(LUMP_CHECK, BM_GETCHECK, 0, 0) == 0;
	SendDlgItemMessage(LUMP_CHECK, BM_SETCHECK, cfg->LumpCheck, 0);
	for (int cnt=0; cnt < shareInfo->fileCnt; cnt++)
		shareInfo->fileInfo[cnt]->SetSelected(cfg->LumpCheck);
	return	TRUE;
}

BOOL TSaveCommonDlg::EventUser(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return	FALSE;
}

BOOL TSaveCommonDlg::SetInfo(void)
{
	char	buf[MAX_BUF], sizestr[MAX_LISTBUF];
	Wstr	fname_w(shareInfo->fileInfo[offset]->Fname());

	::SetDlgItemTextW(::GetParent(hWnd), 0x480, fname_w.Buf());

	if (GET_MODE(shareInfo->fileInfo[offset]->Attr()) == IPMSG_FILE_DIR)
		strcpy(sizestr, GetLoadStrU8(IDS_DIRSAVE));
	else
		MakeSizeString(sizestr, shareInfo->fileInfo[offset]->Size());

	wsprintf(buf, GetLoadStrU8(IDS_FILEINFO), offset + 1, shareInfo->fileCnt, shareInfo->fileInfo[offset]->Fname(), sizestr);
	SetDlgItemTextU8(RESULT_STATIC, buf);

	_int64	total_size = 0;
	for (int cnt=0; cnt < shareInfo->fileCnt; cnt++)
		total_size += shareInfo->fileInfo[cnt]->Size();
	MakeSizeString(sizestr, total_size);
	wsprintf(buf, GetLoadStrU8(IDS_LUMPBUTTON), sizestr, shareInfo->fileCnt);
	SetDlgItemTextU8(LUMP_CHECK, buf);

	const char	*ext = strrchr(shareInfo->fileInfo[offset]->Fname(), '.');
	isLinkFile = (ext && stricmp(ext, ".lnk") == 0) ? TRUE : FALSE;

	return	TRUE;
}


/*
	�t�@�C�����L�i�Y�t�j�����G���R�[�h
*/
BOOL EncodeShareMsg(ShareInfo *info, char *buf, int bufsize)
{
	int		offset=0;
	char	fname[MAX_PATH_U8];

	*buf = 0;
	for (int cnt=0; cnt < info->fileCnt; cnt++)
	{
		ForcePathToFname(info->fileInfo[cnt]->Fname(), fname);
		info->fileInfo[cnt]->SetId(cnt);
		offset += sprintf(buf + offset, "%d:%s:%I64x:%x:%x:%c",
					cnt, fname, info->fileInfo[cnt]->Size(), info->fileInfo[cnt]->Mtime(),
					info->fileInfo[cnt]->Attr(), FILELIST_SEPARATOR);

		if (offset + MAX_BUF > bufsize)
			break;
	}
	return	TRUE;
}

/*
	�t�@�C������ ':' ���܂ޏꍇ�A"::" �ƃG�X�P�[�v����Ă��邪�A
	Windows �ł͎g���Ȃ��̂ŁA';' �ɒu��������
*/
void ConvertShareMsgEscape(char *str)
{
	char	*ptr;
	while ((ptr = strstr(str, "::")) != NULL)
	{
		*ptr++ = ';';
		memmove(ptr, ptr + 1, strlen(ptr));
	}
}

/*
	�t�@�C�����L�i�Y�t�j�����f�R�[�h
	���ӁF�j��Ǐo���B�g�p���I��莟�� FreeDecodeShareMsg ���Ăяo�����ƁB
*/
ShareInfo *DecodeShareMsg(char *buf)
{
	ShareInfo	*shareInfo = new ShareInfo;
	FileInfo	*fileInfo = NULL;
	char		*tok, *p, *p2, *p3;
	char		*file = separate_token(buf, FILELIST_SEPARATOR, &p);

	for (int cnt=0; file; cnt++, file=separate_token(NULL, FILELIST_SEPARATOR, &p))
	{
		ConvertShareMsgEscape(file);	// "::" -> ';'
		if ((tok = separate_token(file, ':', &p2)) == NULL)
			break;
		fileInfo = new FileInfo(atoi(tok));

		if ((tok = separate_token(NULL, ':', &p2)) == NULL || strlen(tok) >= MAX_FILENAME)
			break;
		while ((p3 = strchr(tok, '?')) != NULL)	// UNICODE �Ή��܂ł̎b��
			*p3 = '_';
		if (!IsValidFileName(tok))
			break;
		fileInfo->SetFname(tok);

		if ((tok = separate_token(NULL, ':', &p2)) == NULL)
			break;
		fileInfo->SetSize(hex2ll(tok));

		if ((tok = separate_token(NULL, ':', &p2)) == NULL)
			break;
		fileInfo->SetMtime(strtoul(tok, 0, 16));

		if ((tok = separate_token(NULL, ':', &p2)))
		{
			fileInfo->SetAttr(strtoul(tok, 0, 16));
			u_int	attr_type = GET_MODE(fileInfo->Attr());
			if (attr_type != IPMSG_FILE_DIR && attr_type != IPMSG_FILE_REGULAR)
			{
				delete fileInfo;
				continue;
			}
		}
		else fileInfo->SetAttr(IPMSG_FILE_REGULAR);

		if ((shareInfo->fileCnt % BIG_ALLOC) == 0)
			shareInfo->fileInfo = (FileInfo **)realloc(shareInfo->fileInfo, (shareInfo->fileCnt + BIG_ALLOC) * sizeof(FileInfo *));

		shareInfo->fileInfo[shareInfo->fileCnt++] = fileInfo;
		fileInfo = NULL;
	}
	if (fileInfo)	// �f�R�[�h���ɔ�����
		delete fileInfo;

	if (shareInfo->fileCnt <= 0)
	{
		delete shareInfo;
		return	NULL;
	}
	return	shareInfo;
}

/*
	�f�R�[�h���̊J��
*/
BOOL FreeDecodeShareMsg(ShareInfo *info)
{
	while (info->fileCnt-- > 0)
		delete info->fileInfo[info->fileCnt];
	free(info->fileInfo);
	delete info;
	return	TRUE;
}

/*
	�f�R�[�h�����̃t�@�C�����폜
*/
BOOL FreeDecodeShareMsgFile(ShareInfo *info, int index)
{
	if (index >= info->fileCnt)
		return	FALSE;
	delete info->fileInfo[index];
	memmove(info->fileInfo + index, info->fileInfo + index +1, sizeof(FileInfo *) * (--info->fileCnt - index));
	return	TRUE;
}

ShareInfo::ShareInfo(int _packetNo)
{
	packetNo = _packetNo;
	host = NULL;
	transStat = NULL;
	fileInfo = NULL;
	hostCnt = fileCnt = 0;
}

void ShareInfo::LinkList(ShareInfo *top)
{
	prior = top->prior;
	next = top;
	top->prior->next = this;
	top->prior = this;
}

BOOL GetFileInfomationU8(const char *path, WIN32_FIND_DATA_U8 *fdata, BOOL need_fname)
{
	HANDLE	fh;

	if ((fh = FindFirstFileU8(path, fdata)) != INVALID_HANDLE_VALUE)
	{
		::FindClose(fh);
		return	TRUE;
	}

//	if (need_fname)
//		return	FALSE;

//	memset(fdata, 0, sizeof(WIN32_FIND_DATA_U8));

	if ((fh = CreateFileU8(path, GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0)) != INVALID_HANDLE_VALUE)
	{
		BY_HANDLE_FILE_INFORMATION	info;
		BOOL	info_ret = ::GetFileInformationByHandle(fh, &info);
		::CloseHandle(fh);
		if (info_ret)
			return	memcpy(fdata, &info, (char *)&info.dwVolumeSerialNumber - (char *)&info), TRUE;
	}

	return	(fdata->dwFileAttributes = GetFileAttributesU8(path)) == 0xffffffff ? FALSE : TRUE;
}

