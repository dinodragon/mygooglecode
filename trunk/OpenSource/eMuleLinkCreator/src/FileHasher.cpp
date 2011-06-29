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
#include "LinkCreator.h"
#include "FileHasher.h"
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <share.h>
#include "LinkCreatorDlg.h"
#include "functions.h"
#include "SHAHashSet.h"
#include "MD4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNAMIC(CAbstractFile, CObject)

CAbstractFile::CAbstractFile()
{
	md4clr(m_abyFileHash);
	m_nFileSize = 0;
}

void CAbstractFile::SetFileName(LPCTSTR pszFileName, bool bReplaceInvalidFileSystemChars, bool bAutoSetFileType)
{ 
	m_strFileName = pszFileName;
	if (bReplaceInvalidFileSystemChars){
		m_strFileName.Replace(_T('/'), _T('-'));
		m_strFileName.Replace(_T('>'), _T('-'));
		m_strFileName.Replace(_T('<'), _T('-'));
		m_strFileName.Replace(_T('*'), _T('-'));
		m_strFileName.Replace(_T(':'), _T('-'));
		m_strFileName.Replace(_T('?'), _T('-'));
		m_strFileName.Replace(_T('\"'), _T('-'));
		m_strFileName.Replace(_T('\\'), _T('-'));
		m_strFileName.Replace(_T('|'), _T('-'));
	}
}

void CAbstractFile::SetFileHash(const uchar* pucFileHash)
{
	md4cpy(m_abyFileHash, pucFileHash);
}

bool CAbstractFile::HasNullHash() const
{
	return isnulmd4(m_abyFileHash) == 0;
}

///////////////////////////////////////////////////////////////////////
//// CKnownFile
///////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CKnownFile, CAbstractFile)

void CKnownFile::SetFileName(LPCTSTR pszFileName, bool bReplaceInvalidFileSystemChars)
{ 
	CAbstractFile::SetFileName(pszFileName, bReplaceInvalidFileSystemChars);
} 

void CKnownFile::SetPath(LPCTSTR path)
{
	m_strDirectory = path;
}

void CKnownFile::SetFilePath(LPCTSTR pszFilePath)
{
	m_strFilePath = pszFilePath;
}

bool CKnownFile::CreateFromFile(LPCTSTR in_directory, LPCTSTR in_filename, bool bAICH)
{
	SetPath(in_directory);
	SetFileName(in_filename);

	// open file
	CString strFilePath;
	_tmakepath(strFilePath.GetBuffer(MAX_PATH), NULL, in_directory, in_filename, NULL);
	strFilePath.ReleaseBuffer();
	SetFilePath(strFilePath);
	FILE* file = _tfsopen(strFilePath, _T("rbS"), _SH_DENYNO); // can not use _SH_DENYWR because we may access a completing part file
	if (!file){
		AfxMessageBox(GetResString(IDS_CANTOPENFILE) + strFilePath, MB_ICONSTOP, MB_OK);
		return false;
	}

	// set filesize
	if (_filelengthi64(file->_file) > MAX_EMULE_FILE_SIZE){
		fclose(file);
		return false; // not supported by network
	}
	SetFileSize((uint64)_filelengthi64(file->_file));

	// we are reading the file data later in 8K blocks, adjust the internal file stream buffer accordingly
	setvbuf(file, NULL, _IOFBF, 1024*8*2);

	
	// create hashset
	uint64 togo = m_nFileSize;
	UINT hashcount;
	for (hashcount = 0; togo >= PARTSIZE; )
	{
		CAICHHashTree* pBlockAICHHashTree = m_pAICHHashSet->m_pHashTree.FindHash((uint64)hashcount*PARTSIZE, PARTSIZE);
		ASSERT( pBlockAICHHashTree != NULL );

		uchar* newhash = new uchar[16];
		CreateHash(file, PARTSIZE, newhash, pBlockAICHHashTree);

		if (theApp.m_pLinkCreatorDlg == NULL || theApp.bCancelHashing){
			fclose(file);
			delete[] newhash;
			return false;
		}

		hashlist.Add(newhash);
		togo -= PARTSIZE;
		hashcount++;

		UINT uProgress = (UINT)(((ULONGLONG)(GetFileSize() - togo) * 100) / GetFileSize());
		ASSERT( uProgress <= 100 );
		VERIFY( PostMessage(theApp.m_pLinkCreatorDlg->GetSafeHwnd(), TM_FILEOPPROGRESS, uProgress, 0) );
	}

	CAICHHashTree* pBlockAICHHashTree;
	if (togo == 0)
		pBlockAICHHashTree = NULL; // sha hashtree doesnt takes hash of 0-sized data
	else{
		pBlockAICHHashTree = m_pAICHHashSet->m_pHashTree.FindHash((uint64)hashcount*PARTSIZE, togo);
		ASSERT( pBlockAICHHashTree != NULL );
	}
	
	uchar* lasthash = new uchar[16];
	md4clr(lasthash);

	CreateHash(file, togo, lasthash, pBlockAICHHashTree);
	
	if (theApp.m_pLinkCreatorDlg == NULL || theApp.bCancelHashing){
		fclose(file);
		delete[] lasthash;
		return false;
	}

	if (bAICH){
		m_pAICHHashSet->ReCalculateHash(false);
		if ( m_pAICHHashSet->VerifyHashTree(true) ){
			m_pAICHHashSet->SetStatus(AICH_HASHSETCOMPLETE);
		}
		else{
			// now something went pretty wrong
			AfxMessageBox(GetResString(IDS_CANTCREATEAICH) + GetFileName(), MB_ICONSTOP, MB_OK);
		}
	}

	if (!hashcount){
		md4cpy(m_abyFileHash, lasthash);
		delete[] lasthash;
	} 
	else {
		hashlist.Add(lasthash);
		uchar* buffer = new uchar[hashlist.GetCount()*16];
		for (int i = 0; i < hashlist.GetCount(); i++)
			md4cpy(buffer+(i*16), hashlist[i]);
		CreateHash(buffer, hashlist.GetCount()*16, m_abyFileHash);
		delete[] buffer;
	}

	fclose(file);
	file = NULL;
	return true;
}

