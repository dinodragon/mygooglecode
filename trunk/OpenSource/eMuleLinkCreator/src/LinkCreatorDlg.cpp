//this file is part of eMule
//Copyright (C)2004 Merkur ( merkur-@users.sourceforge.net / http://www.emule-project.net )
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "stdafx.h"
#include <winsock2.h>

#include "LinkCreator.h"
#include "LinkCreatorDlg.h"
#include "filehasher.h"
#include "functions.h"
#include "SHAHashSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg-Dialogfeld für Anwendungsbefehl 'Info'

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	void Localize();

// Dialogfelddaten
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();

// Implementierung
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	Localize();

	return TRUE; 
}

void CAboutDlg::Localize()
{
	if (!m_hWnd)
		return;

	static const UINT ids[] = {
		IDC_STATIC1, IDC_STATIC2
	};
	ModifyStyleEx(WNDEXSTYLE,GetWndExStyle());
	for (int i=0; i<ARRSIZE(ids); i++)
		GetDlgItem(ids[i])->ModifyStyleEx(WNDEXSTYLE,GetWndExStyle());

	CString buffer;
	buffer.Format(_T("%s v%s"),GetResString(IDS_LINKCREATOR),theApp.GetVersion());
	GetDlgItem(IDC_STATIC1)->SetWindowText(buffer);

	buffer.Format(GetResString(IDS_COPYRIGHTS),"2004-2005");
	GetDlgItem(IDC_STATIC2)->SetWindowText(buffer);

	GetDlgItem(IDC_STATIC3)->SetWindowText(GetResString(IDS_TRANSLATION));
	GetDlgItem(IDOK)->SetWindowText(GetResString(IDS_OK));
	SetWindowText(GetResString(IDS_ABOUT));
}


// CLinkCreatorDlg Dialogfeld



CLinkCreatorDlg::CLinkCreatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLinkCreatorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pKnownFile = NULL;
}

void CLinkCreatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILEPATH, m_ctrFilePath);
	DDX_Control(pDX, IDC_WITHHASHSET, m_ctrlWithHashset);
	DDX_Control(pDX, IDC_RESULT, m_ctrlResults);
	DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProgress);
	DDX_Control(pDX, IDC_HTTPLIST, m_ctrlHttpSources);
	DDX_Control(pDX, IDC_CLIENTSOURCESLIST, m_ctrlClientSources);
	DDX_Control(pDX, IDC_WITHAICH, m_ctrlAICH);
	DDX_Control(pDX, IDC_LANGCOMBO, m_ctrlLang);
}

BEGIN_MESSAGE_MAP(CLinkCreatorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_START, OnBnClickedStart)
	ON_BN_CLICKED(IDC_CANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_EXIT, OnClose)
	ON_BN_CLICKED(IDC_ADDHTTP, OnBnClickedAddhttp)
	ON_BN_CLICKED(IDC_HTTPCLEAR, OnBnClickedHttpclear)
	ON_BN_CLICKED(IDC_HTTPREMOVE, OnBnClickedHttpremove)
	ON_BN_CLICKED(IDC_BROWSE, OnBnClickedBrowse)
	ON_BN_CLICKED(IDC_COPY2CB, OnBnCopy2Clipboard)
	ON_BN_CLICKED(IDC_WITHHASHSET, OnBnClickedWithHashset)
	ON_BN_CLICKED(IDC_WITHAICH, OnBnClickedWithAICH)
	ON_CBN_SELCHANGE(IDC_LANGCOMBO, OnSelchangeLang)
	ON_BN_CLICKED(IDC_ADDCLIENT, OnBnClickedAddClientSource)
	ON_BN_CLICKED(IDC_CHECKSOURCE, SetButtonStates)
//	ON_EN_CHANGE(IDC_FILEPATH, SetStartButtonState)
	ON_EN_CHANGE(IDC_HTTPPATH, SetButtonStates)
	ON_EN_CHANGE(IDC_CLIENTSOURCE, SetButtonStates)
