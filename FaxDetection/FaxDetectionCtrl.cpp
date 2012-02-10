//**********************************************************
//
// Author: dbose
// Creation date: 27/02/2007
// Description: Main ActiveX control class for the Fax Detection
//
// Completion time: -
//
// Modification history: 
//		[Author]		[Date]			[Modification Log]
//
//*********************************************************

// FaxDetectionCtrl.cpp : Implementation of the CFaxDetectionCtrl ActiveX Control class.

#include "stdafx.h"
#include "FaxDetection.h"
#include "FaxDetectionCtrl.h"
#include "FaxDetectionPropPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CFaxDetectionCtrl, COleControl)



// Message map

BEGIN_MESSAGE_MAP(CFaxDetectionCtrl, COleControl)
	ON_MESSAGE(ID_PROCESS_EVENT, ProcessMessage)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()



// Dispatch map

BEGIN_DISPATCH_MAP(CFaxDetectionCtrl, COleControl)
	DISP_FUNCTION_ID(CFaxDetectionCtrl, "SetWaveID", dispidSetWaveID, SetWaveID, VT_EMPTY, VTS_I2)
	DISP_FUNCTION_ID(CFaxDetectionCtrl, "StartFaxDetection", dispidStartFaxDetection, StartFaxDetection, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CFaxDetectionCtrl, "StopFaxDetection", dispidStopFaxDetection, StopFaxDetection, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CFaxDetectionCtrl, "SetControlParameters", dispidSetControlParameters, SetControlParameters, VT_EMPTY, VTS_I8)
END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(CFaxDetectionCtrl, COleControl)
	EVENT_CUSTOM_ID("DetectionStarted", eventidDetectionStarted, DetectionStarted, VTS_NONE)
	EVENT_CUSTOM_ID("FaxToneDetected", eventidFaxToneDetected, FaxToneDetected, VTS_NONE)
	EVENT_CUSTOM_ID("DetectionStopped", eventidDetectionStopped, DetectionStopped, VTS_NONE)
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CFaxDetectionCtrl, 1)
	PROPPAGEID(CFaxDetectionPropPage::guid)
END_PROPPAGEIDS(CFaxDetectionCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CFaxDetectionCtrl, "FaxDetection.FaxDetectionCtrl.1",
	0xf6ee488, 0x6da4, 0x43d3, 0xaa, 0xf0, 0xd7, 0x5d, 0xe9, 0x3a, 0xb0, 0xc5)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CFaxDetectionCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID BASED_CODE IID_DFaxDetection =
		{ 0x456C0DDE, 0x7D41, 0x4792, { 0xAB, 0xA4, 0x3A, 0xC, 0x80, 0x5D, 0x1A, 0x71 } };
const IID BASED_CODE IID_DFaxDetectionEvents =
		{ 0xDCCBC9D2, 0x3B58, 0x4AD6, { 0x8B, 0xA, 0x8, 0x9, 0xFD, 0xD9, 0x12, 0x2 } };



// Control type information

static const DWORD BASED_CODE _dwFaxDetectionOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CFaxDetectionCtrl, IDS_FAXDETECTION, _dwFaxDetectionOleMisc)



// CFaxDetectionCtrl::CFaxDetectionCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CFaxDetectionCtrl

BOOL CFaxDetectionCtrl::CFaxDetectionCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_FAXDETECTION,
			IDB_FAXDETECTION,
			afxRegApartmentThreading,
			_dwFaxDetectionOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CFaxDetectionCtrl::CFaxDetectionCtrl - Constructor

CFaxDetectionCtrl::CFaxDetectionCtrl()
{
	InitializeIIDs(&IID_DFaxDetection, &IID_DFaxDetectionEvents);
	// TODO: Initialize your control's instance data here.

	//Set messaging details
	m_recorder.SetMessageWindow(this, ID_PROCESS_EVENT);

	//Set the device ID
	m_recorder.SetDeviceID((MCIDEVICEID)0);

	m_bDraw = false;
}


// CFaxDetectionCtrl::~CFaxDetectionCtrl - Destructor

CFaxDetectionCtrl::~CFaxDetectionCtrl()
{
	// TODO: Cleanup your control's instance data here.
}



// CFaxDetectionCtrl::OnDraw - Drawing function

void CFaxDetectionCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: Replace the following code with your own drawing code.
	//pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	//pdc->Ellipse(rcBounds);
	
}

// CFaxDetectionCtrl::DoPropExchange - Persistence support

void CFaxDetectionCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
}



// CFaxDetectionCtrl::OnResetState - Reset control to default state

void CFaxDetectionCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}

LONG CFaxDetectionCtrl::ProcessMessage(WPARAM wParam, LPARAM lParam)
{
	//Process messages posted to the control's window by
	//the core fax tone detection routines...
	int messageID = wParam;

	switch(messageID)
	{
		case FAX_DETECTION_MSG_TONE_DETECTED:
			FaxToneDetected();
			break;
	}

	return TRUE;
}


// CFaxDetectionCtrl message handlers

void CFaxDetectionCtrl::SetWaveID(short waveID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//Set the device ID
	m_recorder.SetDeviceID((MCIDEVICEID)waveID);

}

void CFaxDetectionCtrl::StartFaxDetection(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	//Fire DetectionStarted event
	DetectionStarted();

	//Start the detection
	//
	//Open the device, Allocate the buffers and set formats
	if (m_recorder.Open() == TRUE)
		m_recorder.Start();
	
}

void CFaxDetectionCtrl::StopFaxDetection(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//Stop detection
	m_recorder.Start();
	m_recorder.Close();

	//Fire event
	DetectionStopped();
}

void CFaxDetectionCtrl::SetControlParameters(LONGLONG lpParameterData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//Pass the control parameters
	m_recorder.SetSamplingDetails((void*)lpParameterData);
}