void CKnownFile::CreateHash(CFile* pFile, uint64 Length, uchar* pMd4HashOut, CAICHHashTree* pShaHashOut) const
{
	ASSERT( pFile != NULL );
	ASSERT( pMd4HashOut != NULL || pShaHashOut != NULL );

	uint64  Required = Length;
	uchar   X[64*128];
	uint64	posCurrentEMBlock = 0;
	uint64	nIACHPos = 0;
	CAICHHashAlgo* pHashAlg = m_pAICHHashSet->GetNewHashAlgo();
	CMD4 md4;

	while (Required >= 64){
        uint32 len; 
        if ((Required / 64) > sizeof(X)/(64 * sizeof(X[0]))) 
			len = sizeof(X)/(64 * sizeof(X[0]));
		else
			len = (uint32)Required / 64;
		pFile->Read(&X, len*64);

		// SHA hash needs 180KB blocks
		if (pShaHashOut != NULL){
			if (nIACHPos + len*64 >= EMBLOCKSIZE){
				uint32 nToComplete = (uint32)(EMBLOCKSIZE - nIACHPos);
				pHashAlg->Add(X, nToComplete);
				ASSERT( nIACHPos + nToComplete == EMBLOCKSIZE );
				pShaHashOut->SetBlockHash(EMBLOCKSIZE, posCurrentEMBlock, pHashAlg);
				posCurrentEMBlock += EMBLOCKSIZE;
				pHashAlg->Reset();
				pHashAlg->Add(X+nToComplete,(len*64) - nToComplete);
				nIACHPos = (len*64) - nToComplete;
			}
			else{
				pHashAlg->Add(X, len*64);
				nIACHPos += len*64;
			}
		}

		if (pMd4HashOut != NULL){
			md4.Add(X, len*64);
		}
		Required -= len*64;
	}

	Required = Length % 64;
	if (Required != 0){
		pFile->Read(&X, (uint32)Required);

		if (pShaHashOut != NULL){
			if (nIACHPos + Required >= EMBLOCKSIZE){
				uint32 nToComplete = (uint32)(EMBLOCKSIZE - nIACHPos);
				pHashAlg->Add(X, nToComplete);
				ASSERT( nIACHPos + nToComplete == EMBLOCKSIZE );
				pShaHashOut->SetBlockHash(EMBLOCKSIZE, posCurrentEMBlock, pHashAlg);
				posCurrentEMBlock += EMBLOCKSIZE;
				pHashAlg->Reset();
				pHashAlg->Add(X+nToComplete, (uint32)(Required - nToComplete));
				nIACHPos = Required - nToComplete;
			}
			else{
				pHashAlg->Add(X, (uint32)Required);
				nIACHPos += Required;
			}
		}
	}
	if (pShaHashOut != NULL){
		if(nIACHPos > 0){
			pShaHashOut->SetBlockHash(nIACHPos, posCurrentEMBlock, pHashAlg);
			posCurrentEMBlock += nIACHPos;
		}
		ASSERT( posCurrentEMBlock == Length );
		VERIFY( pShaHashOut->ReCalculateHash(pHashAlg, false) );
	}

	if (pMd4HashOut != NULL){
		md4.Add(X, (uint32)Required);
		md4.Finish();
		md4cpy(pMd4HashOut, md4.GetHash());
	}

	delete pHashAlg;
}

