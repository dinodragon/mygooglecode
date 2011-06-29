//this file is part of eMule
//Copyright (C)2002-2006 Merkur ( strEmail.Format("%s@%s", "devteam", "emule-project.net") / http://www.emule-project.net )
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "StdAfx.h"
#include "shahashset.h"
#include "sha.h"
#include "FileHasher.h"
#include "functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// for this version the limits are set very high, they might be lowered later
// to make a hash trustworthy, at least 10 unique Ips (255.255.128.0) must have send it
// and if we have received more than one hash  for the file, one hash has to be send by more than 95% of all unique IPs
#define MINUNIQUEIPS_TOTRUST		10	// how many unique IPs most have send us a hash to make it trustworthy
#define	MINPERCENTAGE_TOTRUST		92  // how many percentage of clients most have sent the same hash to make it trustworthy


/////////////////////////////////////////////////////////////////////////////////////////
///CAICHHash
CString CAICHHash::GetString() const{
	return EncodeBase32(m_abyBuffer, HASHSIZE);
}

/////////////////////////////////////////////////////////////////////////////////////////
///CAICHHashTree

CAICHHashTree::CAICHHashTree(uint64 nDataSize, bool bLeftBranch, uint64 nBaseSize){
	m_nDataSize = nDataSize;
	m_nBaseSize = nBaseSize;
	m_bIsLeftBranch = bLeftBranch;
	m_pLeftTree = NULL;
	m_pRightTree = NULL;
	m_bHashValid = false;
}

CAICHHashTree::~CAICHHashTree(){
	delete m_pLeftTree;
	delete m_pRightTree;
}

// recursive
CAICHHashTree* CAICHHashTree::FindHash(uint64 nStartPos, uint64 nSize, uint8* nLevel){
	(*nLevel)++;
	if (*nLevel > 22){ // sanity
		ASSERT( false );
		return false;
	}
	if (nStartPos + nSize > m_nDataSize){ // sanity
		ASSERT ( false );
		return NULL;
	}
	if (nSize > m_nDataSize){ // sanity
		ASSERT ( false );
		return NULL;
	}

	if (nStartPos == 0 && nSize == m_nDataSize){
		// this is the searched hash
		return this;
	}
	else if (m_nDataSize <= m_nBaseSize){ // sanity
		// this is already the last level, cant go deeper
		ASSERT( false );
		return NULL;
	}
	else{
		uint64 nBlocks = m_nDataSize / m_nBaseSize + ((m_nDataSize % m_nBaseSize != 0 )? 1:0); 
		uint64 nLeft = ( ((m_bIsLeftBranch) ? nBlocks+1:nBlocks) / 2)* m_nBaseSize;
		uint64 nRight = m_nDataSize - nLeft;
		if (nStartPos < nLeft){
			if (nStartPos + nSize > nLeft){ // sanity
				ASSERT ( false );
				return NULL;
			}
			if (m_pLeftTree == NULL)
				m_pLeftTree = new CAICHHashTree(nLeft, true, (nLeft <= PARTSIZE) ? EMBLOCKSIZE : PARTSIZE);
			else{
				ASSERT( m_pLeftTree->m_nDataSize == nLeft );
			}
			return m_pLeftTree->FindHash(nStartPos, nSize, nLevel);
		}
		else{
			nStartPos -= nLeft;
			if (nStartPos + nSize > nRight){ // sanity
				ASSERT ( false );
				return NULL;
			}
			if (m_pRightTree == NULL)
				m_pRightTree = new CAICHHashTree(nRight, false, (nRight <= PARTSIZE) ? EMBLOCKSIZE : PARTSIZE);
			else{
				ASSERT( m_pRightTree->m_nDataSize == nRight ); 
			}
			return m_pRightTree->FindHash(nStartPos, nSize, nLevel);
		}
	}
}

// recursive
// calculates missing hash fromt he existing ones
// overwrites existing hashs
// fails if no hash is found for any branch
bool CAICHHashTree::ReCalculateHash(CAICHHashAlgo* hashalg, bool bDontReplace){
	ASSERT ( !( (m_pLeftTree != NULL) ^ (m_pRightTree != NULL)) ); 
	if (m_pLeftTree && m_pRightTree){
		if ( !m_pLeftTree->ReCalculateHash(hashalg, bDontReplace) || !m_pRightTree->ReCalculateHash(hashalg, bDontReplace) )
			return false;
		if (bDontReplace && m_bHashValid)
			return true;
		if (m_pRightTree->m_bHashValid && m_pLeftTree->m_bHashValid){
			hashalg->Reset();
			hashalg->Add(m_pLeftTree->m_Hash.GetRawHash(), HASHSIZE);
			hashalg->Add(m_pRightTree->m_Hash.GetRawHash(), HASHSIZE);
			hashalg->Finish(m_Hash);
			m_bHashValid = true;
			return true;
		}
		else
			return m_bHashValid;
	}
	else
		return true;
}

