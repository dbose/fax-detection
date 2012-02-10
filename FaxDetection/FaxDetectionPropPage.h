#pragma once

// FaxDetectionPropPage.h : Declaration of the CFaxDetectionPropPage property page class.


// CFaxDetectionPropPage : See FaxDetectionPropPage.cpp for implementation.

class CFaxDetectionPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CFaxDetectionPropPage)
	DECLARE_OLECREATE_EX(CFaxDetectionPropPage)

// Constructor
public:
	CFaxDetectionPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_FAXDETECTION };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