//	ON_EN_KILLFOCUS(IDC_FILEPATH, SetStartButtonState)

	///////////////////////////////////////////////////////////////////////////
	// WM_APP messages
	//
	ON_MESSAGE(TM_FINISHEDHASHING, OnFileHashed)
	ON_MESSAGE(TM_HASHFAILED, OnHashFailed)
	ON_MESSAGE(TM_FILEOPPROGRESS, OnProgress)
	ON_BN_CLICKED(IDC_CLIENTREMOVE, OnBnClickedClientremove)
	ON_BN_CLICKED(IDC_CLIENTSOURCECLEAR, OnBnClickedClientsourceclear)
	ON_LBN_SELCHANGE(IDC_HTTPLIST, OnLbnSelchangeHttplist)
	ON_LBN_SELCHANGE(IDC_CLIENTSOURCESLIST, OnLbnSelchangeClientsourceslist)
	ON_EN_CHANGE(IDC_FILEPATH, OnEnChangeFilepath)
END_MESSAGE_MAP()


// CLinkCreatorDlg Meldungshandler

BOOL CLinkCreatorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	RESULTWND=GetDlgItem(IDC_RESULT)->m_hWnd;
	resultbig=false;

	if (!theApp.GetLang())
		theApp.SetLang( (LANGID)::GetThreadLocale() );

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, GetResString(IDS_ABOUT));
	}

	SetIcon(m_hIcon, TRUE);	// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);	// Kleines Symbol verwenden

	m_ctrlAICH.SetCheck(BST_CHECKED);
	m_ctrlProgress.SetRange(0, 100);
	m_ctrlProgress.SetPos(0);

	m_ctrlLang.SetDroppedWidth(150);
	Localize();

	if (m_strFileToHash.GetLength())
	{
		m_ctrFilePath.SetWindowText(m_strFileToHash);
		m_strFileToHash.Empty();
		OnBnClickedStart();
	}

	CheckDlgButton(IDC_CHECKSOURCE,BST_CHECKED);
	CheckDlgButton(IDC_LENGTHCHECK,BST_CHECKED);
	SetButtonStates();

	return TRUE; 
}

void CLinkCreatorDlg::Localize()
{
	if (!m_hWnd)
		return;

	static const UINT ids[] = {
		IDC_STATIC1, IDC_STATIC2, IDC_STATIC3, IDC_STATIC4,
		IDC_WITHHASHSET, IDC_STATIC5, IDC_STATIC6, IDC_WITHAICH,
		IDC_BROWSE
	};
	ModifyStyleEx(WNDEXSTYLE,GetWndExStyle());
	for (int i=0; i<ARRSIZE(ids); i++)
		GetDlgItem(ids[i])->ModifyStyleEx(WNDEXSTYLE,GetWndExStyle());

	GetDlgItem(IDC_STATIC1)->SetWindowText(GetResString(IDS_FILELOCATION));
	GetDlgItem(IDC_BROWSE)->SetWindowText(GetResString(IDS_BROWSE));
	
	GetDlgItem(IDC_ADDHTTP)->SetWindowText(GetResString(IDS_ADDHTTP));
	GetDlgItem(IDC_HTTPREMOVE)->SetWindowText(GetResString(IDS_HTTPREMOVE));
	GetDlgItem(IDC_HTTPCLEAR)->SetWindowText(GetResString(IDS_HTTPCLEAR));

	GetDlgItem(IDC_ADDCLIENT)->SetWindowText(GetResString(IDS_ADDHTTP));
	GetDlgItem(IDC_CLIENTREMOVE)->SetWindowText(GetResString(IDS_HTTPREMOVE));
	GetDlgItem(IDC_CLIENTSOURCECLEAR)->SetWindowText(GetResString(IDS_HTTPCLEAR));

	GetDlgItem(IDC_STATIC2)->SetWindowText(GetResString(IDS_HTTPADDRESS));
	GetDlgItem(IDC_STATIC3)->SetWindowText(GetResString(IDS_ADDEDHTTPSOURCES));
	GetDlgItem(IDC_STATIC4)->SetWindowText(GetResString(IDS_ED2KLINK));
	GetDlgItem(IDC_START)->SetWindowText(GetResString(IDS_START));
	GetDlgItem(IDC_CANCEL)->SetWindowText(GetResString(IDS_CANCEL));
	GetDlgItem(IDC_EXIT)->SetWindowText(GetResString(IDS_EXIT));
	GetDlgItem(IDC_WITHHASHSET)->SetWindowText(GetResString(IDS_WITHHASHSET));
	GetDlgItem(IDC_STATIC5)->SetWindowText(GetResString(IDS_EX1));
	GetDlgItem(IDC_STATIC6)->SetWindowText(GetResString(IDS_EX2));
	GetDlgItem(IDC_COPY2CB)->SetWindowText(GetResString(IDS_COPYTOCLIPBOARD));
	GetDlgItem(IDC_WITHAICH)->SetWindowText(GetResString(IDS_WITHAICH));

	SetDlgItemText(IDC_SOURCESFRAME,GetResString(IDS_SOURCESMANAGEMENT));
	SetDlgItemText(IDC_STATICCLIENTSOURCES,GetResString(IDS_CLIENTSCOURCE));
	SetDlgItemText(IDC_STATIC8,GetResString(IDS_CLIENTSOURCESLIST));

	SetDlgItemText(IDC_CHECKSOURCE,GetResString(IDS_CHECKSOURCE));
	SetDlgItemText(IDC_LENGTHCHECK,GetResString(IDS_LENGTHCHECK));
    		

	CString buffer;
	buffer.Format(_T("%s v%s"),GetResString(IDS_LINKCREATOR),theApp.GetVersion());
	SetWindowText(buffer);
	MakeLangSelection(m_ctrlLang);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu)
		pSysMenu->ModifyMenu(IDM_ABOUTBOX, MF_BYCOMMAND | MF_STRING, IDM_ABOUTBOX, GetResString(IDS_ABOUT));
}


void CLinkCreatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}


void CLinkCreatorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext zum Zeichnen

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CLinkCreatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLinkCreatorDlg::StartOnFolder(CString folder){

	if (PathIsDirectory(folder) && 
		folder.Right(1)!=_T("\\") && folder.Right(1)!=_T("/"))
		folder+="\\";

   if (folder.Right(1)==_T("\\") || folder.Right(1)==_T("/"))
	   folder+=_T("*.*");

   CFileFind ff;
   BOOL bFound = ff.FindFile(folder);
   bool bAich = (m_ctrlAICH.GetCheck() == BST_CHECKED);
   theApp.bFolderJob=true;

   while (bFound)
   {
		bFound = ff.FindNextFile();
		if (ff.IsDirectory())
			continue;
		
		if (!IsValidFile(ff.GetFilePath()))
			continue;

		theApp.m_saHashList.Add(ff.GetFilePath());
   }

   if (!theApp.m_saHashList.IsEmpty())
	   StartNextFile();
}

void CLinkCreatorDlg::OnBnClickedStart()
{
	theApp.bCancelHashing = false;
	CString strFullPath;
	m_ctrFilePath.GetWindowText(strFullPath);

	m_ctrlResults.SetWindowText(_T(""));

	// folder job?
	if (PathIsDirectory(strFullPath) ||
		strFullPath.Find(_T("*"))>=0    || strFullPath.Find(_T("?"))>=0 ) {
		
		StartOnFolder(strFullPath);
		return;
	}

	theApp.bFolderJob=false;
	uint32 Pos;
	if( ((Pos = strFullPath.ReverseFind('\\')) == (-1) && (Pos = strFullPath.ReverseFind('/')) == (-1) )
		|| !IsValidFile(strFullPath) ){
		AfxMessageBox(GetResString(IDS_INVALIDFILEPATH), MB_ICONSTOP, MB_OK);
		return;
	}
	CString strPath = strFullPath.Left(Pos+1);
	CString strFile = strFullPath.Mid(Pos+1);

	// already have the hashed file in m_pKnownFile?
	if (m_pKnownFile)
	{
		bool bAich = (m_ctrlAICH.GetCheck() == BST_CHECKED);
		EAICHStatus aichStatus = (m_pKnownFile->m_pAICHHashSet) ? m_pKnownFile->m_pAICHHashSet->GetStatus() : AICH_EMPTY;

		if (!strFullPath.CompareNoCase(m_pKnownFile->GetFilePath()) && (!bAich || (aichStatus == AICH_HASHSETCOMPLETE && bAich)))
		{
			RenewFileLink();
			return;
		}

		delete m_pKnownFile; // delete previous known file
		m_pKnownFile = NULL;
	}
	StartHashingFile(strPath, strFile);
}


