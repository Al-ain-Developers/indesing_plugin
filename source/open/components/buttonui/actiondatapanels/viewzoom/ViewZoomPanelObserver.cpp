//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/viewzoom/ViewZoomPanelObserver.cpp $
//  
//  Owner: Mark VerMurlen
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

// ----- Interface Includes -----

#include "IBehaviorData.h"
#include "IControlView.h"
#include "IDropDownListController.h"
#include "IFormFieldSuite.h"
#include "IListControlDataOf.h"
#include "IPanelControlData.h"
#include "IStringListControlData.h"
#include "ISubject.h"
#include "IUIDData.h"
#include "IViewZoomBehaviorData.h"
#include "IWidgetUtils.h"

// ----- Implementation Includes -----

#include "BehaviorUIDefs.h"
#include "CBehaviorPanelObserver.h"
#include "K2Pair.h"

#include "FormFieldUIUtils.h"
#include "Utils.h"

#include "BehaviorUIID.h"
#include "widgetid.h"

//========================================================================================
// CLASS ViewZoomPanelObserver
//========================================================================================

class ViewZoomPanelObserver : public CBehaviorPanelObserver
{
public:
	ViewZoomPanelObserver(IPMUnknown *boss);
	virtual ~ViewZoomPanelObserver();

	virtual void 	AutoAttach();
	virtual void 	AutoDetach();
	virtual void	InitializeFieldsFromActionData(const IBehaviorData* inActionData);
	virtual bool	ApplyFieldsToActionData(IBehaviorData* inActionData);

protected:
	virtual void HandleSelectionUpdate
		(
		const ClassID&	inBossClassID, 
		ISubject* inSubject, 
		const PMIID& 	inProtocol,
		void* 			inMessage
		);

private:
	void			LoadZoomChoices(IListControlDataOf< K2Pair<PMString, int32> >* viewZoomData);
	void			InitializeZoomChoice(const IBehaviorData *inActionData);

	bool	isAttached;
};

//========================================================================================
// METHODS ViewZoomPanelObserver
//========================================================================================

CREATE_PMINTERFACE(ViewZoomPanelObserver, kViewZoomPanelObserverImpl)

//----------------------------------------------------------------------------------------
// ViewZoomPanelObserver constructor 
//----------------------------------------------------------------------------------------

ViewZoomPanelObserver::ViewZoomPanelObserver(IPMUnknown *boss) :
	CBehaviorPanelObserver(boss),
	isAttached(false)
{
}


//----------------------------------------------------------------------------------------
// ViewZoomPanelObserver::~ViewZoomPanelObserver
//----------------------------------------------------------------------------------------

ViewZoomPanelObserver::~ViewZoomPanelObserver()
{
}

//----------------------------------------------------------------------------------------
// ViewZoomPanelObserver::AutoAttach
//----------------------------------------------------------------------------------------

void ViewZoomPanelObserver::AutoAttach()
{
	if ( ! isAttached ) {
		
		CBehaviorPanelObserver::AutoAttach();
		
		AttachToWidget(kViewZoomWidgetID, IID_ISTRINGLISTCONTROLDATA);
		
		isAttached = true;

#if 0
	InterfacePtr<IControlView> addUpdateButtonView((IControlView *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kAddBehaviorButtonWidgetID, IID_ICONTROLVIEW));
	
	if ( ! addUpdateButtonView->IsEnabled() )
		addUpdateButtonView->Enable();
#endif
	}
}

//----------------------------------------------------------------------------------------
// ViewZoomPanelObserver::AutoDetach
//----------------------------------------------------------------------------------------

void ViewZoomPanelObserver::AutoDetach()
{
	if ( isAttached ) {
		
		CBehaviorPanelObserver::AutoDetach();
		
		DetachFromWidget(kViewZoomWidgetID, IID_ISTRINGLISTCONTROLDATA);
		
		isAttached = false;
	}
}

//----------------------------------------------------------------------------------------
// ViewZoomPanelObserver::HandleSelectionUpdate
//----------------------------------------------------------------------------------------

void ViewZoomPanelObserver::HandleSelectionUpdate
	(
	const ClassID&	inBossClassID, 
	ISubject* inSubject, 
	const PMIID& 	inProtocol,
	void* 			inMessage
	)
{
	InterfacePtr<IFormFieldSuite> iFormSuite( FormFieldUIUtils::QueryFormSuite() );
	
	if ( iFormSuite && !iFormSuite->IsDefaultSelection() && iFormSuite->IsFieldSelection() )
	{
		if ( inProtocol == IID_ISTRINGLISTCONTROLDATA )
		{
			CBehaviorPanelObserver::HandleSelectionUpdate(inBossClassID, inSubject, inProtocol, inMessage);
		}
		else
		{
			InitializeFieldsFromActionData(nil);
		}
		return;
	}

	ActiveSelectionObserver::HandleSelectionUpdate(inBossClassID, inSubject, inProtocol, inMessage);
}

