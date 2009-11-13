#pragma once

#include <Windows.h>
#include <string>

class CSelectFolder
{
	// ππ‘Ï
public:
	CSelectFolder();
	bool SelectFolder(const wchar_t * initPath,wchar_t * resultPath);
};