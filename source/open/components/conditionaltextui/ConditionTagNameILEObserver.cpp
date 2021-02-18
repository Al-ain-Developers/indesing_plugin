//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionTagNameILEObserver.cpp $
//  
//  Owner: Michele Stutzman
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

#include "IActiveContext.h"
#include "IConditionTag.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "ITreeNodeIDData.h"
#include "IWidgetParent.h"
#include "IWorkspace.h"

// ----- Includes -----

#include "InLineEditObserver.h"
#include "UIDNodeID.h"

// ----- Utility files -----

#include "IConditionalTextFacade.h"

// ----- ID.h files -----

#include "ConditionalTextUIID.h"


class ConditionTagNameILEObserver : public InLineEditObserver
{
public:
	ConditionTagNameILEObserver(IPMUnknown *boss);
	virtual ~ConditionTagNameILEObserver();
		
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);		
	virtual void AutoAttach();			
	virtual void AutoDetach();
};

// =============================================================================
// *** ConditionTagNameILEObserver impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(ConditionTagNameILEObserver, kConditionTagNameILEObserverImpl)

ConditionTagNameILEObserver::ConditionTagNameILEObserver(IPMUnknown *boss) :
	InLineEditObserver(boss)
{
} // end constructor

ConditionTagNameILEObserver::~ConditionTagNameILEObserver()
{
} // end destructor

// -----------------------------------------------------------------------------

void ConditionTagNameILEObserver::AutoAttach()
{
	InLineEditObserver::AutoAttach();

	InterfacePtr<ISubject> subjectList( this, IID_ISUBJECT );
	if (subjectList)
		subjectList->AttachObserver(this, IID_ITEXTCONTROLDATA); 
} // end AutoAttach()

// -----------------------------------------------------------------------------

void ConditionTagNameILEObserver::AutoDetach()
{
	InterfacePtr<ISubject> subjectList( this, IID_ISUBJECT );
	if (subjectList)
		subjectList->DetachObserver(this, IID_ITEXTCONTROLDATA);

	InLineEditObserver::AutoDetach();
} // end AutoDetach()

// -----------------------------------------------------------------------------

void ConditionTagNameILEObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	if (protocol == IID_ITEXTCONTROLDATA && theChange == kTextChangeStateMessage)
	{
		InterfacePtr<IWidgetParent> inLineEditWidget(this, UseDefaultIID());
		InterfacePtr<IWidgetParent> treeNodeWidget(inLineEditWidget->GetParent(), UseDefaultIID());

		InterfacePtr<ITreeNodeIDData> data(treeNodeWidget, UseDefaultIID());
		TreeNodePtr<UIDNodeID> node(data->Get());

		InterfacePtr<ITextControlData>	textData(theSubject, UseDefaultIID());
		WideString wTextData(textData->GetString());

		IActiveContext* context = GetExecutionContextSession()->GetActiveContext();
		IWorkspace* workspace = context->GetContextWorkspace();

		InterfacePtr<IConditionTag> tag(::GetDataBase(workspace), node->GetUID(), UseDefaultIID());
		if (tag && tag->GetName() != wTextData)
			Utils<Facade::IConditionalTextFacade>()->SetConditionName(::GetUIDRef(tag), wTextData);
	}

	InLineEditObserver::Update(theChange, theSubject, protocol, changedBy);
} // end Update()
