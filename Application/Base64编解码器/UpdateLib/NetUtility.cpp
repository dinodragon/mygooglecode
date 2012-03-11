#include "NetUtility.h"
#include <Windows.h>
#include <Wininet.h>
#pragma comment(lib,"wininet.lib")

bool WaitDownload(const std::string& url, std::string& output, int timeout)
{
	output = "";
	HINTERNET hInternet=InternetOpen(NULL, INTERNET_OPEN_TYPE_PRECONFIG_WITH_NO_AUTOPROXY, NULL, NULL, 0);
	if (!(hInternet))
	{
		return  false;
	}
	const std::string cfg = "Cache-Control:no-cache";
	HINTERNET hOpenUrl=InternetOpenUrl(hInternet,url.c_str(),cfg.c_str(),(DWORD)cfg.length(),INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE,0);
	if (!(hOpenUrl)) {
		InternetCloseHandle(hInternet); 
		hInternet=NULL; 
		return false; 
	}

	char http_status[4];
	DWORD http_status_size = sizeof(http_status);
	if (!HttpQueryInfo(hOpenUrl, HTTP_QUERY_STATUS_CODE,static_cast<LPVOID>(&http_status), &http_status_size,0))
	{
			InternetCloseHandle(hInternet); 
			InternetCloseHandle(hOpenUrl);
			hInternet=NULL; 
			return false; 
	}
	long response_code_ = strtol(http_status, NULL, 10);
	if (response_code_ != 200)
	{
		InternetCloseHandle(hInternet); 
		hInternet=NULL; 
		return false; 
	}

	DWORD dataLength=0;
	DWORD len=0;
	const int BufferSize = 10000;
	char * pBuff = new char[BufferSize];
	memset(pBuff, 0 , BufferSize);
	DWORD msglen = 0;
	DWORD OriginalDateLen = 0;
	while(InternetReadFile(hOpenUrl, (void*)(pBuff), BufferSize, &len))
	{
		if (len == 0)
		{
			break;
		}
		else
		{
			output.append(pBuff,len);
		}
	}
	delete[] pBuff;
	InternetCloseHandle(hOpenUrl); 
	hOpenUrl=NULL; 
	InternetCloseHandle(hInternet); 
	hInternet=NULL;
	return true;
}