void CLinkCreatorDlg::StartHashingFile(CString strPath, CString strFile)
{
	GetDlgItem(IDC_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_CANCEL)->EnableWindow(TRUE);
	GetDlgItem(IDC_WITHAICH)->EnableWindow(FALSE);
	GetDlgItem(IDC_WITHHASHSET)->EnableWindow(FALSE);

	if (theApp.m_saHashList.IsEmpty()) {
		GetDlgItem(IDC_STATUS)->SetWindowText(GetResString(IDS_HASHING) + strFile );
	} else {
		CString info;
		info.Format(_T("%s (+%i): %s"),GetResString(IDS_HASHING) , theApp.m_saHashList.GetCount() ,strFile);

		GetDlgItem(IDC_STATUS)->SetWindowText(info);
	}

	CAddFileThread* addfilethread = (CAddFileThread*) AfxBeginThread(RUNTIME_CLASS(CAddFileThread), THREAD_PRIORITY_BELOW_NORMAL,0, CREATE_SUSPENDED);
	addfilethread->SetValues(strPath, strFile, m_ctrlAICH.GetCheck() == BST_CHECKED);
	addfilethread->ResumeThread();
}

void CLinkCreatorDlg::OnBnClickedCancel()
{
	GetDlgItem(IDC_CANCEL)->EnableWindow(FALSE);
	theApp.bCancelHashing = true;
}

bool CLinkCreatorDlg::StartNextFile() {
	if (m_pKnownFile) {
		delete m_pKnownFile;
		m_pKnownFile = NULL;
	}

	if (theApp.bCancelHashing) {
		theApp.m_saHashList.RemoveAll();
		return false;
	}

	CString nextf= theApp.m_saHashList.GetAt(0);
	theApp.m_saHashList.RemoveAt(0);
	int pos=nextf.ReverseFind(_T('\\'));
	StartHashingFile(nextf.Left(pos),nextf.Mid(pos+1));

	return true;
}

LRESULT CLinkCreatorDlg::OnFileHashed(WPARAM wParam, LPARAM lParam)
{
	m_pKnownFile = (CKnownFile*)lParam;
	m_ctrlProgress.SetPos(0);

	RenewFileLink();

	// continue with next file to hash
	if (!theApp.m_saHashList.IsEmpty()) {
		if (StartNextFile())
			return TRUE;
	}
	
	GetDlgItem(IDC_STATUS)->SetWindowText(_T(""));
	
	GetDlgItem(IDC_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_CANCEL)->EnableWindow(FALSE);
	GetDlgItem(IDC_WITHAICH)->EnableWindow(TRUE);
	GetDlgItem(IDC_WITHHASHSET)->EnableWindow(TRUE);

	return TRUE;
}

LRESULT CLinkCreatorDlg::OnHashFailed(WPARAM wParam, LPARAM lParam)
{
	m_ctrlProgress.SetPos(0);

	if (!theApp.m_saHashList.IsEmpty()) {
		if (StartNextFile())
			return TRUE;
	}

	GetDlgItem(IDC_STATUS)->SetWindowText(_T(""));
	GetDlgItem(IDC_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_CANCEL)->EnableWindow(FALSE);
	GetDlgItem(IDC_WITHAICH)->EnableWindow(TRUE);
	GetDlgItem(IDC_WITHHASHSET)->EnableWindow(TRUE);

	return TRUE;
}

LRESULT CLinkCreatorDlg::OnProgress(WPARAM wParam, LPARAM lParam)
{
	m_ctrlProgress.SetPos(wParam);
	return TRUE;
}

void CLinkCreatorDlg::OnClose()
{
	if (m_pKnownFile) {
		delete m_pKnownFile;
		m_pKnownFile = NULL;
	}
	OnCancel();
}

