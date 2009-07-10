#ifndef __ICale_H__
#define __ICale_H__

#include "Unknwn.h"

typedef unsigned short *String;

class ICale : public IUnknown 
{
	public : 
		virtual BOOL __stdcall Initialize() = 0;
		virtual BOOL __stdcall Add(int,int ,int *) = 0;
};

#endif // __ICale_H__
