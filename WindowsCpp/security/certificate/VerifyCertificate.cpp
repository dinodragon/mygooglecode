#include <windows.h>
#include <wincrypt.h>
#include <Softpub.h>
#include <wintrust.h>
#include <stdio.h>
#include <tchar.h>
#include <string>

#pragma comment(lib, "crypt32.lib")
#pragma comment (lib, "wintrust")

#define ENCODING (X509_ASN_ENCODING | PKCS_7_ASN_ENCODING)

bool CheckEmbeddedSignature(LPCWSTR szFileName,LPCWSTR szIncName);
bool VerifyEmbeddedSignature(LPCWSTR pwszSourceFile);
int _tmain(int argc, TCHAR *argv[])
{
  WCHAR szFileName[MAX_PATH]; 
  if (argc != 2)
  {
    _tprintf(_T("Usage: SignedFileInfo <filename>\n"));
    return 0;
  }
  VerifyEmbeddedSignature(L"D:\\DatebaseCopy.exe");
  lstrcpynW(szFileName, argv[1], MAX_PATH);
  bool ok = CheckEmbeddedSignature(szFileName,L"Renren Inc.");
}

//验证文件的数字签名是否可信。
bool VerifyEmbeddedSignature(LPCWSTR pwszSourceFile)
{
    LONG lStatus;
    // Initialize the WINTRUST_FILE_INFO structure.
    WINTRUST_FILE_INFO FileData;
    memset(&FileData, 0, sizeof(FileData));
    FileData.cbStruct = sizeof(WINTRUST_FILE_INFO);
    FileData.pcwszFilePath = pwszSourceFile;
    FileData.hFile = NULL;
    FileData.pgKnownSubject = NULL;

    /*
    WVTPolicyGUID specifies the policy to apply on the file
    WINTRUST_ACTION_GENERIC_VERIFY_V2 policy checks:
    
    1) The certificate used to sign the file chains up to a root 
    certificate located in the trusted root certificate store. This 
    implies that the identity of the publisher has been verified by 
    a certification authority.
    
    2) In cases where user interface is displayed (which this example
    does not do), WinVerifyTrust will check for whether the  
    end entity certificate is stored in the trusted publisher store,  
    implying that the user trusts content from this publisher.
    
    3) The end entity certificate has sufficient permission to sign 
    code, as indicated by the presence of a code signing EKU or no 
    EKU.
    */

    GUID WVTPolicyGUID = WINTRUST_ACTION_GENERIC_VERIFY_V2;
    WINTRUST_DATA WinTrustData;

    // Initialize the WinVerifyTrust input data structure.

    // Default all fields to 0.
    memset(&WinTrustData, 0, sizeof(WinTrustData));

    WinTrustData.cbStruct = sizeof(WinTrustData);
    
    // Use default code signing EKU.
    WinTrustData.pPolicyCallbackData = NULL;

    // No data to pass to SIP.
    WinTrustData.pSIPClientData = NULL;

    // Disable WVT UI.
    WinTrustData.dwUIChoice = WTD_UI_NONE;

    // No revocation checking.
    WinTrustData.fdwRevocationChecks = WTD_REVOKE_NONE; 

    // Verify an embedded signature on a file.
    WinTrustData.dwUnionChoice = WTD_CHOICE_FILE;

    // Default verification.
    WinTrustData.dwStateAction = 0;

    // Not applicable for default verification of embedded signature.
    WinTrustData.hWVTStateData = NULL;

    // Not used.
    WinTrustData.pwszURLReference = NULL;

    // This is not applicable if there is no UI because it changes 
    // the UI to accommodate running applications instead of 
    // installing applications.
    WinTrustData.dwUIContext = 0;

    // Set pFile.
    WinTrustData.pFile = &FileData;

    // WinVerifyTrust verifies signatures as specified by the GUID 
    // and Wintrust_Data.
    lStatus = WinVerifyTrust(
        NULL,
        &WVTPolicyGUID,
        &WinTrustData);
    if(ERROR_SUCCESS != lStatus)
    {
      return false;
    }
    return true;
}