void CLinkCreatorDlg::OnBnClickedAddhttp()
{
	CString strSource;
	GetDlgItemText(IDC_HTTPPATH,strSource);
	if (strSource.GetLength() < 12){
		AfxMessageBox(GetResString(IDS_INVALIDURL), MB_ICONSTOP, MB_OK);
		return;
	}

	if (IsDlgButtonChecked(IDC_CHECKSOURCE) && strSource.Right(1)!=_T("/") ) {
		SetCursor(LoadCursor(NULL, IDC_WAIT));

		if (m_iLocalFilesize==0) {
			CString filepath;
			m_ctrFilePath.GetWindowText(filepath);
			if (!IsValidFile(filepath)) {
				AfxMessageBox(GetResString(IDS_CANTOPENFILE) + filepath, MB_ICONSTOP, MB_OK);
				return;
			}
		}

		// receive header & check filesize
		UINT64 filesize=GetHTTPRequestDataSize(strSource);
		SetCursor(LoadCursor(NULL,IDC_ARROW));

		if (filesize==0) {
			AfxMessageBox(GetResString(IDS_ERR_WEBSOURCECHECK), MB_ICONSTOP, MB_OK);
			return;
		}
		else if (filesize != m_iLocalFilesize ) {
			AfxMessageBox(GetResString(IDS_ERR_WEBSOURCECHECK_NOMATCH), MB_ICONSTOP, MB_OK);
			return;
		}

	}


	m_ctrlHttpSources.AddString(strSource); 

	SetDlgItemText(IDC_HTTPPATH,_T(""));

	SetButtonStates();
	RenewFileLink();
}

void CLinkCreatorDlg::OnBnClickedHttpclear()
{
	m_ctrlHttpSources.ResetContent();
	SetButtonStates();
	RenewFileLink();
}

void CLinkCreatorDlg::OnBnClickedHttpremove()
{
	if (m_ctrlHttpSources.GetCurSel() != LB_ERR)
	{
		m_ctrlHttpSources.DeleteString(m_ctrlHttpSources.GetCurSel());
		SetButtonStates();
		RenewFileLink();
	}
}

void CLinkCreatorDlg::OnBnClickedBrowse()
{
	CFileDialog dlgFile(TRUE, 0, 0,OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, 0, NULL, 0);
	if (dlgFile.DoModal()==IDOK){
		if (IsValidFile(dlgFile.GetPathName()))
			m_ctrFilePath.SetWindowText(dlgFile.GetPathName());
		else 
			AfxMessageBox(GetResString(IDS_CANTOPENFILE) + dlgFile.GetPathName(), MB_ICONSTOP, MB_OK);
		//SetStartButtonState();
	}
}

void CLinkCreatorDlg::OnBnCopy2Clipboard()
{
	CString strLink;
	m_ctrlResults.GetWindowText(strLink);
	CopyTextToClipboard(strLink);
}


void CLinkCreatorDlg::OnBnClickedWithHashset()
{
	if (m_pKnownFile)
		RenewFileLink();
}

void CLinkCreatorDlg::OnBnClickedWithAICH()
{
	if (m_pKnownFile && m_pKnownFile->m_pAICHHashSet &&
		m_pKnownFile->m_pAICHHashSet->GetStatus()==AICH_HASHSETCOMPLETE)
	{
		RenewFileLink();
	}
}

void CLinkCreatorDlg::OnSelchangeLang()
{
	if (m_ctrlLang.GetCurSel() != CB_ERR)
	{
		LANGID lid = (LANGID)m_ctrlLang.GetItemData(m_ctrlLang.GetCurSel());
		theApp.SetLang(lid);
		Localize();
	}
}

void CLinkCreatorDlg::RenewFileLink()
{
	if (!m_pKnownFile)
	{
		m_ctrlResults.SetWindowText(_T(""));
		return;
	}

	CString strWebsources = _T("");
	CString strClientSources = _T("");

	for(int i = 0; i != m_ctrlHttpSources.GetCount(); i++){
		CString strBuffer;
		m_ctrlHttpSources.GetText(i, strBuffer);

		// for multiple file hashing, use only httpsources without filename (to be appended)
		if (theApp.bFolderJob && strBuffer.Right(1) != _T("/") )
			continue;

		if (strBuffer.Right(1) == CString(_T("/")))
			strBuffer += StripInvalidFilenameChars(m_pKnownFile->GetFileName(), false);
		strWebsources.AppendFormat(_T("s=%s|"), strBuffer);
	}

	if (m_ctrlClientSources.GetCount()>0) {
		for(int i = 0; i != m_ctrlClientSources.GetCount(); i++){
			CString strBuffer;
			m_ctrlClientSources.GetText(i, strBuffer);
			strClientSources.AppendFormat(_T(",%s"), strBuffer);
		}
		strClientSources=_T("/|sources")+strClientSources+_T("|");
	}

	if (!theApp.bFolderJob)
		m_ctrlResults.SetWindowText(_T(""));


	CString strLink;
	m_ctrlResults.GetWindowText(strLink);

	bool bHashset = (m_ctrlWithHashset.GetCheck() == BST_CHECKED);
	bool bAICH = (m_ctrlAICH.GetCheck() == BST_CHECKED);

	CString newlink=CreateED2kLink(m_pKnownFile, strWebsources + strClientSources, bAICH, bHashset);

	if (strlen(newlink)>2038){
		if (IsDlgButtonChecked(IDC_LENGTHCHECK)) {
			// remove http sources until strlen is <=2038
			while (strlen(newlink)>2038) {
				int pos1=newlink.Find(_T("|s="));
				if (pos1==-1)
					break;
				int pos2=newlink.Find(_T("|"),pos1+1);
				if (pos2==-1)
					break;
				newlink.Delete(pos1,pos2-pos1);
			}

		}// else newlink=GetResString(IDS_TOOLONG_FOR_LINK) + _T(": \r\n") + newlink;
	}

	strLink += newlink;
	strLink += _T("\r\n");

	m_ctrlResults.SetWindowText(strLink);

	if (theApp.bFolderJob) {
		delete m_pKnownFile;
		m_pKnownFile=NULL;
	}

}