//----------------------------------------------------------------------------------------
// ViewZoomPanelObserver::InitializeFieldsFromActionData
//----------------------------------------------------------------------------------------

void ViewZoomPanelObserver::InitializeFieldsFromActionData(const IBehaviorData* inActionData)
{
	if ( inActionData )
		InitializeZoomChoice(inActionData);
	else
	{
		InterfacePtr<IUIDData> activeBehavior(FormFieldUIUtils::QueryActiveBehavior());
		if ( activeBehavior )
		{
			InterfacePtr<IBehaviorData> iBehaviorData(activeBehavior->GetRef(), UseDefaultIID());
			if ( iBehaviorData )
				InitializeFieldsFromActionData(iBehaviorData);
		}
	}
}

//----------------------------------------------------------------------------------------
// ViewZoomPanelObserver::ApplyFieldsToActionData
//----------------------------------------------------------------------------------------

bool ViewZoomPanelObserver::ApplyFieldsToActionData(IBehaviorData* inActionData)
{
	IViewZoomBehaviorData* actionData = static_cast<IViewZoomBehaviorData*>(inActionData);

//	actionData->SetViewZoom(GetTextControlData(kViewZoomWidgetID));
	InterfacePtr<IDropDownListController> viewZoomChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kViewZoomWidgetID, IID_IDROPDOWNLISTCONTROLLER));
	InterfacePtr< IListControlDataOf< K2Pair<PMString, int32> > > viewZoomData(viewZoomChoice, IID_ILISTCONTROLDATA);
	
	if ( actionData->GetViewZoom() != (IViewZoomBehaviorData::ViewZoom) (*viewZoomData)[viewZoomChoice->GetSelected()].second )
	{
		actionData->SetViewZoom((IViewZoomBehaviorData::ViewZoom) (*viewZoomData)[viewZoomChoice->GetSelected()].second);
		return true;
	}
	else
		return false;
}

//----------------------------------------------------------------------------------------
// ViewZoomPanelObserver::LoadZoomChoices
//----------------------------------------------------------------------------------------

void ViewZoomPanelObserver::LoadZoomChoices(IListControlDataOf< K2Pair<PMString, int32> >* viewZoomData)
{	
	if ( viewZoomData->Length() != 13 )
	{
		viewZoomData->Clear();
		
		viewZoomData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/ViewZoom/Full Screen", IViewZoomBehaviorData::kFullScreen));
		viewZoomData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/ViewZoom/Zoom View In", IViewZoomBehaviorData::kZoomViewIn));
		viewZoomData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/ViewZoom/Zoom View Out", IViewZoomBehaviorData::kZoomViewOut));
		viewZoomData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/ViewZoom/Fit Page", IViewZoomBehaviorData::kFitInWindow));
		viewZoomData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/ViewZoom/Actual Size", IViewZoomBehaviorData::kActualSize));
		viewZoomData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/ViewZoom/Fit Width", IViewZoomBehaviorData::kFitWidth));
		viewZoomData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/ViewZoom/Fit Visible", IViewZoomBehaviorData::kFitVisible));
		viewZoomData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/ViewZoom/SinglePage", IViewZoomBehaviorData::kSinglePage));
		viewZoomData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/ViewZoom/OneColumn", IViewZoomBehaviorData::kContinuous));
		viewZoomData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/ViewZoom/TwoColumns", IViewZoomBehaviorData::kContinuousFacing));
	}
}

//----------------------------------------------------------------------------------------
// ViewZoomPanelObserver::InitializeZoomChoice
//----------------------------------------------------------------------------------------

void ViewZoomPanelObserver::InitializeZoomChoice(const IBehaviorData *inActionData)
{
	InterfacePtr<IDropDownListController> viewZoomChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kViewZoomWidgetID, IID_IDROPDOWNLISTCONTROLLER));
	InterfacePtr< IListControlDataOf< K2Pair<PMString, int32> > > viewZoomData(viewZoomChoice, IID_ILISTCONTROLDATA);
	
	LoadZoomChoices(viewZoomData);
	
	bool bUpdated = false;
	if (inActionData == 0)
	{
		bUpdated = true;
		viewZoomChoice->Select(0, kTrue, kFalse);
	}
	else
	{
		InterfacePtr<IViewZoomBehaviorData> actionData(inActionData, UseDefaultIID());
		for (int32 i = 0; i < viewZoomData->Length(); i++)
			if ((*viewZoomData)[i].second == actionData->GetViewZoom())
			{
				bUpdated = true;
				if ( !viewZoomChoice->IsSelected(i) )
					viewZoomChoice->Select(i, kTrue, kFalse);
				break;
			}
	}

	if ( !bUpdated )
		viewZoomChoice->Deselect(kTrue, kFalse);

	ASSERT(viewZoomChoice->GetSelected() != IDropDownListController::kNoSelection);
}

