#pragma once

// FaxDetectionCtrl.h : Declaration of the CFaxDetectionCtrl ActiveX Control class.


// CFaxDetectionCtrl : See FaxDetectionCtrl.cpp for implementation.

#include "Recorder.h"

#define ID_PROCESS_EVENT (WM_USER+100)

class CFaxDetectionCtrl : public COleControl
{
	DECLARE_DYNCREATE(CFaxDetectionCtrl)

// Constructor
public:
	CFaxDetectionCtrl();

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
	~CFaxDetectionCtrl();

	DECLARE_OLECREATE_EX(CFaxDetectionCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CFaxDetectionCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CFaxDetectionCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CFaxDetectionCtrl)		// Type name and misc status

	// Message maps
	//{{AFX_MSG(CFaxDetectionCtrl)
	afx_msg LONG ProcessMessage(WPARAM wParam, LPARAM lParam);
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	DECLARE_DISPATCH_MAP()

// Event maps
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
		eventidDetectionStopped = 3L,
		eventidFaxToneDetected = 2L,
		eventidDetectionStarted = 1L,
		dispidSetControlParameters = 4L,
		dispidStopFaxDetection = 3L,
		dispidStartFaxDetection = 2L,
		dispidSetWaveID = 1L
	};

	void SetWaveID(short);
	void StartFaxDetection(void);
	void StopFaxDetection(void);
	void SetControlParameters(LONGLONG lpParameterData);

	

private:
	//On heap
	Recorder m_recorder;
	bool m_bDraw;

protected:

	void DetectionStopped(void)
	{
		FireEvent(eventidDetectionStopped, EVENT_PARAM(VTS_NONE));
	}

	void DetectionStarted(void)
	{
		FireEvent(eventidDetectionStarted, EVENT_PARAM(VTS_NONE));
	}

	void FaxToneDetected(void)
	{
		FireEvent(eventidFaxToneDetected, EVENT_PARAM(VTS_NONE));
	}
};

