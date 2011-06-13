#include "stdafx.h"
#include "updater.h"
#include "curl\curl.h"
#include "curl\types.h"
#include "curl\easy.h"

struct FtpFile {
	const char *filename;
	FILE *stream;
};

const char * SERVER1 = "http://mygooglecode.googlecode.com/files/";

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

bool Init(const char * version,const char * configName)
{
	LONG lResult = 0L;
	char pRemotePath[100];
	strcpy(pRemotePath,SERVER1);
	strcat(pRemotePath,configName);
	char pLocalPath[80] = "F:\\aa.xml";
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
	curl_global_cleanup();
	return 0==lResult;
}

bool GetUpdateInfo(PUPDATEINFO pUpdateInfo)
{
	return false;
}