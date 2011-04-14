// FileTransfer.cpp : Implementation of CFileTransfer

#include "stdafx.h"
#include "FileTransfer.h"
#include <stdio.h>
#include <comutil.h>
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#ifdef _UNICODE
#pragma   comment(lib,   "comsuppw.lib")  //_com_util::ConvertBSTRToString
#else
#pragma   comment(lib,   "comsupp.lib")  //_com_util::ConvertBSTRToString
#endif

// CFileTransfer

struct FtpFile {
	const char *filename;
	FILE *stream;
};

static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t retcode = fread(ptr, size, nmemb, (FILE *)stream);
  return retcode;
}

static int my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream)
{
	struct FtpFile *out=(struct FtpFile *)stream;
	if(out && !out->stream) {
		out->stream=fopen(out->filename, "wb");
		if(!out->stream)
			return -1;
	}
	return fwrite(buffer, size, nmemb, out->stream);
}

STDMETHODIMP CFileTransfer::FtpUpload(BSTR UserName, BSTR Password,BSTR RemotePath, BSTR LocalPath, LONG* Result)
{
	LONG lResult = 0L;
	HRESULT hr = S_OK;
	const char * pUserName = _com_util::ConvertBSTRToString(UserName);
	const char * pPassword = _com_util::ConvertBSTRToString(Password);
	const char * pRemotePath = _com_util::ConvertBSTRToString(RemotePath);
	const char * pLocalPath = _com_util::ConvertBSTRToString(LocalPath);

	CURL *curl;
	CURLcode res;
	FILE *hd_src;
	struct stat file_info;
	curl_off_t fsize;

	struct curl_slist *headerlist=NULL;
	if(stat(pLocalPath, &file_info)) {
		//printf("Couldnt open '%s': %s\n", pLocalPath, strerror(errno));
		lResult = CURLE_FILE_COULDNT_READ_FILE;
		return 1;
	}
	fsize = (curl_off_t)file_info.st_size;
	hd_src = fopen(pLocalPath, "rb");

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
		curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
		curl_easy_setopt(curl, CURLOPT_USERNAME, pUserName);
		curl_easy_setopt(curl, CURLOPT_PASSWORD, pPassword);
		curl_easy_setopt(curl, CURLOPT_URL, pRemotePath);
		curl_easy_setopt(curl, CURLOPT_POSTQUOTE, headerlist);
		curl_easy_setopt(curl, CURLOPT_READDATA, hd_src);
		curl_easy_setopt(curl, CURLOPT_FTP_CREATE_MISSING_DIRS ,2L);
		curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,(curl_off_t)fsize);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if(CURLE_OK != res) {
			lResult = res;
			//fprintf(stderr, "curl told us %d\n", res);
		}
	}
	fclose(hd_src);
	curl_global_cleanup();
	*Result = lResult;
	return hr;
}

//STDMETHODIMP CFileTransfer::Upload(BSTR RemotePath, BSTR LocalPath, VARIANT_BOOL* Result)
//{
//	VARIANT_BOOL bResult = TRUE;
//	HRESULT hr = S_OK;
//	const char * pRemotePath = _com_util::ConvertBSTRToString(RemotePath);
//	const char * pLocalPath = _com_util::ConvertBSTRToString(LocalPath);
//
//	CURL *curl;
//	CURLcode res;
//	FILE *hd_src;
//	struct stat file_info;
//	curl_off_t fsize;
//
//	struct curl_slist *headerlist=NULL;
//	if(stat(pLocalPath, &file_info)) {
//		printf("Couldnt open '%s': %s\n", pLocalPath, strerror(errno));
//		bResult = FALSE;
//		return 1;
//	}
//	fsize = (curl_off_t)file_info.st_size;
//	hd_src = fopen(pLocalPath, "rb");
//
//	curl_global_init(CURL_GLOBAL_ALL);
//	curl = curl_easy_init();
//	if(curl) {
//		curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
//		curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
//		curl_easy_setopt(curl, CURLOPT_URL, pRemotePath);
//		curl_easy_setopt(curl, CURLOPT_POSTQUOTE, headerlist);
//		curl_easy_setopt(curl, CURLOPT_READDATA, hd_src);
//		curl_easy_setopt(curl, CURLOPT_FTP_CREATE_MISSING_DIRS ,2L);
//		curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,(curl_off_t)fsize);
//		res = curl_easy_perform(curl);
//		curl_easy_cleanup(curl);
//		if(CURLE_OK != res) {
//			fprintf(stderr, "curl told us %d\n", res);
//			bResult = FALSE;
//		}
//	}
//	fclose(hd_src);
//	curl_global_cleanup();
//	*Result = bResult;
//	return hr;
//}

STDMETHODIMP CFileTransfer::FtpDownload(BSTR UserName, BSTR Password,BSTR RemotePath, BSTR LocalPath, LONG* Result)
{
	LONG lResult = 0L;
	const char * pUserName = _com_util::ConvertBSTRToString(UserName);
	const char * pPassword = _com_util::ConvertBSTRToString(Password);
	const char * pRemotePath = _com_util::ConvertBSTRToString(RemotePath);
	const char * pLocalPath = _com_util::ConvertBSTRToString(LocalPath);

	CURL *curl;
	CURLcode res;
	struct FtpFile ftpfile={
		pLocalPath,
		NULL
	};

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_USERNAME, pUserName);
		curl_easy_setopt(curl, CURLOPT_PASSWORD, pPassword);
		curl_easy_setopt(curl, CURLOPT_URL,pRemotePath);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
#ifdef _DEBUG
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
#endif
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if(CURLE_OK != res) {
			lResult = res;
			//fprintf(stderr, "curl told us %d\n", res);
		}
	}
	if(ftpfile.stream)
		fclose(ftpfile.stream);
	delete[] pRemotePath;
	curl_global_cleanup();
	*Result = lResult;
	return S_OK;
}


//STDMETHODIMP CFileTransfer::Download(BSTR RemotePath, BSTR LocalPath, VARIANT_BOOL* Result)
//{
//	VARIANT_BOOL bResult = TRUE;
//	HRESULT hr = S_OK;
//	const char * pRemotePath = _com_util::ConvertBSTRToString(RemotePath);
//	const char * pLocalPath = _com_util::ConvertBSTRToString(LocalPath);
//
//	CURL *curl;
//	CURLcode res;
//	struct FtpFile ftpfile={
//		pLocalPath,
//		NULL
//	};
//
//	curl_global_init(CURL_GLOBAL_DEFAULT);
//	curl = curl_easy_init();
//	if(curl) {
//		curl_easy_setopt(curl, CURLOPT_URL,pRemotePath);
//		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
//		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
//#ifdef _DEBUG
//		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
//#endif
//		res = curl_easy_perform(curl);
//		curl_easy_cleanup(curl);
//		if(CURLE_OK != res) {
//			fprintf(stderr, "curl told us %d\n", res);
//			bResult = FALSE;
//		}
//	}
//	if(ftpfile.stream)
//		fclose(ftpfile.stream);
//	delete[] pRemotePath;
//	curl_global_cleanup();
//	*Result = bResult;
//	return hr;
//}

STDMETHODIMP CFileTransfer::GetLastError(BSTR* Result)
{
	// TODO: Add your implementation code here

	return S_OK;
}

