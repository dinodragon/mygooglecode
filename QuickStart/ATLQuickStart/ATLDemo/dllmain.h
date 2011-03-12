// dllmain.h : 模块类的声明。

class CATLDemoModule : public CAtlDllModuleT< CATLDemoModule >
{
public :
	DECLARE_LIBID(LIBID_ATLDemoLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLDEMO, "{1705846D-45F1-4F01-B261-7A0B7AA53CE8}")
};

extern class CATLDemoModule _AtlModule;
