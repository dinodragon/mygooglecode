#pragma once
#include <afxtempl.h>

#define	PARTSIZE			9728000
#define EMBLOCKSIZE			184320

class CAICHHashTree;
class CAICHHashSet;

struct UnknownFile_Struct{
	CString strName;
	CString strDirectory;
};

class CAbstractFile: public CObject
{
	DECLARE_DYNAMIC(CAbstractFile)

public:
	CAbstractFile();
	virtual ~CAbstractFile() { }

	const CString& GetFileName() const { return m_strFileName; }
	virtual void SetFileName(LPCTSTR pszFileName, bool bReplaceInvalidFileSystemChars = false, bool bAutoSetFileType = true); // 'bReplaceInvalidFileSystemChars' is set to 'false' for backward compatibility!

	const uchar* GetFileHash() const { return m_abyFileHash; }
	void SetFileHash(const uchar* pucFileHash);
	bool HasNullHash() const;

	EMFileSize		GetFileSize() const					{ return m_nFileSize; }
	virtual void	SetFileSize(EMFileSize nFileSize)	{ m_nFileSize = nFileSize; }

protected:
	CString m_strFileName;
	uchar	m_abyFileHash[16];
	EMFileSize	m_nFileSize;
};

///////////////////////////////////////////////////////////////////////
//// CKnownFile
///////////////////////////////////////////////////////////////////////
class CKnownFile : public CAbstractFile
{
	DECLARE_DYNAMIC(CKnownFile)

public:
	CKnownFile();
	~CKnownFile();

	virtual void SetFileName(LPCTSTR pszFileName, bool bReplaceInvalidFileSystemChars = false); // 'bReplaceInvalidFileSystemChars' is set to 'false' for backward compatibility!

	const CString& GetPath() const { return m_strDirectory; }
	void SetPath(LPCTSTR path);

	const CString& GetFilePath() const { return m_strFilePath; }
	void SetFilePath(LPCTSTR pszFilePath);

	uint16	GetHashCount() const { return hashlist.GetCount(); }
	uchar*	GetPartHash(uint16 part) const;
	UINT	GetED2KPartHashCount() const { return m_iED2KPartHashCount; }

	virtual void SetFileSize(EMFileSize nFileSize);

	bool	CreateFromFile(LPCTSTR directory, LPCTSTR filename, bool bAICH);

	void	CreateHash(CFile* pFile, uint64 uSize, uchar* pucHash, CAICHHashTree* pShaHashOut = NULL) const;
	bool	CreateHash(FILE* fp, uint64 uSize, uchar* pucHash, CAICHHashTree* pShaHashOut = NULL) const;
	bool	CreateHash(const uchar* pucData, uint32 uSize, uchar* pucHash, CAICHHashTree* pShaHashOut = NULL) const;

	CAICHHashSet* m_pAICHHashSet;
protected:
	CArray<uchar*, uchar*> hashlist;
	CString m_strDirectory;
	CString m_strFilePath;
	uint16 m_iED2KPartHashCount;
	uint16 m_iPartCount;
	uint16 m_iED2KPartCount;
};

///////////////////////////////////////////////////////////////////////
//// CAddFileThread
///////////////////////////////////////////////////////////////////////

class CAddFileThread : public CWinThread
{
	DECLARE_DYNCREATE(CAddFileThread)
protected:
	CAddFileThread();
public:
	virtual BOOL InitInstance();
	virtual int	Run();
	void	SetValues(LPCTSTR directory, LPCTSTR filename, bool bAICH);

private:
	CString			 m_strDirectory;
	CString			 m_strFilename;
	bool			 m_bAICH;
};