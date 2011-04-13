// dllmain.h : Declaration of module class.

class CFounderFSClientModule : public CAtlDllModuleT< CFounderFSClientModule >
{
public :
	DECLARE_LIBID(LIBID_FounderFSClientLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_FOUNDERFSCLIENT, "{8165119A-B02C-4AB8-8BD3-24FDCB1262CE}")
};

extern class CFounderFSClientModule _AtlModule;
