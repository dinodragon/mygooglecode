// UpdaterTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Updater\updater.h"


int _tmain(int argc, _TCHAR* argv[])
{
	bool a = Init("1.5","Base64.xml");
	UPDATEINFO ui;
	bool b = GetUpdateInfo(&ui);
	return 0;
}

