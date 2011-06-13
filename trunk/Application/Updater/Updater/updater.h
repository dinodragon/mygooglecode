#include "stdafx.h"
#ifndef _UPDATER_H
#define _UPDATER_H


enum UPDATEFLAG
{
	U_NO,U_YES,U_RECOMMEND
};

typedef struct
{
	UPDATEFLAG updateFlag;
	char updateUrl[120];
	char newVersion[20];
}UPDATEINFO,*PUPDATEINFO;

bool Init(const char * version,const char * configName);
bool GetUpdateInfo(PUPDATEINFO pUpdateInfo);


#endif