bool CAICHHashTree::VerifyHashTree(CAICHHashAlgo* hashalg, bool bDeleteBadTrees){
	if (!m_bHashValid){
		ASSERT ( false );
		if (bDeleteBadTrees){
			delete m_pLeftTree;
			m_pLeftTree = NULL;
			delete m_pRightTree;
			m_pRightTree = NULL;
		}
		return false;
	}
	
		// calculated missing hashs without overwriting anything
		if (m_pLeftTree && !m_pLeftTree->m_bHashValid)
			m_pLeftTree->ReCalculateHash(hashalg, true);
		if (m_pRightTree && !m_pRightTree->m_bHashValid)
			m_pRightTree->ReCalculateHash(hashalg, true);
		
		if ((m_pRightTree && m_pRightTree->m_bHashValid) ^ (m_pLeftTree && m_pLeftTree->m_bHashValid)){
			// one branch can never be verified
			if (bDeleteBadTrees){
				delete m_pLeftTree;
				m_pLeftTree = NULL;
				delete m_pRightTree;
				m_pRightTree = NULL;
			}
			return false;
		}
	if ((m_pRightTree && m_pRightTree->m_bHashValid) && (m_pLeftTree && m_pLeftTree->m_bHashValid)){			
	    // check verify the hashs of both child nodes against my hash 
	
		CAICHHash CmpHash;
		hashalg->Reset();
		hashalg->Add(m_pLeftTree->m_Hash.GetRawHash(), HASHSIZE);
		hashalg->Add(m_pRightTree->m_Hash.GetRawHash(), HASHSIZE);
		hashalg->Finish(CmpHash);
		
		if (m_Hash != CmpHash){
			if (bDeleteBadTrees){
				delete m_pLeftTree;
				m_pLeftTree = NULL;
				delete m_pRightTree;
				m_pRightTree = NULL;
			}
			return false;
		}
		return m_pLeftTree->VerifyHashTree(hashalg, bDeleteBadTrees) && m_pRightTree->VerifyHashTree(hashalg, bDeleteBadTrees);
	}
	else
		// last hash in branch - nothing below to verify
		return true;

}

void CAICHHashTree::SetBlockHash(uint64 nSize, uint64 nStartPos, CAICHHashAlgo* pHashAlg){
	ASSERT ( nSize <= EMBLOCKSIZE );
	CAICHHashTree* pToInsert = FindHash(nStartPos, nSize);
	if (pToInsert == NULL){ // sanity
		ASSERT ( false );
		return;
	}
	
	//sanity
	if (pToInsert->m_nBaseSize != EMBLOCKSIZE || pToInsert->m_nDataSize != nSize){
		ASSERT ( false );
		return;
	}

	pHashAlg->Finish(pToInsert->m_Hash);
	pToInsert->m_bHashValid = true;
	//DEBUG_ONLY(theApp.QueueDebugLogLine(/*DLP_VERYLOW,*/ false, _T("Set ShaHash for block %u - %u (%u Bytes) to %s"), nStartPos, nStartPos + nSize, nSize, pToInsert->m_Hash.GetString()) );
	
}


/////////////////////////////////////////////////////////////////////////////////////////
///CAICHHashSet
CAICHHashSet::CAICHHashSet(CKnownFile* pOwner)
	: m_pHashTree(0, true, PARTSIZE)
{
	m_eStatus = AICH_EMPTY;
	m_pOwner = pOwner;
}

CAICHHashSet::~CAICHHashSet(void)
{
	FreeHashSet();
}

// delete the hashset except the masterhash (we dont keep aich hashsets in memory to save ressources)
void CAICHHashSet::FreeHashSet(){
	delete m_pHashTree.m_pLeftTree;
	m_pHashTree.m_pLeftTree = NULL;
	delete m_pHashTree.m_pRightTree;
	m_pHashTree.m_pRightTree = NULL;
}

void CAICHHashSet::SetMasterHash(const CAICHHash& Hash, EAICHStatus eNewStatus){
	m_pHashTree.m_Hash = Hash;
	m_pHashTree.m_bHashValid = true;
	SetStatus(eNewStatus);
}

CAICHHashAlgo*	CAICHHashSet::GetNewHashAlgo(){
	return new CSHA();
}

bool CAICHHashSet::ReCalculateHash(bool bDontReplace){
	CAICHHashAlgo* hashalg = GetNewHashAlgo();
	bool bResult = m_pHashTree.ReCalculateHash(hashalg, bDontReplace);
	delete hashalg;
	return bResult;
}

bool CAICHHashSet::VerifyHashTree(bool bDeleteBadTrees){
	CAICHHashAlgo* hashalg = GetNewHashAlgo();
	bool bResult = m_pHashTree.VerifyHashTree(hashalg, bDeleteBadTrees);
	delete hashalg;
	return bResult;
}

void CAICHHashSet::SetFileSize(EMFileSize nSize){
	m_pHashTree.m_nDataSize = nSize;
	m_pHashTree.m_nBaseSize = (nSize <= (uint64)PARTSIZE) ? EMBLOCKSIZE : PARTSIZE;	
}

