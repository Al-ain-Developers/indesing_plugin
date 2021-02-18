//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicpanel/BscPnlActionComponent.cpp $
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
#include "CActionComponent.h"
#include "CAlert.h"

// Project includes:
#include "BscPnlID.h"


/** Implements IActionComponent based on
	the partial implementation CActionComponent; 
	handles popup menu selections.
	
	Executes the actions that are executed when the plug-in's
	menu items are selected.

	@ingroup basicpanel
	
*/
class BscPnlActionComponent : public CActionComponent
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		BscPnlActionComponent(IPMUnknown* boss);

		/**
			The action component should execute the requested action.
			This is where the menu item's action is taken.
			When a menu item is selected, the Menu Manager determines
			which plug-in is responsible for it, and calls its DoAction
			with the ID for the menu item chosen.

			@param ac active context (see IActiveContext)
			@param actionID identifies the menu item that was selected.
			@param mousePoint where widget was clicked
			@param widget identifies the widget clicked on
			@see CActionComponent::DoAction
			*/
		void DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint = kInvalidMousePoint, IPMUnknown* widget = nil);

	private:
		/** Encapsulates functionality for the about menu item. */
		void DoAbout();

		/** Encapsulates functionality for the GoesNowhere menu item. */
		void DoGoesNowhere();

		/** Encapsulates functionality for the DoesNothing menu item. */
		void DoDoesNothing();

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(BscPnlActionComponent, kBscPnlActionComponentImpl)

/* BscPnlActionComponent Constructor
*/
BscPnlActionComponent::BscPnlActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}

/* DoAction
*/
void BscPnlActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{
		case kBscPnlPopupAboutThisActionID:
		case kBscPnlAboutActionID:
		{
			this->DoAbout();
			break;
		}

		case kBscPnlGoesNowhereActionID:
		{
			this->DoGoesNowhere();
			break;
		}

		case kBscPnlDoesNothingActionID:
		{
			this->DoDoesNothing();
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
void BscPnlActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
		kBscPnlAboutBoxStringKey,		// Alert string
		kOKString, 						// OK button
		kNullString, 					// No second button
		kNullString, 					// No third button
		1,								// Set OK button to default
		CAlert::eInformationIcon		// Information icon.
	);
}

/* DoGoesNowhere
*/
void BscPnlActionComponent::DoGoesNowhere()
{
	CAlert::InformationAlert(kBscPnlGoesNowhereStringKey);
}

/* DoDoesNothing
*/
void BscPnlActionComponent::DoDoesNothing()
{
	CAlert::InformationAlert(kBscPnlDoesNothingStringKey);
}

// End, BscPnlActionComponent.cpp.