bool CKnownFile::CreateHash(FILE* fp, uint64 uSize, uchar* pucHash, CAICHHashTree* pShaHashOut) const
{
	bool bResult = false;
	CStdioFile file(fp);
	try
	{
		CreateHash(&file, uSize, pucHash, pShaHashOut);
		bResult = true;
	}
	catch(CFileException* ex)
	{
		ex->Delete();
	}
	return bResult;
}

bool CKnownFile::CreateHash(const uchar* pucData, uint32 uSize, uchar* pucHash, CAICHHashTree* pShaHashOut) const
{
	bool bResult = false;
	CMemFile file(const_cast<uchar*>(pucData), uSize);
	try
	{
		CreateHash(&file, uSize, pucHash, pShaHashOut);
		bResult = true;
	}
	catch(CFileException* ex)
	{
		ex->Delete();
	}
	return bResult;
}

uchar* CKnownFile::GetPartHash(uint16 part) const {
	if (part >= hashlist.GetCount())
		return 0;
	return hashlist[part];
}

void CKnownFile::SetFileSize(EMFileSize nFileSize)
{
	CAbstractFile::SetFileSize(nFileSize);
	m_pAICHHashSet->SetFileSize(nFileSize);

	if (nFileSize == (uint64)0){
		ASSERT(0);
		m_iPartCount = 0;
		m_iED2KPartCount = 0;
		m_iED2KPartHashCount = 0;
		return;
	}

	// nr. of data parts
	ASSERT( (uint64)(((uint64)nFileSize + (PARTSIZE - 1)) / PARTSIZE) <= (UINT)USHRT_MAX );
	m_iPartCount = (uint16)(((uint64)nFileSize + (PARTSIZE - 1)) / PARTSIZE);

	// nr. of parts to be used with OP_FILESTATUS
	m_iED2KPartCount = (uint16)((uint64)nFileSize / PARTSIZE + 1);

	// nr. of parts to be used with OP_HASHSETANSWER
	m_iED2KPartHashCount = (uint16)((uint64)nFileSize / PARTSIZE);
	if (m_iED2KPartHashCount != 0)
		m_iED2KPartHashCount += 1;
}

CKnownFile::CKnownFile()
{
	m_iPartCount = 0;
	m_iED2KPartCount = 0;
	m_iED2KPartHashCount = 0;
	m_pAICHHashSet = new CAICHHashSet(this);
}

CKnownFile::~CKnownFile()
{
	for (int i = 0; i < hashlist.GetSize(); i++)
		delete[] hashlist[i];
	delete m_pAICHHashSet; 
}

///////////////////////////////////////////////////////////////////////
//// CAddFileThread
///////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CAddFileThread, CWinThread)

CAddFileThread::CAddFileThread()
{
}

void CAddFileThread::SetValues(LPCTSTR directory, LPCTSTR filename, bool bAICH)
{
	 m_strDirectory = directory;
	 m_strFilename = filename;
	 m_bAICH = bAICH;
}

BOOL CAddFileThread::InitInstance()
{
	return TRUE;
}

int CAddFileThread::Run()
{

	CSingleLock sLock1(&theApp.hashing_mut); // only one filehash at a time
	sLock1.Lock();

	CString strFilePath;
	_tmakepath(strFilePath.GetBuffer(MAX_PATH), NULL, m_strDirectory, m_strFilename, NULL);
	strFilePath.ReleaseBuffer();
	
	CKnownFile* newrecord = new CKnownFile();
	if (newrecord->CreateFromFile(m_strDirectory, m_strFilename, m_bAICH) && theApp.m_pLinkCreatorDlg != NULL ) // SLUGFILLER: SafeHash - in case of shutdown while still hashing
	{
		VERIFY( PostMessage(theApp.m_pLinkCreatorDlg->m_hWnd, TM_FINISHEDHASHING, 0, (LPARAM)newrecord) );
	}
	else
	{
		if (theApp.m_pLinkCreatorDlg != NULL)
		{
			UnknownFile_Struct hashed;
			hashed.strDirectory = m_strDirectory;
			hashed.strName = m_strFilename;
			VERIFY( PostMessage(theApp.m_pLinkCreatorDlg->m_hWnd,TM_HASHFAILED,0,(LPARAM)&hashed) );
		}
		// SLUGFILLER: SafeHash
		delete newrecord;
	}

	sLock1.Unlock();

	return 0;
}

