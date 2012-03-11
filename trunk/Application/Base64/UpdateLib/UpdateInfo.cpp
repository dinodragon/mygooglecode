#include "UpdateInfo.h"
#include "tinyxml/tinyxml.h"

CUpdateInfo::CUpdateInfo(void)
{
}

CUpdateInfo::~CUpdateInfo(void)
{
}

bool CUpdateInfo::Init(const std::string &updateXml)
{
	try
	{
		TiXmlDocument doc;
		doc.Parse(updateXml.c_str());
		TiXmlElement* pRoot = doc.RootElement();
		if (!pRoot)
		{
			return false;
		}
		if (!pRoot->FirstChild("UpdateUrl") || !pRoot->FirstChild("UpdateMsg"))
		{
			return false;
		}
		updateUrl_ = pRoot->FirstChild("UpdateUrl")->FirstChild()->Value();
		updateMsg_ = pRoot->FirstChild("UpdateMsg")->FirstChild()->Value();
	}
	catch (...)
	{
		return false;
	}
	return true;
}
