//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/dynamicmenu/DynMnuActionComponent.cpp $
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
#include "IActionIDToUIDData.h"
#include "IActionStateList.h"
#include "ILayoutUIUtils.h"
#include "IGeometry.h"
#include "IDocument.h"
#include "IControlView.h"
#include "IActiveContext.h"

// General includes:
#include "CActionComponent.h"
#include "CAlert.h"
#include "CmdUtils.h"
#include "StringUtils.h"


// Project includes:
#include "DynMnuID.h"


/** DynMnuActionComponent
	implements the actions that are executed when the plug-in's
	menu items are selected.

	DynMnuActionComponent implements IActionComponent based on
	the partial implementation CActionComponent.


	
*/
class DynMnuActionComponent : public CActionComponent
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		DynMnuActionComponent(IPMUnknown* boss);

		/**
			The action component should do the requested action. Because this
			plug-in has dynamic menu entries, the ActionIDs received by this
			method from the action manager is not a closed set. Action IDs for
			static menu entries are handled as an explicit case in a switch statement.
			Action IDs for dynamic menu entries are handled by the switch's default case,
			and are delegated to the DoHandleDynamic() method.
			@param ac refers to the current active context, such as the front document
			@param actionID identifies which action this action component should perform
			@param mousePoint contains the global mouse location at time of event causing action (e.g. context menus). kInvalidMousePoint if not relevant.
			@param widget contains the widget that invoked this action. May be nil. e.g. Useful to use as a basis for Utils<IWidgetUtils>()->QueryRelatedWidget(...) to find widgets in a panel after its popup menu is hit.
			*/
		virtual void	DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);

		/**
			This method controls what menu items are enabled at any given time.
			InDesign calls this method when a menu is exposed if the ActionDef 
			has entries with the enabling type set to kCustomEnabling.  This method
			is the opportunity to enable or disable any of the menu entries in the
			IActionStateList.  This implementation simply enables any item in the action
			state list for which it can find a valid spread UID in the IActionIDToUIDData interface.
			@param ac refers to the current active context, such as the front document
			@param listToUpdate contains the items that client code should update the state for
			@param mousePoint contains the global mouse location at time of event causing action (e.g. context menus). kInvalidMousePoint if not relevant.
			@param widget contains the widget that invoked this action. May be nil. e.g. Useful to use as a basis for Utils<IWidgetUtils>()->QueryRelatedWidget(...) to find widgets in a panel after its popup menu is hit.
		*/
		virtual void	UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);


	private:
		/** Encapsulates functionality for the StaticMenuEntry menu item. */
		void DoHandleStaticMenu();

		/** 
			Encapsulates handling the dynamic action IDs.  Looks up the 
			spread UIDRef for a given action ID, then scrolls to that spread.
			@param dynAct ID of action corresponding to a spread.  Any IDs received must be defined in IActionIDToUIDData.
		*/
		void DoHandleDynamic(IActiveContext* ac, ActionID dynAct);

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(DynMnuActionComponent, kDynMnuActionComponentImpl)

/* DynMnuActionComponent Constructor
*/
DynMnuActionComponent::DynMnuActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}


/* UpdateActionStates
*/
void DynMnuActionComponent::UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
	// Get the interface that maps dynamic action IDs to document UIDs
	InterfacePtr<IActionIDToUIDData> actionID2uidMap(this,UseDefaultIID());
	if ( actionID2uidMap == nil )
	{
		ASSERT_FAIL("Nil IActionIDToUIDData*");
	}

	// Iterate over the list, updating each to be enabled.
	UID itemUID = kInvalidUID;
	for(int32 i = 0; i < listToUpdate->Length(); i++)
	{
		// Get the UID mapped to this action ID & verify it's valid
		itemUID = actionID2uidMap->GetUID(listToUpdate->GetNthAction(i));

		if (itemUID != kInvalidUID)
		{
			// Set the action state to enabled.
			listToUpdate->SetNthActionState(i,kEnabledAction);
		}
		else
		{
			// Oops, we're out of sync in our UID mapping.  Bad news.  Don't enable.
			listToUpdate->SetNthActionState(i,kDisabled_Unselected);
		}
	}	
}



