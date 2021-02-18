//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionTagEyeballObserver.cpp $
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
#include "IConditionTagList.h"
#include "ISubject.h"
#include "ITreeNodeIDData.h"
#include "ITriStateControlData.h"
#include "IWidgetParent.h"
#include "IWorkspace.h"

// ----- Includes -----

#include "CObserver.h"
#include "UIDNodeID.h"

// ----- Utility files -----

#include "IConditionalTextFacade.h"
#include "IEventUtils.h"

// ----- ID.h files -----

#include "ConditionalTextUIID.h"


class ConditionTagEyeballObserver : public CObserver
{
public:
	ConditionTagEyeballObserver(IPMUnknown *boss);
	virtual ~ConditionTagEyeballObserver();
		
	virtual void AutoAttach();
	virtual void AutoDetach();
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
};

// =============================================================================
// *** ConditionTagEyeballObserver impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(ConditionTagEyeballObserver, kConditionTagEyeballObserverImpl)

ConditionTagEyeballObserver::ConditionTagEyeballObserver(IPMUnknown *boss) :
	CObserver(boss)
{
} // end constructor

ConditionTagEyeballObserver::~ConditionTagEyeballObserver()
{
} // end desctructor

// -----------------------------------------------------------------------------

void ConditionTagEyeballObserver::AutoAttach()
{
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
		subject->AttachObserver(this, IID_ITRISTATECONTROLDATA);
} // end AutoAttach()

// -----------------------------------------------------------------------------

void ConditionTagEyeballObserver::AutoDetach()
{
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
		subject->DetachObserver(this, IID_ITRISTATECONTROLDATA);
} // end AutoDetach()

// -----------------------------------------------------------------------------

void ConditionTagEyeballObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	if (theChange == kTrueStateMessage || theChange == kFalseStateMessage)
	{
		InterfacePtr<ITriStateControlData> data(this, IID_ITRISTATECONTROLDATA);
		if (data)
		{
			InterfacePtr<IWidgetParent> eyeballWidget(this, UseDefaultIID());
			InterfacePtr<ITreeNodeIDData> nodeData((ITreeNodeIDData*)eyeballWidget->QueryParentFor(IID_ITREENODEIDDATA));
			TreeNodePtr<UIDNodeID> node(nodeData->Get());
			IActiveContext* context = GetExecutionContextSession()->GetActiveContext();
			IWorkspace* workspace = context->GetContextWorkspace();

			InterfacePtr<IConditionTag> tag(::GetDataBase(workspace), node->GetUID(), UseDefaultIID());
			bool16 bNewVisibility = !tag->IsVisible();

			// Do the Alt/Opt+Click behavior as described: hide all other conditions or if all other
			// conditions are hidden then show them.
			Utils<Facade::IConditionalTextFacade> ctFacade;
			if (::IsOptionAltKeyPressed())
			{
				InterfacePtr<IConditionTagList> tags(workspace, UseDefaultIID());
				if (tags && tags->GetCount() > 1)
				{
					bool16 allOthersHidden(kTrue);
					for (int32 i=0; i < tags->GetCount(); i++)
					{
						if (tags->GetNthCondition(i) != node->GetUID())
						{
							InterfacePtr<IConditionTag> otherTag(::GetDataBase(workspace), tags->GetNthCondition(i), UseDefaultIID());
							if (otherTag && otherTag->IsVisible())
							{
								allOthersHidden = kFalse;
								break;
							}
						}
					}

					if (allOthersHidden)
						ctFacade->ShowAllConditions(workspace, kTrue);
					else
						ctFacade->ShowAllConditions(workspace, kFalse);
				}
			}

			// Toggle this condition's visibility.
			ctFacade->SetConditionVisibleState(::GetUIDRef(tag), bNewVisibility);
		}
	}
} // end Update()

