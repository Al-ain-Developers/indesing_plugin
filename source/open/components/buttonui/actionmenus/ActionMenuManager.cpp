//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actionmenus/ActionMenuManager.cpp $
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
//========================================================================================

#include "VCPlugInHeaders.h"

#include "IActionMenuManager.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "IBehaviorEvent.h"
#include "IActionMenuService.h"
#include "IBehaviorSuite.h"
#include "IDropDownListController.h"
#include "IControlView.h"
#include "IEventBehaviorData.h"

#include "IListControlDataOf.h"

// ----- Implementation Includes -----

#include "Utils.h"
#include "SelectionUtils.h"
#include "K2Vector.tpp"
#include "CPMUnknown.h"
#include "K2Pair.h"

#include "BehaviorUIID.h"
#include "BehaviorID.h"

#include <map>
#include <algorithm>


//========================================================================================

typedef std::map<ActionEvent, EventMenuInfo> EventListType;
typedef K2Vector<EventMenuInfo> SortedEventListType;

class ActionMenuManager : public CPMUnknown<IActionMenuManager>
{
public:
	ActionMenuManager(IPMUnknown *boss);

	void AddEventMenuItem(ActionEvent inEvent, const PMString& inName, double inOrder);
	void AddEventSeparatorItem(ActionEvent inBeforeEvent, double inOrder);

	void BuildEventMenuSupportingSelection(IDropDownListController* inDropDownList, const ActionEvent& inSelectEvent);

private:
	void AddEvents();
	void AddEventInfo();
	void SortEventInfo();
	
	//NOTE: I may not need fEventMenuItems...
	EventListType 		fEventMenuItems;
	SortedEventListType fSortedEventMenuItems;


	bool fAddedEvents;
	bool fAddedEventInfo;
	bool fSortedEventInfo;
};

//========================================================================================

CREATE_PMINTERFACE(ActionMenuManager, kActionMenuManagerImpl)

//----------------------------------------------------------------------------------------

ActionMenuManager::ActionMenuManager(IPMUnknown *boss) :
	CPMUnknown<IActionMenuManager>(boss), fAddedEvents(false),fAddedEventInfo(false), fSortedEventInfo(false)
{
}

//----------------------------------------------------------------------------------------

void ActionMenuManager::AddEvents()
{
	if (fAddedEvents)
		return;
		
	InterfacePtr<IK2ServiceRegistry> servReg(GetExecutionContextSession(), UseDefaultIID());
		
	int32 eventServiceCount = servReg->GetServiceProviderCount(kBehaviorEventService);

	{
		for(int32 serviceIndex = 0; serviceIndex < eventServiceCount; serviceIndex++)
		{
			InterfacePtr<IK2ServiceProvider> provider(servReg->QueryNthServiceProvider(kBehaviorEventService, serviceIndex));
			InterfacePtr<IBehaviorEvent> eventData(provider, UseDefaultIID());
			
			ActionEvent event =  eventData->GetEvent();

			bool exists =  (fEventMenuItems.find(event) != fEventMenuItems.end());
			ASSERT_MSG(!exists, "That event was already added!");
			if (!exists)
				fEventMenuItems[event] = EventMenuInfo( event, eventData->GetName(), 0.0 /* filled in later...*/, serviceIndex, false /*sep*/ );
		}
	}
	
	 fAddedEvents = true;
}
//----------------------------------------------------------------------------------------

void ActionMenuManager::AddEventInfo()
{
	if (!fAddedEvents)
		AddEvents();
		
	InterfacePtr<IK2ServiceRegistry> servReg(GetExecutionContextSession(), UseDefaultIID());
	int32 actionMenuServiceCount = servReg->GetServiceProviderCount(kActionMenuService);

	{
		for(int32 serviceIndex = 0; serviceIndex < actionMenuServiceCount; serviceIndex++)
		{
			InterfacePtr<IK2ServiceProvider> provider(servReg->QueryNthServiceProvider(kActionMenuService, serviceIndex));
			InterfacePtr<IActionMenuService> actionMenuService(provider, UseDefaultIID());
			
			actionMenuService->AddEventMenuItems(this);
		}
	}
	
	fAddedEventInfo = true;
}

//----------------------------------------------------------------------------------------