void CLinkCreatorDlg::OnBnClickedAddClientSource()
{
	CString newsource;
	GetDlgItemText(IDC_CLIENTSOURCE,newsource);

	if (newsource.IsEmpty())
		return;

	// check syntax
	bool syntaxok=true;
	CString host,sport;
	int port;
	int pos=newsource.Find(':');
	if (pos>4) {
		host=newsource.Left(pos);
		sport=newsource.Mid(pos+1);
		port=atoi(sport);

		// check ip
		if (_istdigit(host.GetAt(0))) {
			if (inet_addr(host) == INADDR_NONE )
				syntaxok=false;
		}

		// check port
		if (port<1 || port>65535)
			syntaxok=false;
	} else 
		syntaxok=false;
	
	if (!syntaxok)
	{
		AfxMessageBox(GetResString(IDS_ERRCLIENTSOURCE), MB_ICONSTOP, MB_OK);
        return;
	}

	m_ctrlClientSources.AddString(newsource); 
	SetDlgItemText(IDC_CLIENTSOURCE,_T(""));
	SetButtonStates();
	RenewFileLink();
}

void CLinkCreatorDlg::OnBnClickedClientremove()
{
	if (m_ctrlClientSources.GetCurSel() != LB_ERR)
	{
		m_ctrlClientSources.DeleteString(m_ctrlClientSources.GetCurSel());
		SetButtonStates();
		RenewFileLink();
	}
}

void CLinkCreatorDlg::OnBnClickedClientsourceclear()
{
	m_ctrlClientSources.ResetContent();
	SetButtonStates();
	RenewFileLink();
}

bool CLinkCreatorDlg::IsValidFile(CString filepath)
{
	// check local file existance and accessability
	bool flag=false;
	m_iLocalFilesize=0;

	if (!filepath.IsEmpty()) {
		HANDLE fHandle=CreateFile(filepath,    // file to open
                   GENERIC_READ,          // open for reading
                   FILE_SHARE_READ,       // share for reading
                   NULL,                  // default security
                   OPEN_EXISTING,         // existing file only
                   FILE_ATTRIBUTE_NORMAL, // normal file
                   NULL); 
			
		if (fHandle!=INVALID_HANDLE_VALUE){

			DWORD dwl,dwh;
			dwl=GetFileSize(fHandle, &dwh);
			if (dwl!=INVALID_FILE_SIZE) {
				m_iLocalFilesize= dwh;
				m_iLocalFilesize<<=32;
				m_iLocalFilesize+= dwl;
			} else 
				m_iLocalFilesize=0;
			
			CloseHandle(fHandle);

			if (m_iLocalFilesize>0) {
				if (m_iLocalFilesize> MAX_EMULE_FILE_SIZE ) {
					MessageBox(GetResString(IDS_FILETOOLARGE));

				} else 
					flag=true;
			}
		}
	}
//	GetDlgItem(IDC_START)->EnableWindow(flag);
	return flag;
}

