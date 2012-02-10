// FaxDetectionPropPage.cpp : Implementation of the CFaxDetectionPropPage property page class.

#include "stdafx.h"
#include "AMSFaxDetection.h"
#include "FaxDetectionPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CFaxDetectionPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CFaxDetectionPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CFaxDetectionPropPage, "FaxDetection.FaxDetectionPropPage.1",
	0x640ad211, 0x478f, 0x4845, 0xaa, 0x1d, 0xe1, 0xe7, 0xef, 0x4a, 0x57, 0xfb)



// CFaxDetectionPropPage::CFaxDetectionPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CFaxDetectionPropPage

BOOL CFaxDetectionPropPage::CFaxDetectionPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_FAXDETECTION_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CFaxDetectionPropPage::CFaxDetectionPropPage - Constructor

CFaxDetectionPropPage::CFaxDetectionPropPage() :
	COlePropertyPage(IDD, IDS_FAXDETECTION_PPG_CAPTION)
{
}



// CFaxDetectionPropPage::DoDataExchange - Moves data between page and properties

void CFaxDetectionPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CFaxDetectionPropPage message handlers