/* DoAction
*/
void DynMnuActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{
		case kDynMnuAboutActionID:
		{
			CAlert::ModalAlert
			(
			   kDynMnuAboutBoxStringKey,			// Alert string
			   kOKString, 							// OK button
			   kNullString, 						// No second button
			   kNullString, 						// No third button
			   1,									// Set OK button to default
			   CAlert::eInformationIcon				// Information icon.
			);
			break;
		}

		case kDynMnuStaticMenuActionID:
		{
			// Handle the static menu item.
			this->DoHandleStaticMenu();
			break;
		}

		default:
		{
			// Handle the dynamic menu items
			this->DoHandleDynamic(ac, actionID);
			break;
		}
	}
}

/* DoHandleStaticMenu
*/
void DynMnuActionComponent::DoHandleStaticMenu()
{
	do {

		// Report the number of spreads.  We could do this by polling the
		// document itself.  But the information is already stored in the
		// IActionIDtoUIDData interface.  So use that.
		InterfacePtr<IActionIDToUIDData> actionID2uidMap(this,UseDefaultIID());
		if ( actionID2uidMap == nil )
		{
			ASSERT_FAIL("Nil IActionIDToUIDData*");
			break;
		}
		int32 numSpreads = actionID2uidMap->Length();

		// Now set a string for an alert box based on the number of spreads
		// Translate the reporting string.  Replace the ^1 marker in the
		// reporting string with the actual number of spreads.  We have to
		// mark the spreadCount string as translated because there is no
		// practical way to translate the number as a string.
		PMString alertString(kDynMnuNumSpreadsStringKey, PMString::kTranslateDuringCall);
		PMString spreadCount;
		spreadCount.AppendNumber(numSpreads);
		spreadCount.SetTranslated();
		::ReplaceStringParameters( &alertString, spreadCount);

		// Show the alert box
		CAlert::InformationAlert(alertString);

	} while(false);
}


/* DoHandleDynamic
*/
void DynMnuActionComponent::DoHandleDynamic(IActiveContext* ac, ActionID dynAct)
{
	do {
		
		ASSERT(ac);
		if (!ac) {
			break;
		}

		// Get the UIDRef of the spread corresponding to this action ID
		InterfacePtr<IActionIDToUIDData> actionID2uidMap(this,UseDefaultIID());
		if ( actionID2uidMap == nil )
		{
			ASSERT_FAIL("Nil IActionIDToUIDData*");
			break;
		}

		IDocument* fntDoc = ac->GetContextDocument();
		if (fntDoc == nil)
		{
			ASSERT_FAIL(" The front document is nil.");
			break;
		}

		UIDRef spreadUIDref(::GetDataBase(fntDoc), actionID2uidMap->GetUID(dynAct));
		if (spreadUIDref.GetUID() == kInvalidUID)
		{
			ASSERT_FAIL("Invalid UID for active ActionID");
			break;
		}

		// Zoom so center of spread is in center of window
		IControlView* fntView = ac-> GetContextView();
		if (fntView == nil)
		{
			ASSERT_FAIL("The front view is nil.");
			break;
		}
		InterfacePtr<IGeometry> spreadGeo(spreadUIDref, UseDefaultIID());
		ASSERT(spreadGeo);
		if (!spreadGeo) {
			break;
		}
		InterfacePtr<ICommand> showSprdCmd(Utils<ILayoutUIUtils>()->MakeScrollToSpreadCmd(fntView, spreadGeo, kTrue));

		if (CmdUtils::ProcessCommand(showSprdCmd) != kSuccess) {
			ASSERT_FAIL("MakeScrollToSpreadCmd failed");
			break;
		}

	} while(false);
}

//  Generated by Dolly build 17: template "IfPanelMenu".
// End, DynMnuActionComponent.cpp.





