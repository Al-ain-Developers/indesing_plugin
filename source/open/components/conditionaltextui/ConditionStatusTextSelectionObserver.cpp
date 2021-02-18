//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionStatusTextSelectionObserver.cpp $
//  
//  Owner: Kevin Van Wiel
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
#include "ITextControlData.h"
#include "IActiveContext.h"
#include "ISelectionManager.h"
#include "IConditionTagSuite.h"
#include "IConditionTagList.h"

// ----- Includes -----
#include "SelectionObserver.h"
#include "UIDList.h"

// ----- Utility files -----
#include "IConditionalTextFacade.h"
#include "StringUtils.h"

// ----- ID.h files -----
#include "ConditionalTextUIID.h"
#include "ConditionalTextID.h"

using namespace Facade;
/******************************************************************************
 * class ConditionStatusTextSelectionObserver
 ******************************************************************************/
class ConditionStatusTextSelectionObserver : public ActiveSelectionObserver
{
public:
	ConditionStatusTextSelectionObserver(IPMUnknown *boss);

	virtual void HandleSelectionChanged( const ISelectionMessage* iSelectionMessage );
	virtual void HandleSelectionAttributeChanged( const ISelectionMessage* iSelectionMessage );
	
private:
	void UpdateStatus();
};

CREATE_PMINTERFACE(ConditionStatusTextSelectionObserver, kConditionStatusTextSelectionObserverImpl)

/******************************************************************************
 * ConditionStatusTextSelectionObserver::ConditionStatusTextSelectionObserver
 ******************************************************************************/
ConditionStatusTextSelectionObserver::ConditionStatusTextSelectionObserver(IPMUnknown *boss) :
	ActiveSelectionObserver(boss, IID_ISELECTIONOBSERVER)
{
	
}

/******************************************************************************
 * ConditionStatusTextSelectionObserver::HandleSelectionChanged
 ******************************************************************************/
void ConditionStatusTextSelectionObserver::HandleSelectionChanged(const ISelectionMessage* iSelectionMessage)
{
#pragma unused(iSelectionMessage)
	UpdateStatus();
}

/******************************************************************************
 * ConditionStatusTextSelectionObserver::HandleSelectionAttributeChanged
 ******************************************************************************/
void ConditionStatusTextSelectionObserver::HandleSelectionAttributeChanged(const ISelectionMessage* iSelectionMessage)
{
#pragma unused(iSelectionMessage)
	UpdateStatus();
}

/******************************************************************************
 * ConditionStatusTextSelectionObserver::HandleSelectionAttributeChanged
 ******************************************************************************/
void ConditionStatusTextSelectionObserver::UpdateStatus()
{
	PMString statusString("");
	statusString.Translate();
	
	IActiveContext* ac = GetExecutionContextSession()->GetActiveContext();
	InterfacePtr<IConditionTagList> conditionTagList(Utils<Facade::IConditionalTextFacade>()->QueryActiveConditionList(ac));
	if (conditionTagList && conditionTagList->GetCount() > 0)
	{
		ISelectionManager* selMgr = ac->GetContextSelection();
		InterfacePtr<IConditionTagSuite> conditionsSuite(static_cast<IConditionTagSuite*>(selMgr->QueryIntegratorSuite(IID_ICONDITIONTAGSUITE, ISelectionManager::kEnabledInterface)));
		if (conditionsSuite)
		{
			UIDList appliedToAllChars;
			UIDList appliedToSomeChars;
			if (conditionsSuite->GetAppliedConditionTags(appliedToAllChars, appliedToSomeChars) == kSuccess)
			{
				int32 numberApplied = appliedToAllChars.size() + appliedToSomeChars.size();
				if (numberApplied > 0)
				{
					PMString numberString;
					numberString.SetTranslatable(kFalse);
					numberString.AppendNumber(numberApplied);
					
					PMString bodyString;
					if (numberApplied == 1)
					{
						bodyString = PMString("#SingularConditionStatusBodyString");
						bodyString.Translate();
					}
					else
					{
						bodyString = PMString("#PluralConditionStatusBodyString");
						bodyString.Translate();
					}
					
					PMString mixedStateString(" ");
					mixedStateString.SetTranslatable(kFalse);
					if (appliedToSomeChars.size() > 0)
					{
						mixedStateString = PMString("#MixedConditionString");
						mixedStateString.Translate();
					}
					
					::ReplaceStringParameters(&bodyString, numberString, mixedStateString);
					statusString = bodyString;
					statusString.SetTranslatable(kFalse);
				}
				else
				{
					statusString = PMString("#NoConditionsString");
				}
			}
		}
	}
	
	// Update string if it has changed.
	InterfacePtr<ITextControlData> controlData(this, UseDefaultIID());
	if (statusString != controlData->GetString())
		controlData->SetString(statusString);
}