class CompOrder
{
public:
	bool operator()( const EventMenuInfo& first, const EventMenuInfo&  second) { return first.fOrder < second.fOrder; }
};

//----------------------------------------------------------------------------------------

void ActionMenuManager::SortEventInfo()
{
	if (!fAddedEventInfo)
		AddEventInfo();
		
	{
		EventListType::iterator iter = fEventMenuItems.begin();

		for(; iter != fEventMenuItems.end(); iter++)
			fSortedEventMenuItems.push_back(iter->second);
	}
	

	std::sort(fSortedEventMenuItems.begin(), fSortedEventMenuItems.end(), CompOrder());

	
	fSortedEventInfo = true;
}

//----------------------------------------------------------------------------------------

void ActionMenuManager::AddEventSeparatorItem(ActionEvent inBeforeEvent, double inOrder)
{
	if (!fAddedEvents)
		AddEvents();

	EventListType::iterator iter = fEventMenuItems.find(inBeforeEvent);
	
	bool exists =  (iter != fEventMenuItems.end());
	
	ASSERT_MSG(exists, "That event wasn't found!");
	if (exists)
		iter->second.fSeparator = true;
}

//----------------------------------------------------------------------------------------

void ActionMenuManager::AddEventMenuItem(ActionEvent inEvent, const PMString& inName, double inOrder)
{
	if (!fAddedEvents)
		AddEvents();

	EventListType::iterator iter = fEventMenuItems.find(inEvent);
	
	bool exists =  (iter != fEventMenuItems.end());
	
	ASSERT_MSG(exists, "That event wasn't found!");
	if (exists)
	{
		ASSERT_MSG( iter->second.fOrder == 0.0, "Event added twice");
		
		iter->second.fOrder = inOrder;
		if (!inName.IsEmpty())
			iter->second.fName = inName; //otherwise use what the event service told us...
	}
}

//----------------------------------------------------------------------------------------

void ActionMenuManager::BuildEventMenuSupportingSelection(IDropDownListController* inDropDownList, const ActionEvent& inSelectEvent)
{
	if (!fSortedEventInfo)
		SortEventInfo();


	InterfacePtr<IBehaviorSuite> actionSuite (SelectionUtils::QuerySuite<IBehaviorSuite>());

	InterfacePtr< IListControlDataOf< K2Pair<PMString, int32> > > listControlData(inDropDownList, IID_ILISTCONTROLDATA);

	InterfacePtr<IControlView> view(inDropDownList, UseDefaultIID());
	InterfacePtr<IK2ServiceRegistry> servReg(GetExecutionContextSession(), UseDefaultIID());

	listControlData->Clear();

	// Add event menu items in sorted order.
	if ( actionSuite )
	{
		SortedEventListType::iterator iter = fSortedEventMenuItems.begin();

		for(; iter != fSortedEventMenuItems.end(); iter++)
		{
			EventMenuInfo& eventInfo = *iter;
			InterfacePtr<IK2ServiceProvider> provider(servReg->QueryNthServiceProvider(kBehaviorEventService, eventInfo.fServiceIndex));
			InterfacePtr<IBehaviorEvent> behaviorEvent(provider, UseDefaultIID());
			if (behaviorEvent && actionSuite->IsEventSupported(behaviorEvent))
			{
				if (eventInfo.fSeparator)
					listControlData->Add(K2Pair<PMString, int32>("-", kNoEvt));

				listControlData->Add(K2Pair<PMString, int32>(behaviorEvent->GetName(), behaviorEvent->GetEvent()));
			}
		}

	}

	// Select the default item...

	InterfacePtr<IEventBehaviorData> defaults(GetExecutionContextSession(), UseDefaultIID());

	inDropDownList->Deselect();
	
	if (inSelectEvent == 0)  //When adding, event should be zero
	{
		if ( listControlData->Length() <= 1 )
			view->Disable(); 
		else
		{
			view->Enable();
			inDropDownList->Select(defaults->GetEvent());
		}
	}
	else
	{
		for (int32 i = 0; i < listControlData->Length(); i++)  //When editing, should be supported event
			if ((*listControlData)[i].second == inSelectEvent)
			{
				inDropDownList->Select(i);
				break;
			}
		
		view->Disable(); //don't allow event change when editing existing event
	}
	
	//ASSERT(inDropDownList->GetSelected() != IDropDownListController::kNoSelection);
}
