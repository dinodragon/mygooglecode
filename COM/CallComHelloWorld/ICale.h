#ifndef __ICale_H__
#define __ICale_H__

#ifndef __IMyUnknown_H__
#include "IMyUnknown.h"
#endif

typedef unsigned short *String;

// {54BF6568-1007-11D1-B0AA-444553540000}
extern "C" const GUID IID_Computer = 
		{ 0x54bf6568, 0x1007, 0x11d1,
		{ 0xb0, 0xaa, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00} } ;

class ICale : public IMyUnknown 
{
	public : 
		virtual BOOL __stdcall Initialize() = 0;
		virtual BOOL __stdcall Add(int,int ,int *) = 0;
};

#endif // __ICale_H__
