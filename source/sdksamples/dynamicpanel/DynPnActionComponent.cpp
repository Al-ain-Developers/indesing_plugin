//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/dynamicpanel/DynPnActionComponent.cpp $
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
#include "DynPnID.h"


/** Implements IActionComponent; responsible for the behaviour of the menu items
	on a dynamic panel popup menu. Just included to show that you can have multiple action
	components on the same plug-in with differing responsibilities.

	
	@ingroup dynamicpanel
*/
class DynPnActionComponent : public CActionComponent
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		DynPnActionComponent(IPMUnknown* boss);

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

	
	private:
		/** Encapsulates functionality for the about menu item. */
		void DoAbout();

		/** Encapsulates functionality for the Something menu item. */
		void DoSomething();

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(DynPnActionComponent, kDynPnActionComponentImpl)

/* DynPnActionComponent Constructor
*/
DynPnActionComponent::DynPnActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}

/* DoAction
*/
void DynPnActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{
		case kDynPnPopupAboutThisActionID:
		case kDynPnAboutActionID:
		{
			this->DoAbout();
			break;
		}

		case kDynPnSomethingActionID:
		{
			this->DoSomething();
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
void DynPnActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
	   kDynPnAboutBoxStringKey,			// Alert string
	   kOKString, 							// OK button
	   kNullString, 						// No second button
	   kNullString, 						// No third button
	   1,									// Set OK button to default
	   CAlert::eInformationIcon				// Information icon.
	);
}

/* DoSomething
*/
void DynPnActionComponent::DoSomething()
{
	CAlert::InformationAlert(kDynPnSomethingStringKey);
}

// End, DynPnActionComponent.cpp.