bool CheckEmbeddedSignature(LPCWSTR pwszFileName,LPCWSTR pwszIncName)
{
	HCERTSTORE hStore = NULL;
	HCRYPTMSG hMsg = NULL; 
	PCCERT_CONTEXT pCertContext = NULL;
	BOOL fResult;   
	DWORD dwEncoding, dwContentType, dwFormatType;
	PCMSG_SIGNER_INFO pSignerInfo = NULL;
	PCMSG_SIGNER_INFO pCounterSignerInfo = NULL;
	DWORD dwSignerInfo;
	CERT_INFO CertInfo;     

	bool breturn = false;
	__try
	{
		// Get message handle and store handle from the signed file.
		fResult = CryptQueryObject(CERT_QUERY_OBJECT_FILE,
			pwszFileName,
			CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED_EMBED,
			CERT_QUERY_FORMAT_FLAG_BINARY,
			0,
			&dwEncoding,
			&dwContentType,
			&dwFormatType,
			&hStore,
			&hMsg,
			NULL);
		if (!fResult)
		{
			__leave;
		}
		// Get signer information size.
		fResult = CryptMsgGetParam(hMsg, 
			CMSG_SIGNER_INFO_PARAM, 
			0, 
			NULL, 
			&dwSignerInfo);
		if (!fResult)
		{
			__leave;
		}
		// Allocate memory for signer information.
		pSignerInfo = (PCMSG_SIGNER_INFO)LocalAlloc(LPTR, dwSignerInfo);
		if (!pSignerInfo)
		{
			__leave;
		}

		// Get Signer Information.
		fResult = CryptMsgGetParam(hMsg, 
			CMSG_SIGNER_INFO_PARAM, 
			0, 
			(PVOID)pSignerInfo, 
			&dwSignerInfo);
		if (!fResult)
		{
			__leave;
		}

		// Search for the signer certificate in the temporary 
		// certificate store.
		CertInfo.Issuer = pSignerInfo->Issuer;
		CertInfo.SerialNumber = pSignerInfo->SerialNumber;
    pCertContext = CertFindCertificateInStore(hStore,
      ENCODING,
      0,
      CERT_FIND_SUBJECT_CERT,
      (PVOID)&CertInfo,
      NULL);
    if (!pCertContext)
    {
      _tprintf(_T("CertFindCertificateInStore failed with %x\n"),
        GetLastError());
      __leave;
    }

		// Print Signer certificate information.
    DWORD dwData;
    LPTSTR szName = NULL;
    if (!(dwData = CertGetNameString(pCertContext, 
      CERT_NAME_SIMPLE_DISPLAY_TYPE,
      0,
      NULL,
      NULL,
      0)))
    {
      __leave;
    }

    // Allocate memory for subject name.
    szName = (LPTSTR)LocalAlloc(LPTR, dwData * sizeof(TCHAR));
    if (!szName)
    {
      _tprintf(_T("Unable to allocate memory for subject name.\n"));
      __leave;
    }

    // Get subject name.
    if (!(CertGetNameString(pCertContext, 
      CERT_NAME_SIMPLE_DISPLAY_TYPE,
      0,
      NULL,
      szName,
      dwData)))
    {
      _tprintf(_T("CertGetNameString failed.\n"));
      __leave;
    }

    if (0 == wcscmp(szName,pwszIncName))
    {
      breturn = VerifyEmbeddedSignature(pwszFileName);
      __leave;
    }
  }
  __finally
  {
		if (pSignerInfo != NULL) LocalFree(pSignerInfo);
		if (pCounterSignerInfo != NULL) LocalFree(pCounterSignerInfo);
		if (pCertContext != NULL) CertFreeCertificateContext(pCertContext);
		if (hStore != NULL) CertCloseStore(hStore, 0);
		if (hMsg != NULL) CryptMsgClose(hMsg);
	}
	return breturn;
}
