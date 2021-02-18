//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/dialogs/selectabledialogs/CSelectableDialogObserver.cpp $
//  
//  Owner: Tom Taylor
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

#include "VCWidgetHeaders.h"

#include "CSelectableDialogObserver.h"

// ----- Interface Includes -----

#include "IControlView.h"
#include "IListBoxController.h"
#include "IPanelControlData.h"
#include "ISubject.h"
#include "ISelectableDialogSwitcher.h"
#include "IDropDownListController.h"

// ----- Implementation Includes -----

//#include "CmdUtils.h"
#include "widgetid.h"


// BP 04/17/01: moved to  .../source/components/WidgetBin/WidgetBinImpl.cpp
// CREATE_PMINTERFACE(CSelectableDialogObserver, kCSelectableDialogObserverImpl)

//========================================================================================
// CLASS CSelectableDialogObserver
//========================================================================================

CSelectableDialogObserver::CSelectableDialogObserver(IPMUnknown *boss) :
	CDialogObserver(boss)
{
}

CSelectableDialogObserver::~CSelectableDialogObserver()
{
}

void CSelectableDialogObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy)
{
	CDialogObserver::Update(theChange, theSubject, protocol, changedBy);
	
	InterfacePtr<IControlView> view(theSubject, IID_ICONTROLVIEW);
	if (view) {
		InterfacePtr<ISelectableDialogSwitcher> panelSwitcher(this, IID_ISELECTABLEDIALOGSWITCHER);

		//----------------------------
		// Handle Selectable Dialog ListBox
		//----------------------------
		if (view->GetWidgetID() == panelSwitcher->GetSelectionListWidgetID()) 
		{
			bool16 panelSwitched = kFalse;
			if ( (theChange == kListSelectionChangedMessage) || (theChange == kListSelectionChangedByUserMessage) )
				panelSwitched = kTrue; //Listbox implementation
			else if (theChange == kSelectedTabChangedMessage)
				panelSwitched = kTrue; // Tab implementation

			if (panelSwitched)
			{
				int32 panelIndex = this->GetSelectedPanelIndex();
				if (panelIndex >= 0)
				{
					panelSwitcher->SwitchDialogPanel(panelIndex);
				}
			}
			else if (theChange == kPopupChangeStateMessage)
			{
				InterfacePtr<IDropDownListController> listController(view, UseDefaultIID());
				ASSERT_MSG(listController, "IDropDownListController not found");
				panelSwitcher->SwitchDialogPanel(listController->GetSelected());
			}
		}
	}
}

void CSelectableDialogObserver::AutoAttach()
{
	CDialogObserver::AutoAttach();
		
	InterfacePtr<IPanelControlData> panelData(this, IID_IPANELCONTROLDATA);
	if (panelData)
	{

		InterfacePtr<ISelectableDialogSwitcher> panelSwitcher(this, IID_ISELECTABLEDIALOGSWITCHER);
		AttachToWidget(panelSwitcher->GetSelectionListWidgetID(), IID_ILISTCONTROLDATA, panelData);
		AttachToWidget(panelSwitcher->GetSelectionListWidgetID(), IID_ISTRINGLISTCONTROLDATA, panelData);
	}
}

void CSelectableDialogObserver::AutoDetach()
{
	CDialogObserver::AutoDetach();

	InterfacePtr<IPanelControlData> panelData(this, IID_IPANELCONTROLDATA);
	if (panelData)
	{
		InterfacePtr<ISelectableDialogSwitcher> panelSwitcher(this, IID_ISELECTABLEDIALOGSWITCHER);
		DetachFromWidget(panelSwitcher->GetSelectionListWidgetID(), IID_ILISTCONTROLDATA, panelData);
		DetachFromWidget(panelSwitcher->GetSelectionListWidgetID(), IID_ISTRINGLISTCONTROLDATA, panelData);
	}
}

int32 CSelectableDialogObserver::GetSelectedPanelIndex()
{
	InterfacePtr<ISelectableDialogSwitcher> panelSwitcher(this, IID_ISELECTABLEDIALOGSWITCHER);
	InterfacePtr<IPanelControlData> iPanelControlData(this, IID_IPANELCONTROLDATA);
	InterfacePtr<IListBoxController> listCntl( iPanelControlData->FindWidget(panelSwitcher->GetSelectionListWidgetID()), IID_ILISTBOXCONTROLLER );
	return (listCntl->GetSelected());
}
