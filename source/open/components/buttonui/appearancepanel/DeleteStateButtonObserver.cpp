//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/DeleteStateButtonObserver.cpp $
//  
//  Owner: Tim Wright
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
//  
//  Based on DeleteLayerButtonObserver.cpp in Layer Panel Project
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "CObserver.h"

#include "ILayerList.h"
#include "IDocument.h"
#include "ISubject.h"
#include "InterfacePtr.h"
#include "ITriStateControlData.h"
#include "ICommand.h"
#include "IDocumentLayer.h"
#include "IControlView.h"
#include "ILayoutControlData.h"
#include "IPanelControlData.h"
#include "IWidgetParent.h"
#include "ITextControlData.h"

#include "UIDList.h"
#include "EventUtilities.h"
#include "ILayoutUIUtils.h"
#include "CmdUtils.h"
#include "LayoutUIID.h"
#include "widgetid.h"
#include "IPalettePanelUtils.h"
#include "CAlert.h"

#include "FormFieldUIID.h"
#include "AppearancePanelUtils.h"

//----------------------------------------------------------------------------------------
//
// Class definition
//
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Class DeleteStateButtonObserver
//----------------------------------------------------------------------------------------

class DeleteStateButtonObserver : public CObserver
{
	public:
		DeleteStateButtonObserver(IPMUnknown *boss);
		virtual ~DeleteStateButtonObserver();
		
		virtual void AutoAttach();
		virtual void AutoDetach();
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);


	private:
		void UpdateButton();
};




//----------------------------------------------------------------------------------------
//
// Class implementation
//
//----------------------------------------------------------------------------------------

//========================================================================================
// CLASS DeleteStateButtonObserver
//========================================================================================

CREATE_PMINTERFACE(DeleteStateButtonObserver, kDeleteStateButtonObserverImpl)

//----------------------------------------------------------------------------------------
// DeleteStateButtonObserver constructor 
//----------------------------------------------------------------------------------------

DeleteStateButtonObserver::DeleteStateButtonObserver(IPMUnknown *boss) :
	CObserver(boss)
{
}


//----------------------------------------------------------------------------------------
// DeleteStateButtonObserver::~DeleteStateButtonObserver: 
//----------------------------------------------------------------------------------------

DeleteStateButtonObserver::~DeleteStateButtonObserver()
{
}


//----------------------------------------------------------------------------------------
// DeleteStateButtonObserver::AutoAttach: 
// We also observe IID_ILISTCONTROLDATA, but that is hooked up
// when the listbox is created. See LayerPanelObserver.cpp, AutoAttach.
//----------------------------------------------------------------------------------------

void DeleteStateButtonObserver::AutoAttach()
{
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
		subject->AttachObserver(this, IID_ITRISTATECONTROLDATA);

	this->UpdateButton();
}

//----------------------------------------------------------------------------------------
// DeleteStateButtonObserver::AutoDetach: 
//----------------------------------------------------------------------------------------

void DeleteStateButtonObserver::AutoDetach()
{
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
		subject->DetachObserver(this, IID_ITRISTATECONTROLDATA);
}

//----------------------------------------------------------------------------------------
// DeleteStateButtonObserver::Update: 
//----------------------------------------------------------------------------------------

void DeleteStateButtonObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	// ==> Please update GetObserverInfo()  <==

	if (theChange == kTrueStateMessage)
	{
		IDocument* doc = Utils<ILayoutUIUtils>()->GetFrontDocument();
		InterfacePtr<ITriStateControlData> data(this, IID_ITRISTATECONTROLDATA);
		if (doc != nil && data->IsSelected())
		{

			InterfacePtr<IControlView> frontView(Utils<ILayoutUIUtils>()->QueryFrontView());
			if (frontView)
			{
				InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kAppearanceParentWidgetId));

				// Check if the Alt/Option key is down
				bool16 optionKeyDown = ::IsOptionAltKeyPressed();
				if ( !optionKeyDown && HasStateContent(panelData) ) {
					
					// Display a delete warning dialog
			        PMString alertStr("$$$/Dialog/FormFieldUI/DeleteAlert");
			        int16 whatToDo = CAlert::ModalAlert(alertStr,
			                                            kOKString, 
			                                            kCancelString, 
			                                            kNullString, 
			                                            1,                        // pass in 1, 2, or 3 to make that button the default button or 0 for no default
			                                            CAlert::eWarningIcon);
			        // If they don't want to continue, then punt
					if ( whatToDo == 2 )
						return;
				}
				
				DeleteSelectedStates(panelData);
			}
		}
	}
	else {
		this->UpdateButton();
	}
}

//----------------------------------------------------------------------------------------
// DeleteStateButtonObserver::UpdateButton: 
//----------------------------------------------------------------------------------------
void DeleteStateButtonObserver::UpdateButton()
{
	InterfacePtr<IControlView> pView( this, IID_ICONTROLVIEW ) ;
	
	// Get widgetparent for the layer panel itself
	InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kAppearanceParentWidgetId));
	if (panelData != nil)
	{
		bool16 canDelete = CanDeleteSelectedStates(panelData);
		
		if (pView->GetEnableState() && !canDelete)
			pView->Disable();
		else if (!pView->GetEnableState() && canDelete)
			pView->Enable();
	}
}



