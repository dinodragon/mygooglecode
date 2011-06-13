#include "stdafx.h"
#include "updater.h"
#include "curl\curl.h"
#include "curl\types.h"
#include "curl\easy.h"
#include "tinyxml.h"
#include <iostream>

using namespace std;

#define MAXFILELENGTH 1024
struct FtpFile {
	const char *filename;
	FILE *stream;
};



char xmlString[MAXFILELENGTH];
char version[20];


const char * SERVER1 = "http://mygooglecode.googlecode.com/files/";

static int writer(char *data, size_t size, size_t nmemb,char *writerData)
{
	if (writerData == NULL)
		return 0;
	if(size*nmemb > MAXFILELENGTH)
		return 0;
	memcpy(writerData,data,size*nmemb);
	return size * nmemb;
}

bool Init(const char * version,const char * configName)
{
	strcpy(::version,version);
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
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &xmlString);
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

int VerCmp(const char * ver1,const char * ver2)
{
	return strcmp(ver1,ver2);
}

bool GetUpdateInfo(PUPDATEINFO pUpdateInfo)
{
	pUpdateInfo->updateFlag = U_NO;
	strcpy(pUpdateInfo->newVersion,"0.0");
	strcpy(pUpdateInfo->updateUrl,"http://www.yangfei.org");

	TiXmlDocument doc;
	int iRecommend = 0;
	doc.Parse(xmlString);
	TiXmlNode *pNode = doc.RootElement()->FirstChild();
	while(pNode != NULL)
	{
		if(strcmp(pNode->Value(),"LastVersion") == 0)
		{
			strcpy(pUpdateInfo->newVersion,pNode->FirstChild()->Value());
		}
		if(strcmp(pNode->Value(),"Recommend") == 0)
		{
			iRecommend = atoi(pNode->FirstChild()->Value());
		}
		if(strcmp(pNode->Value(),"UpdateUrl") == 0)
		{
			strcpy(pUpdateInfo->updateUrl,pNode->FirstChild()->Value());
		}
		pNode = pNode->NextSibling();
	}
	if(VerCmp(pUpdateInfo->newVersion,version) > 0)
	{
		pUpdateInfo->updateFlag = UPDATEFLAG(U_YES + iRecommend);
	}
	return false;
}