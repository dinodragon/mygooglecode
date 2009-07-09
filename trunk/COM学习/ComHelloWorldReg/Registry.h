#ifndef __Registry_H__
#define __Registry_H__
//
// Registry.h
//   - Helper functions registering and unregistering a component.
//
//   - These helper functions were borrowed and modifed from
//     Dale Rogerson's book Inside COM.

// This function will register a component in the Registry.
// DllRegisterServer function should call this function.
HRESULT RegisterServer(const CLSID& clsid,
					   const TCHAR *szFileName, 
					   const TCHAR* szProgID,
					   const TCHAR* szDescription,
					   const TCHAR* szVerIndProgID) ;

// This function will unregister a component.  Components
// DllUnregisterServer function should call this function.
HRESULT UnregisterServer(const CLSID& clsid,
						 const TCHAR* szProgID,
						 const TCHAR* szVerIndProgID) ;

#endif