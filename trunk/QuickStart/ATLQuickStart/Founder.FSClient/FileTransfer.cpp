// FileTransfer.cpp : Implementation of CFileTransfer

#include "stdafx.h"
#include "FileTransfer.h"
#include <stdio.h>

#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>


// CFileTransfer

struct FtpFile {
	const char *filename;
	FILE *stream;
};

static int my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream)
{
	struct FtpFile *out=(struct FtpFile *)stream;
	if(out && !out->stream) {
		/* open file for writing */
		out->stream=fopen(out->filename, "wb");
		if(!out->stream)
			return -1; /* failure, can't open file to write */
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
	// TODO: Add your implementation code here
	CComBSTR remotePath(RemotePath);
	CComBSTR localPath(RemotePath);
	CURL *curl;
	CURLcode res;
	struct FtpFile ftpfile={
		(const char *)localPath.m_str, /* name to store the file as if succesful */
		NULL
	};

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if(curl) {
		//  curl_easy_setopt(curl, CURLOPT_URL,
		//"ftp://userName:password@172.19.41.114:2100/2011/4/6/1a4e71cf-d0aa-4b3d-a94e-df826aaf1750.zip");
		curl_easy_setopt(curl, CURLOPT_URL,(const char *)remotePath.m_str);


		/* Define our callback to get called when there's data to be written */
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
		/* Set a pointer to our struct to pass to the callback */
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);

		/* Switch on full protocol/debug output */
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);

		res = curl_easy_perform(curl);

		/* always cleanup */
		curl_easy_cleanup(curl);

		if(CURLE_OK != res) {
			/* we failed */
			//*Result = res;
			fprintf(stderr, "curl told us %d\n", res);
			hr = S_FALSE;
		}
	}
	if(ftpfile.stream)
		fclose(ftpfile.stream); /* close the local file */
	curl_global_cleanup();
	return hr;
}
