//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/suppui/SuppUIActionComponent.cpp $
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
#include "ISession.h"
#include "IActionStateList.h"
#include "IApplication.h"


// General includes:
#include "CActionComponent.h"
#include "CAlert.h"
#include "SuppUISuppressedUI.h"

// Project includes:
#include "SuppUIID.h"

/** Implements IActionComponent; performs the actions that are executed when the plug-in's
	menu items are selected.

	
	@ingroup suppui

*/
class SuppUIActionComponent : public CActionComponent
{
public:
/**
 Constructor.
 @param boss interface ptr from boss object on which this interface is aggregated.
 */
		SuppUIActionComponent(IPMUnknown* boss);

		/** The action component should perform the requested action.
			This is where the menu item's action is taken.
			When a menu item is selected, the Menu Manager determines
			which plug-in is responsible for it, and calls its DoAction
			with the ID for the menu item chosen.

			@param actionID identifies the menu item that was selected.
			@param ac active context
			@param mousePoint contains the global mouse location at time of event causing action (e.g. context menus). kInvalidMousePoint if not relevant.
			@param widget contains the widget that invoked this action. May be nil. 
			*/
		virtual void DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);

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
	
		/** Toggles whether or not we are hiding Style Options OK Button */
		void ToggleSuppressStyleOptions();

		/** Toggles whether or not we are suppressing the font and size menus */
		void ToggleSuppressFontAndSizeMenus();

		/** Toggles whether or not we are suppressing open file dialog controls */
		void ToggleSuppressOpenFileDialogControls();

		/** Toggles whether we are suppressing the exposing of paragraph styles through the quick apply dialog */
		void ToggleSuppressParaStyleQuickApply();
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(SuppUIActionComponent, kSuppUIActionComponentImpl)


/* SuppUIActionComponent Constructor
*/
SuppUIActionComponent::SuppUIActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{

}

/* DoAction
*/
void SuppUIActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{

		case kSuppUIAboutActionID:
			this->DoAbout();
			break;

		case  kSuppUISuppressStyleChangesActionID:
			this->ToggleSuppressStyleOptions();
			break;

		case kSuppUISuppressFontAndSizeActionID:

			this->ToggleSuppressFontAndSizeMenus();
			break;

		case kSuppUISuppressOpenFileDialogControlsActionID:

			this->ToggleSuppressOpenFileDialogControls();
			break;

		case kSuppUISuppressParaStyleQuickApplyActionID:
			this->ToggleSuppressParaStyleQuickApply();
			break;

		default:
		{
			break;
		}
	}
}

/* UpdateActionStates
*/
void SuppUIActionComponent::UpdateActionStates(IActiveContext* ac, 
											   IActionStateList* listToUpdate, 
											   GSysPoint mousePoint, 
											   IPMUnknown* widget)
{
	for (int32 i = 0; i < listToUpdate->Length(); i++)
	{
		int16 actionState = kEnabledAction;
		switch (listToUpdate->GetNthAction(i).Get())
		{
			case kSuppUISuppressStyleChangesActionID:
				// Check to see if we need a check mark
				if (SuppUISuppressedUI::gSuppressStyleChages == kTrue) 
				{
					// Yes we do
					actionState |= kSelectedAction;
				}
				break;
				
			case kSuppUISuppressFontAndSizeActionID:
				// Check to see if we need a check mark
				if (SuppUISuppressedUI::gSuppressFontAndSizeMenus == kTrue) 
				{
					// Yes we do
					actionState |= kSelectedAction;
				}
				break;
				
			case kSuppUISuppressOpenFileDialogControlsActionID:
				// Check to see if we need a check mark
				if (SuppUISuppressedUI::gSuppressOpenFileDialogControls == kTrue) 
				{
					// Yes we do
					actionState |= kSelectedAction;
				}
				break;
			
			case kSuppUISuppressParaStyleQuickApplyActionID:
				// Check to see if we need a check mark
				if (SuppUISuppressedUI::gSuppressParaStyleQuickApply == kTrue) 
				{
					// Yes we do
					actionState |= kSelectedAction;
				}
				break;
			default:
				break;
		}
		listToUpdate->SetNthActionState(i, actionState);

	}
}


/* DoAbout
*/
void SuppUIActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
		kSuppUIAboutBoxStringKey,				// Alert string
		kOKString, 						// OK button
		kNullString, 						// No second button
		kNullString, 						// No third button
		1,							// Set OK button to default
		CAlert::eInformationIcon				// Information icon.
	);
}

/* ToggleSuppressStyleOptions
*/
void SuppUIActionComponent::ToggleSuppressStyleOptions()
{
	SuppUISuppressedUI::gSuppressStyleChages = !SuppUISuppressedUI::gSuppressStyleChages;
}

/* ToggleSuppressFontAndSizeMenus
*/
void SuppUIActionComponent::ToggleSuppressFontAndSizeMenus()
{
	SuppUISuppressedUI::gSuppressFontAndSizeMenus = !SuppUISuppressedUI::gSuppressFontAndSizeMenus;
}

/* ToggleSuppressOpenFileDialogControls
*/
void SuppUIActionComponent::ToggleSuppressOpenFileDialogControls()
{
	SuppUISuppressedUI::gSuppressOpenFileDialogControls = !SuppUISuppressedUI::gSuppressOpenFileDialogControls;
}

/* ToggleSuppressParaStyleQuickApply
*/
void SuppUIActionComponent::ToggleSuppressParaStyleQuickApply()
{
	SuppUISuppressedUI::gSuppressParaStyleQuickApply = !SuppUISuppressedUI::gSuppressParaStyleQuickApply;
}

//  Code generated by DollyXs code generator
