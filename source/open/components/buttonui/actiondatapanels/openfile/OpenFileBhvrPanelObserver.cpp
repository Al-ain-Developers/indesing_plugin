//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/openfile/OpenFileBhvrPanelObserver.cpp $
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
#include "IOpenFileBehaviorData.h"
#include "ISubject.h"
#include "IUIDData.h"
#include "IWidgetUtils.h"


// ----- Implementation Includes -----

#include "CBehaviorPanelObserver.h"

#include "ErrorUtils.h"
#include "FormFieldUIUtils.h"
#include "Utils.h"
#include "widgetid.h"

#include "BehaviorUIID.h"
#include "BehaviorUIDefs.h"

//========================================================================================
// CLASS OpenFileBhvrPanelObserver
//========================================================================================

class OpenFileBhvrPanelObserver : public CBehaviorPanelObserver
{
public:
	OpenFileBhvrPanelObserver(IPMUnknown *boss);
	virtual ~OpenFileBhvrPanelObserver();

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
// METHODS OpenFileBhvrPanelObserver
//========================================================================================

CREATE_PMINTERFACE(OpenFileBhvrPanelObserver, kOpenFileBehaviorPanelObserverImpl)

//----------------------------------------------------------------------------------------
// OpenFileBhvrPanelObserver constructor 
//----------------------------------------------------------------------------------------

OpenFileBhvrPanelObserver::OpenFileBhvrPanelObserver(IPMUnknown *boss) :
	CBehaviorPanelObserver(boss),
	isAttached(false)
{
}


//----------------------------------------------------------------------------------------
// OpenFileBhvrPanelObserver::~OpenFileBhvrPanelObserver
//----------------------------------------------------------------------------------------

OpenFileBhvrPanelObserver::~OpenFileBhvrPanelObserver()
{
}

//----------------------------------------------------------------------------------------
// OpenFileBhvrPanelObserver::AutoAttach
//----------------------------------------------------------------------------------------

void OpenFileBhvrPanelObserver::AutoAttach()
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
// OpenFileBhvrPanelObserver::AutoDetach
//----------------------------------------------------------------------------------------

void OpenFileBhvrPanelObserver::AutoDetach()
{
	if ( isAttached ) {
		
		CBehaviorPanelObserver::AutoDetach();
		
		DetachFromWidget(kSelectFileWidgetID, IID_ITEXTCONTROLDATA);
		
		isAttached = false;
	}
}

//----------------------------------------------------------------------------------------
// OpenFileBhvrPanelObserver::HandleSelectionUpdate
//----------------------------------------------------------------------------------------

void OpenFileBhvrPanelObserver::HandleSelectionUpdate
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
// OpenFileBhvrPanelObserver::InitializeFieldsFromActionData
//----------------------------------------------------------------------------------------

void OpenFileBhvrPanelObserver::InitializeFieldsFromActionData(const IBehaviorData* inActionData)
{
	if (inActionData == 0)
	{
		InterfacePtr<IUIDData const> activeBehavior(FormFieldUIUtils::QueryActiveBehavior());
		
		if (activeBehavior)
		{
			InterfacePtr<IOpenFileBehaviorData> behaviorData(activeBehavior->GetRef(), UseDefaultIID());
			if(behaviorData)
				SetTextControlData(kSelectFileWidgetID, behaviorData->GetFileName(), nil, kTrue, kFalse);
		}
	}
	else
	{
		InterfacePtr<IOpenFileBehaviorData> behaviorData(inActionData, UseDefaultIID());
		if(behaviorData)
			SetTextControlData(kSelectFileWidgetID, behaviorData->GetFileName(), nil, kTrue, kFalse);
	}
}

//----------------------------------------------------------------------------------------
// OpenFileBhvrPanelObserver::InitializeFieldsFromActionData
//----------------------------------------------------------------------------------------

bool OpenFileBhvrPanelObserver::ApplyFieldsToActionData(IBehaviorData* inActionData)
{
	IOpenFileBehaviorData* behaviorData = static_cast<IOpenFileBehaviorData*>(inActionData);

	if ( behaviorData->GetFileName() != GetTextControlData(kSelectFileWidgetID) )
	{
		behaviorData->SetFileName(GetTextControlData(kSelectFileWidgetID));
		return true;
	}
	return false;
}
