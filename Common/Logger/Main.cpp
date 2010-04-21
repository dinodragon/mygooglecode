// Main.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Logger.h"


int _tmain(int argc, _TCHAR* argv[])
{
	CLogger log;
	log.WriteLog(L"日志内容");

	//写到了C:\\PluginLog.txt
	return 0;
}

