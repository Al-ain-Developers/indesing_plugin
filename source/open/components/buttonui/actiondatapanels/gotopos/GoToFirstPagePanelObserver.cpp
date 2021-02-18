//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/gotopos/GoToFirstPagePanelObserver.cpp $
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

#include "IActiveContext.h"
#include "IBehaviorData.h"
#include "IControlView.h"
#include "IDocument.h"
#include "IDropDownListController.h"
#include "IFormFieldSuite.h"
#include "IGoToPositionBehaviorData.h"
#include "IListControlDataOf.h"
#include "IPageList.h"
#include "IPanelControlData.h"
#include "ISession.h"
#include "IStringListControlData.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "ITextDataValidation.h"
#include "ITextValue.h"
#include "IUIDData.h"
#include "IWidgetUtils.h"


// ----- Implementation Includes -----

#include "CBehaviorPanelObserver.h"
#include "K2Pair.h"

#include "BehaviorUIID.h"
#include "BehaviorUIDefs.h"

#include "ErrorUtils.h"
#include "FormFieldUIUtils.h"
#include "Utils.h"
#include "widgetid.h"

//========================================================================================
// CLASS GoToFirstPagePanelObserver
//========================================================================================

class GoToFirstPagePanelObserver : public CBehaviorPanelObserver
{
public:
	GoToFirstPagePanelObserver(IPMUnknown *boss);
	virtual ~GoToFirstPagePanelObserver();

	virtual void 	AutoAttach();
	virtual void 	AutoDetach();

protected:
	virtual void HandleSelectionUpdate
		(
		const ClassID&	inBossClassID, 
		ISubject* inSubject, 
		const PMIID& 	inProtocol,
		void* 			inMessage
		);
	virtual void	InitializeFieldsFromActionData(const IBehaviorData* inActionData);
	virtual bool	ApplyFieldsToActionData(IBehaviorData* inActionData);

private:
	void			LoadZoomChoices(IListControlDataOf< K2Pair<PMString, int32> >* movieOpData) const;
	void			InitializeZoomChoice(const IBehaviorData *inActionData) const;

	bool	isAttached;
};

//========================================================================================
// METHODS GoToFirstPagePanelObserver
//========================================================================================

CREATE_PMINTERFACE(GoToFirstPagePanelObserver, kGoToFirstPagePanelObserverImpl)

//----------------------------------------------------------------------------------------
// GoToFirstPagePanelObserver constructor 
//----------------------------------------------------------------------------------------

GoToFirstPagePanelObserver::GoToFirstPagePanelObserver(IPMUnknown *boss) :
	CBehaviorPanelObserver(boss),
	isAttached(false)
{
}


//----------------------------------------------------------------------------------------
// GoToFirstPagePanelObserver::~GoToFirstPagePanelObserver
//----------------------------------------------------------------------------------------

GoToFirstPagePanelObserver::~GoToFirstPagePanelObserver()
{
}

//----------------------------------------------------------------------------------------
// GoToFirstPagePanelObserver::AutoAttach
//----------------------------------------------------------------------------------------

void GoToFirstPagePanelObserver::AutoAttach()
{
	if ( ! isAttached ) {
		
		CBehaviorPanelObserver::AutoAttach();
		
		AttachToWidget(kZoomWidgetID, IID_ISTRINGLISTCONTROLDATA);
		
		isAttached = true;
	}
}

//----------------------------------------------------------------------------------------
// GoToFirstPagePanelObserver::AutoDetach
//----------------------------------------------------------------------------------------

void GoToFirstPagePanelObserver::AutoDetach()
{
	if ( isAttached ) {
		
		CBehaviorPanelObserver::AutoDetach();
		
		DetachFromWidget(kZoomWidgetID, IID_ISTRINGLISTCONTROLDATA);
		
		isAttached = false;
	}
}

//----------------------------------------------------------------------------------------
// GoToFirstPagePanelObserver::HandleSelectionUpdate
//----------------------------------------------------------------------------------------

void GoToFirstPagePanelObserver::HandleSelectionUpdate
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
// GoToFirstPagePanelObserver::InitializeFieldsFromActionData
//----------------------------------------------------------------------------------------

void GoToFirstPagePanelObserver::InitializeFieldsFromActionData(const IBehaviorData* inActionData)
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
// GoToFirstPagePanelObserver::InitializeFieldsFromActionData
//----------------------------------------------------------------------------------------

bool GoToFirstPagePanelObserver::ApplyFieldsToActionData(IBehaviorData* inActionData)
{
	IGoToPositionBehaviorData* actionData = static_cast<IGoToPositionBehaviorData*>(inActionData);

	InterfacePtr<IDropDownListController> zoomChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kZoomWidgetID, IID_IDROPDOWNLISTCONTROLLER));
	InterfacePtr< IListControlDataOf< K2Pair<PMString, int32> > > zoomData(zoomChoice, IID_ILISTCONTROLDATA);
	if ( actionData->GetZoom() != (IGoToPositionBehaviorData::Zoom) (*zoomData)[zoomChoice->GetSelected()].second)
	{
		actionData->SetZoom((IGoToPositionBehaviorData::Zoom) (*zoomData)[zoomChoice->GetSelected()].second);
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------------------
// GoToFirstPagePanelObserver::LoadZoomChoices
//----------------------------------------------------------------------------------------

void GoToFirstPagePanelObserver::LoadZoomChoices(IListControlDataOf< K2Pair<PMString, int32> >* gotoData) const
{	
	if ( gotoData->Length() != 5 )
	{
		gotoData->Clear();
		gotoData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/GoToView/Inherit Zoom", IGoToPositionBehaviorData::kInherit));
		gotoData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/GoToView/Actual Size", IGoToPositionBehaviorData::kActualSize));
		gotoData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/GoToView/Fit In Window", IGoToPositionBehaviorData::kFitInWindow));
		gotoData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/GoToView/Fit Width", IGoToPositionBehaviorData::kFitWidth));
		gotoData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/GoToView/Fit Visible", IGoToPositionBehaviorData::kFitVisible));
	}
}

//----------------------------------------------------------------------------------------
// GoToFirstPagePanelObserver::InitializeZoomChoice
//----------------------------------------------------------------------------------------

void GoToFirstPagePanelObserver::InitializeZoomChoice(const IBehaviorData *inActionData) const
{
	InterfacePtr<IDropDownListController> zoomChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kZoomWidgetID, IID_IDROPDOWNLISTCONTROLLER));
	InterfacePtr< IListControlDataOf< K2Pair<PMString, int32> > > zoomData(zoomChoice, IID_ILISTCONTROLDATA);
	
	LoadZoomChoices(zoomData);
	
	//zoomChoice->Deselect(kTrue, kFalse);
	
	if (inActionData == 0)
		zoomChoice->Select(0, kTrue, kFalse);
	else
	{
		InterfacePtr<IGoToPositionBehaviorData> actionData(inActionData, UseDefaultIID());
		bool bFound = false;
		for (int32 i = 0; i < zoomData->Length(); i++)
			if ((*zoomData)[i].second == actionData->GetZoom())
			{
				bFound = true;
				if ( !zoomChoice->IsSelected(i) )
					zoomChoice->Select(i, kTrue, kFalse);
				break;
			}

		if ( !bFound )
			zoomChoice->Deselect(kTrue, kFalse);
	}

	ASSERT(zoomChoice->GetSelected() != IDropDownListController::kNoSelection);
}
