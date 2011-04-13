// dllmain.h : Declaration of module class.

class CCOMServerModule : public CAtlDllModuleT< CCOMServerModule >
{
public :
	DECLARE_LIBID(LIBID_COMServerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_COMSERVER, "{2F5BC82E-BC76-4630-84B2-05247E1D8EDA}")
};

extern class CCOMServerModule _AtlModule;
