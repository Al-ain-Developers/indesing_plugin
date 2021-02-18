//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/ToggleStatesButtonObserver.cpp $
//  
//  Owner: lance bushore
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
#include "IPanelDetailController.h"
#include "ISubject.h"
#include "IWidgetParent.h"
#include "IWidgetUtils.h"

// ----- Includes -----

#include "CObserver.h"
#include "IconRsrcDefs.h"

// ----- Utility files -----
#include "Utils.h"

#include "FormFieldUIID.h"

//========================================================================================
// CLASS ToggleStatesButtonObserver
//========================================================================================
class ToggleStatesButtonObserver : public CObserver
{
	public:
		ToggleStatesButtonObserver(IPMUnknown *boss);
		virtual ~ToggleStatesButtonObserver();
		
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
		
		virtual void AutoAttach();
		virtual void AutoDetach();
	
	private:
		void	UpdateStatesSectionButtonState();

};


CREATE_PMINTERFACE(ToggleStatesButtonObserver, kToggleStatesButtonObserverImpl)

//----------------------------------------------------------------------------------------
// ToggleStatesButtonObserver constructor 
//----------------------------------------------------------------------------------------

ToggleStatesButtonObserver::ToggleStatesButtonObserver(IPMUnknown *boss) :
	CObserver(boss)
{
}

//----------------------------------------------------------------------------------------
// ToggleStatesButtonObserver::~ToggleStatesButtonObserver: 
//----------------------------------------------------------------------------------------

ToggleStatesButtonObserver::~ToggleStatesButtonObserver()
{
}

//----------------------------------------------------------------------------------------
// ToggleStatesButtonObserver::AutoAttach: 
//----------------------------------------------------------------------------------------
void ToggleStatesButtonObserver::AutoAttach()
{
	InterfacePtr<ISubject> subject(this, UseDefaultIID());
	if (subject)
		subject->AttachObserver(this, IID_ITRISTATECONTROLDATA);

	UpdateStatesSectionButtonState();
}

//----------------------------------------------------------------------------------------
// ToggleStatesButtonObserver::AutoDetach: 
//----------------------------------------------------------------------------------------
void ToggleStatesButtonObserver::AutoDetach()
{
	InterfacePtr<ISubject> subject(this, UseDefaultIID());
	if (subject)
		subject->DetachObserver(this, IID_ITRISTATECONTROLDATA);
}

void ToggleStatesButtonObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	#pragma unused(theSubject,protocol,changedBy)
	if (theChange == kTrueStateMessage)
	{
		InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
		InterfacePtr<IPanelDetailController> detailController((IPanelDetailController *)parentHolder->QueryParentFor(IID_ILISTBOXDETAILCONTROLLER));
		if(detailController)
		{
			IWidgetUtils *iWidgetUtils = Utils<IWidgetUtils>();
			InterfacePtr<IControlView> buttonView((IControlView*)iWidgetUtils->QueryRelatedWidget(detailController, kToggleStatesButtonWidgetID, IID_ICONTROLVIEW));
			InterfacePtr<IControlView> statesView((IControlView*)iWidgetUtils->QueryRelatedWidget(detailController, kStateListBoxesContainerWidgetID, IID_ICONTROLVIEW));

			if ( statesView && statesView->IsVisible() )
			{
				statesView->HideView();
				buttonView->SetRsrcID(kTreeBranchCollapsedRsrcID);
			}
			else if ( statesView )
			{
				statesView->ShowView(kTrue);
				buttonView->SetRsrcID(kTreeBranchExpandedRsrcID);
			}
			
			detailController->ShowDetailLevel(detailController->GetDetailLevel());
		}
	}
}

void ToggleStatesButtonObserver::UpdateStatesSectionButtonState()
{
	InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
	InterfacePtr<IPanelDetailController> detailController((IPanelDetailController *)parentHolder->QueryParentFor(IID_ILISTBOXDETAILCONTROLLER));
	if(detailController)
	{
		IWidgetUtils *iWidgetUtils = Utils<IWidgetUtils>();
		InterfacePtr<IControlView> buttonView((IControlView*)iWidgetUtils->QueryRelatedWidget(detailController, kToggleStatesButtonWidgetID, IID_ICONTROLVIEW));
		InterfacePtr<IControlView> statesView((IControlView*)iWidgetUtils->QueryRelatedWidget(detailController, kStateListBoxesContainerWidgetID, IID_ICONTROLVIEW));
		if ( statesView && statesView->IsVisible() )
			buttonView->SetRsrcID(kTreeBranchExpandedRsrcID);
		else
			buttonView->SetRsrcID(kTreeBranchCollapsedRsrcID);
	}
}

