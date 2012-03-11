#include "Updater.h"
#include <process.h>
#include "NetUtility.h"
#include "../../../../base/unicode/unicode.h"
#include "UpdateInfo.h"


namespace yfupdate
{
	const std::string updateServer1 = "http://yangfei.googlecode.com/svn/update/1.0/";
	const std::string updateServer2 = "http://update.yangfei.org/update/1.0/";
	bool UpdateLib::CheckNewVersion(const std::string&productName,const std::string &productVersion,const std::string & productTitle)
	{
		productName_ = productName;
		productVersion_ = productVersion;
		productTitle_ = productTitle;
		::_beginthreadex(0, 0, CheckUpdate,(PVOID)this, 0, NULL);
		return true;
	}

	unsigned int _stdcall UpdateLib:: CheckUpdate(LPVOID param)
	{
		UpdateLib *pThis = static_cast<UpdateLib *>(param);
		std::string xml;
		std::string url = updateServer1 + pThis->productName_ + "/" + pThis->productVersion_ + "/update.xml";
		bool result = WaitDownload(url,xml);
		if (!result)
		{
			//主域名失败，则再测试备用域名。
			url = updateServer2 + pThis->productName_ + "/" + pThis->productVersion_ + "/update.xml";
			result = WaitDownload(url,xml);
			if (!result)
			{
				return -1;
			}
		}
		else if (xml.length() < 60)
		{
			return 0;
		}
		
		xml = yfbase::utf82string(xml);
		CUpdateInfo info;
		if(!info.Init(xml))
		{
			return -1;
		}
		MessageBox(NULL,info.GetUpdateMsg().c_str(),pThis->productTitle_.c_str(),MB_OK);
		ShellExecute(NULL,TEXT("open"),info.GetUpdateUrl().c_str(),NULL,NULL,SW_SHOWNORMAL);
		return 0;
	}
}
