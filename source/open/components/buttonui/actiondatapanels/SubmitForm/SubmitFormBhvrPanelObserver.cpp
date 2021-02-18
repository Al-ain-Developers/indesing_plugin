//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/SubmitForm/SubmitFormBhvrPanelObserver.cpp $
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
#include "IFormFieldSuite.h"
#include "ISubject.h"
#include "ISubmitFormBehaviorData.h"
#include "IUIDData.h"
#include "IWidgetUtils.h"

// ----- Implementation Includes -----

#include "BehaviorUIDefs.h"
#include "BehaviorUIID.h"
#include "CBehaviorPanelObserver.h"
#include "ErrorUtils.h"
#include "FormFieldUIUtils.h"
#include "Utils.h"
#include "widgetid.h"

//========================================================================================
// CLASS SubmitFormBhvrPanelObserver
//========================================================================================

class SubmitFormBhvrPanelObserver : public CBehaviorPanelObserver
{
public:
	SubmitFormBhvrPanelObserver(IPMUnknown *boss);
	virtual ~SubmitFormBhvrPanelObserver();

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
	bool	isAttached;
};

//========================================================================================
// METHODS SubmitFormBhvrPanelObserver
//========================================================================================

CREATE_PMINTERFACE(SubmitFormBhvrPanelObserver, kSubmitFormBehaviorPanelObserverImpl)

//----------------------------------------------------------------------------------------
// SubmitFormBhvrPanelObserver constructor 
//----------------------------------------------------------------------------------------

SubmitFormBhvrPanelObserver::SubmitFormBhvrPanelObserver(IPMUnknown *boss) :
	CBehaviorPanelObserver(boss),
	isAttached(false)
{
}


//----------------------------------------------------------------------------------------
// SubmitFormBhvrPanelObserver::~SubmitFormBhvrPanelObserver
//----------------------------------------------------------------------------------------

SubmitFormBhvrPanelObserver::~SubmitFormBhvrPanelObserver()
{
}

//----------------------------------------------------------------------------------------
// SubmitFormBhvrPanelObserver::AutoAttach
//----------------------------------------------------------------------------------------

void SubmitFormBhvrPanelObserver::AutoAttach()
{
	if ( ! isAttached ) {
		
		CBehaviorPanelObserver::AutoAttach();
		
		AttachToWidget(kSelectFileWidgetID, IID_ITEXTCONTROLDATA);
		
		isAttached = true;

#if 0
		InterfacePtr<IControlView> addUpdateButtonView((IControlView *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kAddBehaviorButtonWidgetID, IID_ICONTROLVIEW));
		
		if ( ! addUpdateButtonView->IsEnabled() )
			addUpdateButtonView->Enable();
#endif
	}
}

//----------------------------------------------------------------------------------------
// SubmitFormBhvrPanelObserver::AutoDetach
//----------------------------------------------------------------------------------------

void SubmitFormBhvrPanelObserver::AutoDetach()
{
	if ( isAttached ) {
		
		CBehaviorPanelObserver::AutoDetach();
		
		DetachFromWidget(kSelectFileWidgetID, IID_ITEXTCONTROLDATA);
		
		isAttached = false;
	}
}

//----------------------------------------------------------------------------------------
// SubmitFormBhvrPanelObserver::HandleSelectionUpdate
//----------------------------------------------------------------------------------------

void SubmitFormBhvrPanelObserver::HandleSelectionUpdate
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
		if ( inProtocol == IID_ITEXTCONTROLDATA )
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
// SubmitFormBhvrPanelObserver::InitializeFieldsFromActionData
//----------------------------------------------------------------------------------------

void SubmitFormBhvrPanelObserver::InitializeFieldsFromActionData(const IBehaviorData* inActionData)
{
	if (inActionData == 0)
	{
		InterfacePtr<IUIDData const> activeBehavior(FormFieldUIUtils::QueryActiveBehavior());
		
		if (activeBehavior)
		{
			InterfacePtr<ISubmitFormBehaviorData> behaviorData(activeBehavior->GetRef(), UseDefaultIID());
			if(behaviorData)	
				SetTextControlData(kSelectFileWidgetID, behaviorData->GetURL(), nil, kTrue, kFalse);
		}
	}
	else
	{
		InterfacePtr<ISubmitFormBehaviorData> behaviorData(inActionData, UseDefaultIID());
		if(behaviorData)	
			SetTextControlData(kSelectFileWidgetID, behaviorData->GetURL(), nil, kTrue, kFalse);
	}
}

//----------------------------------------------------------------------------------------
// SubmitFormBhvrPanelObserver::InitializeFieldsFromActionData
//----------------------------------------------------------------------------------------

bool SubmitFormBhvrPanelObserver::ApplyFieldsToActionData(IBehaviorData* inActionData)
{
	ISubmitFormBehaviorData* behaviorData = static_cast<ISubmitFormBehaviorData*>(inActionData);

	if ( behaviorData->GetURL() != GetTextControlData(kSelectFileWidgetID) )
	{
		behaviorData->SetURL(GetTextControlData(kSelectFileWidgetID));
		return true;
	}
	return false;
}
