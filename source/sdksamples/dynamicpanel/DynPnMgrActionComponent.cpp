//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/dynamicpanel/DynPnMgrActionComponent.cpp $
//  
//  Owner: Adobe Developer Technologies
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

// Interface includes:
#include "IDynPnPanelManager.h"
#include "IActionStateList.h"

// General includes:
#include "CActionComponent.h"
#include "CAlert.h"

// Project includes:
#include "DynPnID.h"


/** Implements IActionComponent; responsible for handling the 'new panel' and 'close panel' menu items
	located on the main plug-ins menu.

	
	@ingroup dynamicpanel
*/
class DynPnMgrActionComponent : public CActionComponent
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		DynPnMgrActionComponent(IPMUnknown* boss);

		/**
			The action component should do the requested action.
			This is where the menu item's action is taken.
			When a menu item is selected, the Menu Manager determines
			which plug-in is responsible for it, and calls its DoAction
			with the ID for the menu item chosen.
	
			@param ac points to the current active context
			@param actionID identifies which action this action component should perform
			@param mousePoint contains the global mouse location at time of event causing action 
			@param widget contains the widget that invoked this action. May be nil. 

			*/
		virtual void DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);
		
		/**
			Called by the framework to allow items to be enabled or disabled. 
			Custom enabling is used because we don't want to enable the close panel
			item to be seen where there is no dynamic panel to close.

			@param ac points to the current active context
  			@param listToUpdate contains the items that client code should update the state for
			@param mousePoint contains the global mouse location at time of event causing action 
			@param widget contains the widget that invoked this action. May be nil. 
		*/
		virtual void UpdateActionStates(IActiveContext* ac, IActionStateList* listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);

	private:
		/** Encapsulates functionality for the NewPanel menu item. */
		void DoNewPanel();
		void DoClosePanel();

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(DynPnMgrActionComponent, kDynPnMgrActionComponentImpl)

/* DynPnMgrActionComponent Constructor
*/
DynPnMgrActionComponent::DynPnMgrActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}

/* DoAction
*/
void DynPnMgrActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{
		case kDynPnMgrNewPanelActionID:
		{
			this->DoNewPanel();
			break;
		}

		case kDynPnMgrClosePanelActionID:
		{
			this->DoClosePanel();
			break;
		}

		default:
		{
			break;
		}
	}
}

/* DoNewPanel
*/
void DynPnMgrActionComponent::DoNewPanel()
{
	do {
		
		InterfacePtr< IDynPnPanelManager> dynPanelManager( IDynPnPanelManager::QueryDynamicPanelManager());
		ASSERT(dynPanelManager);
		if(!dynPanelManager) {
			break;
		}
		int32 dynPanelCount = dynPanelManager->GetPanelsCreatedCount();
		PMString name(kDynPnDynamicPanelNameStart);
		name.AppendNumber(1+dynPanelCount);
		ErrorCode err=dynPanelManager->Create(name);
		ASSERT(err==kSuccess);
	} while(kFalse);

}

void DynPnMgrActionComponent::DoClosePanel()
{
	do {
		
		InterfacePtr< IDynPnPanelManager> dynPanelManager( IDynPnPanelManager::QueryDynamicPanelManager());
		ASSERT(dynPanelManager);
		if(!dynPanelManager) {
			break;
		}
		int32 dynPanelCount = dynPanelManager->GetPanelsCreatedCount();
		if(dynPanelCount <=0 ) {
			break;
		}
		PMString name(kDynPnDynamicPanelNameStart);
		name.AppendNumber(dynPanelCount);
		bool16 isShown = dynPanelManager->IsShowing(name);
		if(isShown) {
			ErrorCode err=dynPanelManager->Destroy(name);
			ASSERT(err==kSuccess);
		}
	} while(kFalse);

}

/* UpdateActionStates
*/
void DynPnMgrActionComponent::UpdateActionStates(IActiveContext* ac, IActionStateList* listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
	do 
	{			
		ASSERT(listToUpdate);
		if(listToUpdate==nil) {
			break;
		}
		
	
		for(int i=0; i < listToUpdate->Length(); i++) 
		{
			ActionID actionID = listToUpdate->GetNthAction(i);
			switch (actionID.Get())
			{
				case kDynPnMgrClosePanelActionID:
				{
					InterfacePtr< IDynPnPanelManager> dynPanelManager( IDynPnPanelManager::QueryDynamicPanelManager());
					ASSERT(dynPanelManager);
					if(!dynPanelManager) {
						break;
					}
					int32 dynPanelCount = dynPanelManager->GetPanelsCreatedCount();				
					bool16 moreThanZeroItems = (dynPanelCount > 0);
									
				
					if(moreThanZeroItems) 
					{
						PMString name(kDynPnDynamicPanelNameStart);
						name.AppendNumber(dynPanelCount);
						bool16 isShown = dynPanelManager->IsShowing(name);
						// If the panel's not currently showing with this name,
						// we can't yet delete it.
						if(isShown) {
							listToUpdate->SetNthActionState(i,kEnabledAction);	
						} else {
							listToUpdate->SetNthActionState(i,kDisabled_Unselected);
						}
					}
					else 
					{
						listToUpdate->SetNthActionState(i,kDisabled_Unselected);
					}
					break;
				}

				default: 
				{
					break;
				}
			} // end switch

		} // end for

	} while(kFalse);
}


//  Generated by Dolly build 17: template "IfPanelMenu".
// End, DynPnMgrActionComponent.cpp.