void CLinkCreatorDlg::SetButtonStates()
{
	CString buffer;

	// websources

	// add
	GetDlgItemText(IDC_HTTPPATH,buffer);
	bool checkflag=true;
	if (IsDlgButtonChecked(IDC_CHECKSOURCE))
		if (GetDlgItem(IDC_START)->IsWindowEnabled()==FALSE)
			checkflag=false;
	GetDlgItem(IDC_ADDHTTP)->EnableWindow(buffer.GetLength()>12 && buffer.Left(7).CompareNoCase("http://")==0 && checkflag );
	
	// remove
	GetDlgItem(IDC_HTTPREMOVE)->EnableWindow((m_ctrlHttpSources.GetCurSel() != LB_ERR));

	// clear
	GetDlgItem(IDC_HTTPCLEAR)->EnableWindow( m_ctrlHttpSources.GetCount()>0 );


	// clientsources

	// add
	GetDlgItemText(IDC_CLIENTSOURCE,buffer);
	GetDlgItem(IDC_ADDCLIENT)->EnableWindow(buffer.GetLength()>6/* && buffer.Find(':')>4*/);

	// remove
	GetDlgItem(IDC_CLIENTREMOVE)->EnableWindow((m_ctrlClientSources.GetCurSel() != LB_ERR));

	// clear
	GetDlgItem(IDC_CLIENTSOURCECLEAR)->EnableWindow( m_ctrlClientSources.GetCount()>0 );
}

void CLinkCreatorDlg::OnLbnSelchangeHttplist()
{
	SetButtonStates();
}

void CLinkCreatorDlg::OnLbnSelchangeClientsourceslist()
{
	SetButtonStates();
}

BOOL CLinkCreatorDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_LBUTTONDBLCLK && pMsg->hwnd ==RESULTWND ) {
		WINDOWPLACEMENT wp;
		wp.length=sizeof(WINDOWPLACEMENT);
		GetDlgItem(IDC_RESULT)->GetWindowPlacement(&wp);

		if (resultbig) {
			wp.rcNormalPosition.top=436;
		} else {
			wp.rcNormalPosition.top=6;
		}
		GetDlgItem(IDC_RESULT)->SetWindowPlacement(&wp);

		resultbig = !resultbig;

		GetDlgItem(IDC_FILEPATH)->ShowWindow(resultbig?SW_HIDE:SW_SHOW);
		GetDlgItem(IDC_HTTPPATH)->ShowWindow(resultbig?SW_HIDE:SW_SHOW);
		GetDlgItem(IDC_CLIENTSOURCE)->ShowWindow(resultbig?SW_HIDE:SW_SHOW);
		GetDlgItem(IDC_WITHAICH)->ShowWindow(resultbig?SW_HIDE:SW_SHOW);
		GetDlgItem(IDC_WITHHASHSET)->ShowWindow(resultbig?SW_HIDE:SW_SHOW);
		GetDlgItem(IDC_CHECKSOURCE)->ShowWindow(resultbig?SW_HIDE:SW_SHOW);
		GetDlgItem(IDC_BROWSE)->ShowWindow(resultbig?SW_HIDE:SW_SHOW);
		GetDlgItem(IDC_ADDHTTP)->ShowWindow(resultbig?SW_HIDE:SW_SHOW);
		GetDlgItem(IDC_HTTPLIST)->ShowWindow(resultbig?SW_HIDE:SW_SHOW);
		GetDlgItem(IDC_HTTPREMOVE)->ShowWindow(resultbig?SW_HIDE:SW_SHOW);
		GetDlgItem(IDC_HTTPCLEAR)->ShowWindow(resultbig?SW_HIDE:SW_SHOW);
		GetDlgItem(IDC_ADDCLIENT)->ShowWindow(resultbig?SW_HIDE:SW_SHOW);
		GetDlgItem(IDC_CLIENTSOURCESLIST)->ShowWindow(resultbig?SW_HIDE:SW_SHOW);
		GetDlgItem(IDC_CLIENTREMOVE)->ShowWindow(resultbig?SW_HIDE:SW_SHOW);
		GetDlgItem(IDC_CLIENTSOURCECLEAR)->ShowWindow(resultbig?SW_HIDE:SW_SHOW);
		GetDlgItem(IDC_SOURCESFRAME)->ShowWindow(resultbig?SW_HIDE:SW_SHOW);
		GetDlgItem(IDC_LENGTHCHECK)->ShowWindow(resultbig?SW_HIDE:SW_SHOW);

		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CLinkCreatorDlg::OnEnChangeFilepath()
{
	m_iLocalFilesize=0;
}
