//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicmenu/BscMnuActionComponent.cpp $
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
#include "IActiveContext.h"
#include "ISelectionManager.h"

// General includes:
#include "CActionComponent.h"
#include "IActionStateList.h"
#include "CAlert.h"
#include "Utils.h"

// Project includes:
#include "BscMnuID.h"
#include "IBscMnuSuite.h"


/** BscMnuActionComponent
	implements the actions that are executed when the plug-in's
	menu items are selected.

	BscMnuActionComponent implements IActionComponent based on
	the partial implementation CActionComponent.

	@ingroup basicmenu
	
*/
class BscMnuActionComponent : public CActionComponent
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		BscMnuActionComponent(IPMUnknown* boss);

		/**
			The action component should perform the requested action.
			This is where the menu item's action is taken.
			When a menu item is selected, the application framework determines
			which plug-in is responsible for it, and calls its DoAction
			with the ID for the menu item chosen.

			@param actionID identifies the menu item that was selected.
			@see CActionComponent::DoAction
		*/
		void DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint = kInvalidMousePoint, IPMUnknown* widget = nil);

		/**
			Called to determine if an action should be enabled.
			This call enables the action that pops this
			plug-in's dialog.
			@see CActionComponent::UpdateActionStates
		*/
		void UpdateActionStates(IActiveContext* ac, IActionStateList* listToUpdate, GSysPoint mousePoint = kInvalidMousePoint, IPMUnknown* widget = nil);

	private:
		/** Encapsulates functionality for the about menu item. */
		void DoAbout();

		/** Encapsulates functionality for the AlwaysOn menu item. */
		void DoAlwaysOn();

		/** Encapsulates functionality for the OnIfFrontDoc menu item. */
		void DoOnIfFrontDoc();

		/** Encapsulates functionality for the NeedsSelection menu item. */
		void DoNeedsSelection();

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(BscMnuActionComponent, kBscMnuActionComponentImpl)

/* BscMnuActionComponent Constructor
*/
BscMnuActionComponent::BscMnuActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}

/*
*/
void BscMnuActionComponent::UpdateActionStates(IActiveContext* ac, IActionStateList* listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
	if (ac == nil)
	{
		ASSERT(ac);
		return;
	}

	for(int32 iter = 0; iter < listToUpdate->Length(); iter++) 
	{
		ActionID actionID = listToUpdate->GetNthAction(iter);
		if (actionID.Get() == kBscMnuNeedsSelectionActionID) 
		{
			InterfacePtr<IBscMnuSuite> bscmnuSuite(ac->GetContextSelection(), UseDefaultIID());
			if (bscmnuSuite != nil && bscmnuSuite->CanApplyBscMnu() == kTrue) 
			{
				listToUpdate->SetNthActionState(iter, kEnabledAction);
			}
		}
	}
}

/* DoAction
*/
void BscMnuActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{
		case kBscMnuAboutActionID:
		{
			this->DoAbout();
			break;
		}

		case kBscMnuAlwaysOnActionID:
		{
			this->DoAlwaysOn();
			break;
		}

		case kBscMnuOnIfFrontDocActionID:
		{
			this->DoOnIfFrontDoc();
			break;
		}

		case kBscMnuNeedsSelectionActionID:
		{
			this->DoNeedsSelection();
			break;
		}

		default:
		{
			break;
		}
	}
}

/* DoAbout
*/
void BscMnuActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
	   kBscMnuAboutBoxStringKey,						// Alert string
	   kOKString, 							// OK button
	   kNullString, 						// No second button
	   kNullString, 						// No third button
	   1,									// Set OK button to default
	   CAlert::eInformationIcon				// Information icon.
	);
}

/* DoAlwaysOn
*/
void BscMnuActionComponent::DoAlwaysOn()
{
	CAlert::InformationAlert(kBscMnuAlwaysOnStringKey);
}

/* DoOnIfFrontDoc
*/
void BscMnuActionComponent::DoOnIfFrontDoc()
{
	CAlert::InformationAlert(kBscMnuOnIfFrontDocStringKey);
}

/* DoNeedsSelection
*/
void BscMnuActionComponent::DoNeedsSelection()
{
	CAlert::InformationAlert(kBscMnuNeedsSelectionStringKey);
}

// End, BscMnuActionComponent.cpp.



