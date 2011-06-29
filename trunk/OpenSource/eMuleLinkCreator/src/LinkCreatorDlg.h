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

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "FileHasher.h"


// CLinkCreatorDlg Dialogfeld
class CLinkCreatorDlg : public CDialog
{
// Konstruktion
public:
	CLinkCreatorDlg(CWnd* pParent = NULL);	// Standardkonstruktor
	void Localize();
	void SetFilePath(CString strFilePath) { m_strFileToHash = strFilePath; }

// Dialogfelddaten
	enum { IDD = IDD_LINKCREATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung

// Implementierung
protected:
	HICON	m_hIcon;
	HWND	RESULTWND;
	bool	resultbig;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnFileHashed(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnHashFailed(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnProgress(WPARAM wParam,LPARAM lParam);
	afx_msg void	OnBnClickedAddhttp();
	afx_msg void	OnBnClickedHttpclear();
	afx_msg void	OnBnClickedHttpremove();
	afx_msg void	OnBnClickedBrowse();
	afx_msg void	OnBnClickedStart();
	afx_msg void	OnBnClickedCancel();
	afx_msg void	OnBnClickedWithHashset();
	afx_msg void	OnBnClickedWithAICH();
	afx_msg void	OnClose();
	afx_msg void	OnBnCopy2Clipboard();
	afx_msg void	OnSelchangeLang();
	afx_msg void	OnBnClickedAddClientSource();
	//afx_msg void	SetStartButtonState();

	void			OnOK()			{}
	DECLARE_MESSAGE_MAP()
private:
	CEdit		m_ctrFilePath;
	CButton		m_ctrlWithHashset;
	CEdit		m_ctrlResults;
	CProgressCtrl	m_ctrlProgress;
	CListBox		m_ctrlHttpSources;
	CListBox		m_ctrlClientSources;
	CButton		m_ctrlAICH;
	CComboBox	m_ctrlLang;

	void		StartOnFolder(CString folder);
	void		SetButtonStates();
	void		RenewFileLink();
	void		StartHashingFile(CString strPath, CString strFile);
	bool		StartNextFile();
	bool		IsValidFile(CString filepath);
	CKnownFile*	m_pKnownFile;
	CString		m_strFileToHash;
	UINT64		m_iLocalFilesize;

public:
	afx_msg void OnBnClickedClientremove();
	afx_msg void OnBnClickedClientsourceclear();
	afx_msg void OnLbnSelchangeHttplist();
	afx_msg void OnLbnSelchangeClientsourceslist();
	afx_msg void OnEnChangeFilepath();
};

enum EEmlueAppMsgs
{
	//thread messages
	TM_FINISHEDHASHING = WM_APP + 10,
	TM_HASHFAILED,
	TM_FRAMEGRABFINISHED,
	TM_FILEALLOCEXC,
	TM_FILECOMPLETED,
	TM_FILEOPPROGRESS
};
