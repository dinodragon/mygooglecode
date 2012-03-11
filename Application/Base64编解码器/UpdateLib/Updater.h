#ifndef __UPDATER_H_
#define __UPDATER_H_
#pragma once

#include <string>
#include <Windows.h>

namespace yfupdate
{
	class UpdateLib
	{
		std::string productName_;
		std::string productVersion_;
		std::string productTitle_;
	public:
		bool CheckNewVersion(const std::string&productName,const std::string &productVersion,const std::string & productTitle);
	private:
		static unsigned int _stdcall CheckUpdate(LPVOID param);
	};
	
}//namespace yfupdate

#endif
