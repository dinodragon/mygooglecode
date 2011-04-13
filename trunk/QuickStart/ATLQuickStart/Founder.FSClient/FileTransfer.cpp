// FileTransfer.cpp : Implementation of CFileTransfer

#include "stdafx.h"
#include "FileTransfer.h"
#include <stdio.h>
#include <comutil.h>
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>
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

STDMETHODIMP CFileTransfer::Upload(BSTR RemotePath, BSTR LocalPath, BSTR* Result)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CFileTransfer::Download(BSTR RemotePath, BSTR LocalPath, BSTR* Result)
{
	HRESULT hr = S_OK;
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
		curl_easy_setopt(curl, CURLOPT_URL,pRemotePath);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if(CURLE_OK != res) {
			fprintf(stderr, "curl told us %d\n", res);
			hr = S_FALSE;
		}
	}
	if(ftpfile.stream)
		fclose(ftpfile.stream);
	delete[] pRemotePath;
	curl_global_cleanup();
	return hr;
}
