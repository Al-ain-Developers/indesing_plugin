//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/dynamicmenu/DynMnuDynamicMenu.cpp $
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
//  
//  For a dynamic menu example this class gets the UIDs of the spreads in the document and 
//  makes a menu entry for each one. Selecting that menu item causes action to be taken by 
//  the ActionComponent class.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
//#include "ISession.h"
#include "IApplication.h"
#include "IDynamicMenu.h"
#include "IActionIDToUIDData.h"
#include "IMenuManager.h"
#include "IActionManager.h"
#include "IActionComponent.h"
#include "IDocument.h"
#include "ISpreadList.h"

// General includes:
#include "UIDList.h"
#include "ILayoutUIUtils.h"
#include "ActionDefs.h"
#include "CPMUnknown.h"

#include "DynMnuID.h"


/** DynMnuDynamicMenu
	implements the IDynamicMenu interface.  Builds the menu each time it is
	exposed.

	
*/

class DynMnuDynamicMenu : public CPMUnknown<IDynamicMenu>
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		DynMnuDynamicMenu(IPMUnknown *boss);

		/**
			Destructor
		*/
		~DynMnuDynamicMenu();

		/** 
			This method controls what menu items appear at any given time. InDesign calls this method
			when the menu is exposed and any menu entry in the MenuDef resource uses the kSDKDefIsDynamicMenuFlag.
			Control is exercised by rebuilding this action component's valid menus with the menu and action managers. 
			This example implementation builds the menus and action IDs based on the number of 
			spreads in the front document.
			@param dynamicActionID ID of menu hit just before this method is called.
			@param widget contains the widget that invoked this action. May be nil. e.g. Useful to use as a basis for Utils<IWidgetUtils>()->QueryRelatedWidget(...) to find widgets in a panel after its popup menu is hit.
		*/
		void RebuildMenu(ActionID dynamicActionID, IPMUnknown* widget);

	protected:

		/**
			Gets the UIDs for spreads 1..n in the front document. This method will always return
			a UIDList with length > 0, event though the [0] entry may be kInvalidUID.  It is the
			responsibility of the caller to insure that [0] is a valid UID and the Idatabase* is
			is not nil.
			@return List of front document spread UIDs
		*/
		UIDList GetSpreadUIDs();
	
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(DynMnuDynamicMenu, kDynMnuDynamicMenuImpl )


/* DynMnuDynamicMenu Constructor
*/
DynMnuDynamicMenu::DynMnuDynamicMenu(IPMUnknown *boss) : 
	CPMUnknown<IDynamicMenu>(boss) 
{
}


/* DynMnuDynamicMenu Destructor
*/
DynMnuDynamicMenu::~DynMnuDynamicMenu()
{
}

