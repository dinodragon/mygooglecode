#ifndef __UPDATEINFO_H_
#define __UPDATEINFO_H_

#pragma once
#include <string>

class CUpdateInfo
{
private:
	std::string lastVersion_;
	std::string updateUrl_;
	std::string updateMsg_;
public:
	CUpdateInfo(void);
	~CUpdateInfo(void);
	bool Init(const std::string& updateXml);
	std::string GetUpdateMsg() const {return updateMsg_;}
	std::string GetUpdateUrl() const {return updateUrl_;}
};

#endif //__UPDATEINFO_H_