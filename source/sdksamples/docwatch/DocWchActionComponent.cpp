//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/docwatch/DocWchActionComponent.cpp $
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

// General includes:
#include "CAlert.h"
#include "CActionComponent.h"
#include "IActionStateList.h" // this is not based on IPMUnknown

// Project includes:
#include "DocWchUtils.h"
#include "DocWchID.h"


/** DocWchActionComponent
	implements the actions that are executed when the plug-in's
	menu items are selected.

	DocWchActionComponent implements IActionComponent based on
	the partial implementation CActionComponent.

	@ingroup docwatch
	
*/
class DocWchActionComponent : public CActionComponent
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		DocWchActionComponent(IPMUnknown* boss);

		/**
			The action component is where the menu item's action is taken.
			When a menu item is selected, the Menu Manager determines
			which plug-in is responsible for it, and calls its DoAction
			with the ID for the menu item chosen.

			@param ac IN Specifies active context -- active selection, active view, active doc, etc.
			@param actionID IN Identifies the menu item that was selected.
			@param mousePoint IN Contains the global mouse location at time of event-causing action (e.g. context menus). kInvalidMousePoint if not relevant.
			@param widget IN Contains the widget that invoked this action. May be nil. e.g. Useful to use as a basis for Utils<IWidgetUtils>()->QueryRelatedWidget(...) to find widgets in a panel after its popup menu is hit.
		*/
		void DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);
		
		/** 
			The action component is asked to update a list of actions to the proper state.
			the list of actions is intially disabled and unselected, so it only has to be
			changed if this state is not correct. Note that action components are never asked to update
			actions that don't belong to them, or actions they have not specified kCustomEnabling for.
			
			@param ac IN Specifies active context -- active selection, active view, active doc, etc.
			@param listToUpdate IN contains the items that client code	should update the state for
			@param mousePoint IN contains the global mouse location at time of event causing action (e.g. context menus). kInvalidMousePoint if not known or relevant.
			@param widget IN contains the widget that invoked this action. May be nil. e.g. Useful to use as a basis for Utils<IWidgetUtils>()->QueryRelatedWidget(...) to find widgets in a panel after its popup menu is hit.
		*/
		virtual void UpdateActionStates(IActiveContext* ac, IActionStateList* listToUpdate, GSysPoint mousePoint = kInvalidMousePoint, IPMUnknown* widget = nil);


	private:
		/** Encapsulates functionality for the about menu item. */
		void DoAbout();

		/** Encapsulates functionality for the UseResponder menu item. */
		void DoUseResponder();

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(DocWchActionComponent, kDocWchActionComponentImpl)

/* DocWchActionComponent Constructor
*/
DocWchActionComponent::DocWchActionComponent(IPMUnknown* boss)
	: CActionComponent(boss)
{
}

/* DoAction
*/
void DocWchActionComponent::DoAction(IActiveContext* ac, 
									 ActionID actionID, 
									 GSysPoint mousePoint, 
									 IPMUnknown* widget)
{
	switch (actionID.Get())
	{
		case kDocWchAboutActionID:
		{
			this->DoAbout();
			break;
		}

		case kDocWchUseResponderActionID:
		{
			this->DoUseResponder();
			break;
		}

		default:
		{
			break;
		}
	}
}

/* UpdateActionStates
*/
void DocWchActionComponent::UpdateActionStates(IActiveContext* ac, 
											   IActionStateList* listToUpdate, 
											   GSysPoint mousePoint, 
											   IPMUnknown* widget)
{
	do
    {
		// the Use Responder menu item is always enabled
		int16 actionState = kEnabledAction;

		// see if the DocWatch responder is currently in use 
		if (DocWchUtils::QueryDocResponderMode() == kTrue) 
		{
			// Yes, it is - add a check mark
			actionState |= kSelectedAction;
		}

        for (int32 i = 0; i < listToUpdate->Length(); i++)
        {
            if (listToUpdate->GetNthAction(i) == kDocWchUseResponderActionID)
			{
				listToUpdate->SetNthActionState(i, actionState);
			}
        }
    } while (kFalse);
}

/* DoAbout
*/
void DocWchActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
	   kDocWchAboutBoxStringKey,		// Alert string
	   kOKString, 						// OK button
	   kNullString, 					// No second button
	   kNullString, 					// No third button
	   1,								// Set OK button to default
	   CAlert::eInformationIcon		// Information icon.
	);
}

/* DoUseResponder
*/
void DocWchActionComponent::DoUseResponder()
{
	if (DocWchUtils::QueryDocResponderMode())
	{
		DocWchUtils::StopDocResponderMode();
	}
	else
	{
		DocWchUtils::StartDocResponderMode();
	}
}

// End, DocWchActionComponent.cpp.