/* Rebuild Menu
*/
void DynMnuDynamicMenu::RebuildMenu(ActionID dynamicActionID, IPMUnknown* widget)
{
	do {
		// Get the menu and action managers
		InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
		if (app == nil)
		{
			ASSERT_FAIL("Nil IApplication");
			break;
		}
		InterfacePtr<IActionManager> actionMgr(app->QueryActionManager());
		if (actionMgr == nil)
		{
			ASSERT_FAIL("Nil IActionManager");
			break;
		}
		InterfacePtr<IMenuManager> menuMgr(actionMgr,UseDefaultIID());
		if (menuMgr == nil)
		{
			ASSERT_FAIL("Nil IMenuManager");
			break;
		}
		InterfacePtr<IActionComponent> bscMnuActComp(this,UseDefaultIID());
		ASSERT(bscMnuActComp);
		if (!bscMnuActComp) {
			break;
		}

		// This list just keeps track of what we're displaying -- so we don't remove something that isn't
		// displayed.  As a bonus it also maps an action ID to a UID.
		InterfacePtr<IActionIDToUIDData> actionID2uidMap(this,UseDefaultIID());
		ASSERT(actionID2uidMap);
		if (!actionID2uidMap) {
			break;
		}

		// First remove all entries in the dynamic portion of the pop-up panel menu
		int32 numItems = actionID2uidMap->Length();
		if(numItems > 0)
		{
			// Remove all dynamic entries
			for (int32 j=0; j<numItems; j++)
			{
				// Calculate the action ID, then get it's corresponding UID
				ActionID nextDynMenuID(kDynMnuFirstDynamicActionID + j);
				if ( actionID2uidMap->GetUID(nextDynMenuID) == kInvalidUID )
				{
					ASSERT_FAIL("Dynamic action ID has invalid UID");
					break;
				}

				// Remove the entry from the menu manager.  Menu path is same as used in menu def resource
	 			menuMgr->RemoveMenuItem(kDynMnuTargetMenuPath, nextDynMenuID);
				
				// Remove entry from action manager
				actionMgr->RemoveAction(nextDynMenuID);

				// Remove actionID and mapping from our list of active menus
				actionID2uidMap->RemoveEntry(nextDynMenuID);

			}
			// Remove the separator between the static and menu dynamic entries.  
			// Path is same as used in menu def resource
			menuMgr->RemoveMenuItem(kDynMnuTargetMenuPath kSDKDefDelimiterAndSeparatorPath, kDynMnuSeparatorActionID);
		}

		// Get the UIDs of spreads. 
		UIDList docSpreadUIDs = this->GetSpreadUIDs();

		// Rebuild the dynamic menu based on the document state.
		numItems = docSpreadUIDs.Length();
		if ( (numItems > 0) && (docSpreadUIDs[0] != kInvalidUID) )
		{

			// Add a separator before adding the new items
			menuMgr->AddMenuItem(kDynMnuSeparatorActionID,kDynMnuTargetMenuPath kSDKDefDelimiterAndSeparatorPath, kDynMnuSeparatorPosition,kFalse);

			// Add the new items: dynamically compose the entry and action IDs
			PMReal windowMenuPos = kDynMnuItemBasePosition;
			for( int32 i = 0; i < numItems; i++)
			{
				// Compose menu entry string. Note that since it is dynamic, it is made non-translatable.
				PMString itemName("Show Spread ");
				itemName.AppendNumber(i+1);
				itemName.Append(", UID ");
				itemName.AppendNumber(docSpreadUIDs[i].Get());
				itemName.SetTranslatable(kFalse);

				// Calculate action ID for new entry
				ActionID newActionID(kDynMnuFirstDynamicActionID + i);

				// Calculate new menu position
				PMReal newMenuPos(kDynMnuItemBasePosition + i);

				// Add to menu and action managers
				actionMgr->AddAction(bscMnuActComp,			// ptr to IActionComponent to field menu hit
									newActionID,			// Action ID 
									itemName,				// Sub-menu string 
									kMiscellaneousArea,		// Action area
									kNormalAction,			// Action type
									kCustomEnabling,		// Enabling type
									kInvalidInterfaceID,	// Selection IID	
									kFalse					// User editability
									);
				menuMgr->AddMenuItem(newActionID,					// Action ID
									kDynMnuTargetMenuPath,			// Menu path
									newMenuPos,						// Menu position
									kSDKDefIsNotDynamicMenuFlag);	// Note we say it's not dynamic here.

				// Add to the list that maps action ID to UID
				actionID2uidMap->AddEntry( newActionID , docSpreadUIDs[i] );
			} 
		}
	} while (false);
}


/* GetSpreadUIDs()
*/
UIDList DynMnuDynamicMenu::GetSpreadUIDs()
{
	UIDList spreads(nil, kInvalidUID);

	do {

		// Get the spreadlist for the front document
		IDocument* fntDoc = Utils<ILayoutUIUtils>()->GetFrontDocument();
		if ( fntDoc == nil) 
		{
			// No front doc, no spreads, just exit.  This is not an error because 
			// InDesign calls RebuildMenu() every time the menu is exposed, regardless
			// of whether a document is open.
			break;
		}
		InterfacePtr<ISpreadList> docSprdLst(fntDoc, UseDefaultIID());
		if ( docSprdLst == nil )
		{
			ASSERT_FAIL("Nil ISpreadList*");
			break;
		}

		// Make a list of spread UIDs.  
		int32 numSpreads = docSprdLst->GetSpreadCount();
		UIDList tmpSprds(::GetDataBase(fntDoc));
		for (int32 i=0; i<numSpreads; i++)
		{
			tmpSprds.Append(docSprdLst->GetNthSpreadUID(i));
		}
		spreads = tmpSprds;

	} while (false);

	return spreads;
}
