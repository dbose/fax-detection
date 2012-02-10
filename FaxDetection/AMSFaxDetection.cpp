// FaxDetection.cpp : Implementation of CFaxDetectionApp and DLL registration.

#include "stdafx.h"
#include "AMSFaxDetection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CFaxDetectionApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x9521D099, 0x9240, 0x4F30, { 0x85, 0x48, 0xB5, 0x89, 0x67, 0x41, 0xB7, 0xAD } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CFaxDetectionApp::InitInstance - DLL initialization

BOOL CFaxDetectionApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CFaxDetectionApp::ExitInstance - DLL termination

int CFaxDetectionApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
