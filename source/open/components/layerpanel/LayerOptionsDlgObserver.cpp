//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerOptionsDlgObserver.cpp $
//  
//  Owner: psorrick
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IControlView.h"
#include "IPanelControlData.h"
#include "ISubject.h"
#include "IUIFontSpec.h"

// ----- Includes -----

#include "CDialogObserver.h"

// ----- Utility files -----


// ----- ID.h files -----

#include "LayerPanelID.h"

class LayerOptionsDlgObserver : public CDialogObserver
{
public:
	LayerOptionsDlgObserver(IPMUnknown* boss);
	virtual ~LayerOptionsDlgObserver();

	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);

	virtual void AutoAttach();
	virtual void AutoDetach();

private:
	int32	fOriginalFontID;
	int32	fOriginalHiliteFontID;
};


CREATE_PMINTERFACE(LayerOptionsDlgObserver, kLayerOptionsDlgObserverImpl)

//========================================================================================
// CLASS LayerOptionsDlgObserver
//========================================================================================

LayerOptionsDlgObserver::LayerOptionsDlgObserver(IPMUnknown *boss) :
	CDialogObserver(boss),
	fOriginalFontID(-1),
	fOriginalHiliteFontID(-1)
{
}

LayerOptionsDlgObserver::~LayerOptionsDlgObserver()
{
}

void LayerOptionsDlgObserver::AutoAttach()
{
	CDialogObserver::AutoAttach( );

	InterfacePtr<IPanelControlData> iPanelControlData(this, IID_IPANELCONTROLDATA);
	if (iPanelControlData != nil) 
	{
		AttachToWidget(kLayerShowCheckboxWidgetID, IID_ITRISTATECONTROLDATA, iPanelControlData);
		AttachToWidget(kLayerPrintCheckboxWidgetID, IID_ITRISTATECONTROLDATA, iPanelControlData);
	}
}

void LayerOptionsDlgObserver::AutoDetach()
{
	CDialogObserver::AutoDetach( );

	InterfacePtr<IPanelControlData> iPanelControlData(this, IID_IPANELCONTROLDATA);
	if (iPanelControlData != nil) 
	{
		DetachFromWidget(kLayerShowCheckboxWidgetID, IID_ITRISTATECONTROLDATA, iPanelControlData);
		DetachFromWidget(kLayerPrintCheckboxWidgetID, IID_ITRISTATECONTROLDATA, iPanelControlData);
	}
}

void LayerOptionsDlgObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy)
{
	// need to call the base class Update function
	CDialogObserver::Update(theChange, theSubject, protocol, changedBy);

	InterfacePtr<IControlView> iControlView(theSubject, IID_ICONTROLVIEW);
	if (iControlView != nil) 
	{
		WidgetID widgetID = iControlView->GetWidgetID();
		if (widgetID.Get() == kLayerShowCheckboxWidgetID) 
		{
			InterfacePtr<IPanelControlData> iPanelControlData(this, IID_IPANELCONTROLDATA);
			IControlView* printCheckbox = iPanelControlData->FindWidget(kLayerPrintCheckboxWidgetID);
			if (theChange == kFalseStateMessage)
				printCheckbox->Disable();
			else
				printCheckbox->Enable();
		}
//		else if (widgetID.Get() == kLayerPrintCheckboxWidgetID) 
//		{
//			InterfacePtr<IPanelControlData> iPanelControlData(this, IID_IPANELCONTROLDATA);
//			IControlView* layerName = iPanelControlData->FindWidget(kLayerNameWidgetID);
//			InterfacePtr<IUIFontSpec> fontSpec(layerName, IID_IUIFONTSPEC);
//			if (theChange == kFalseStateMessage)
//			{
//				fontSpec->SetFontID(kPaletteWindowItalicsFontId);
//				fontSpec->SetHiliteFontID(kPaletteWindowBoldItalicsFontId);
//			}
//			else
//			{
//				fontSpec->SetFontID(kPaletteWindowFontId);
//				fontSpec->SetHiliteFontID(kPaletteWindowHiliteFontId);
//			}
//		}
	}
}
