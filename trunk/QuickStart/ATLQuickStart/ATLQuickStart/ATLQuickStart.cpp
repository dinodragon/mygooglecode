// ATLQuickStart.cpp : WinMain µÄÊµÏÖ


#include "stdafx.h"
#include "resource.h"
#include "ATLQuickStart_i.h"
#include "dlldatax.h"


class CATLQuickStartModule : public CAtlExeModuleT< CATLQuickStartModule >
{
public :
	DECLARE_LIBID(LIBID_ATLQuickStartLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLQUICKSTART, "{1D0C7C17-AA41-4206-98BF-095AE7624C7B}")
};

CATLQuickStartModule _AtlModule;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
                                LPTSTR /*lpCmdLine*/, int nShowCmd)
{
    return _AtlModule.WinMain(nShowCmd);
}

